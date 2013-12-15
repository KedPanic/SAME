//===========================================
// Copyright (C) 2013 Cedric Liaudet
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to
// do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//===========================================
#include "SamBoxPCH.h"
#include "exporter/CExporterManager.h"
#include "exporter/IExporter.h"
#include "resources/IResource.h"

//////////////////////////////////////////////////////////////////////////
//							WORKER THREAD								//
//////////////////////////////////////////////////////////////////////////
static uint32 s_nMaxJobArrays = 0; ///< Size of the ring buffer.

class CExportRequest
{
public:
	uint32 m_nSize;
	sam::SJob *m_aJobs;
	sam::CAtomicInteger m_nCurrentJob;
	sam::CAtomicInteger m_nLastAddedJob;
	sam::CAtomicInteger m_nNbJobs;

	void AddJob(const sam::SJob &p_oJob)
	{
		// before to add new job we add the jobs in the queue.
		while(m_aJobQueue.empty() == false)
		{
			sam::SJob &oJob = m_aJobQueue.back();
			if(!AddJobInternal(oJob))
			{
				break;
			}

			m_aJobQueue.pop();
		}

		AddJobInternal(p_oJob);
	}

private:
	typedef std::queue<sam::SJob> JobQueue;
	JobQueue m_aJobQueue;

	bool AddJobInternal(const sam::SJob &p_oJob)
	{
		if(m_nNbJobs.GetValue() < static_cast<int32>(m_nSize))
		{
			uint32 nIndex = m_nLastAddedJob.Increment();
			if(nIndex == m_nSize)
			{
				nIndex = 0;
				m_nLastAddedJob.SetValue(0);
			}							

			m_aJobs[nIndex].m_pData = p_oJob.m_pData;
			m_aJobs[nIndex].m_pfCallback = p_oJob.m_pfCallback;
			m_nNbJobs.Increment();

			return true;
		}

		// add to the queue when there is no more place.
		m_aJobQueue.push(p_oJob);
		return false;
	}
};
static CExportRequest s_oExportRequest;
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//							WORKER THREAD								//
//////////////////////////////////////////////////////////////////////////
class CExporterWorkerThread : public sam::CThread
{
public:
	CExporterWorkerThread();
	~CExporterWorkerThread();

	void WaitUntilIsExporting();

private:
	uint32 m_nCurrentJobIndex;		///< Index of the current treated job queue.
	bool   m_bRequestStop;			///< True if we have to stop when there is no more export.

	virtual int32 Run();
};

CExporterWorkerThread::CExporterWorkerThread()
	: m_nCurrentJobIndex(0), m_bRequestStop(false)
{

}

CExporterWorkerThread::~CExporterWorkerThread()
{
}

void CExporterWorkerThread::WaitUntilIsExporting()
{
	m_bRequestStop = true;
	Wait();
}

int32 CExporterWorkerThread::Run()
{
	while(IsRunning())
	{
		if(s_oExportRequest.m_nNbJobs.GetValue() > 0)
		{
			// run current job.
			m_nCurrentJobIndex = s_oExportRequest.m_nCurrentJob.Increment() - 1;
			if(s_oExportRequest.m_nCurrentJob.GetValue() == s_oExportRequest.m_nSize)
			{
				s_oExportRequest.m_nCurrentJob.SetValue(0);
			}
			
			s_oExportRequest.m_aJobs[m_nCurrentJobIndex].m_pfCallback(s_oExportRequest.m_aJobs[m_nCurrentJobIndex].m_pData);
			s_oExportRequest.m_nNbJobs.Decrement();
		}
		else if(m_bRequestStop)
		{
			Stop();
		}
		else 
		{			
			Yield();
		}
	}

	return 0;
}
static CExporterWorkerThread *s_pWorkerThreads;
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//							SAM EXPORTER								//
//////////////////////////////////////////////////////////////////////////
typedef IExporter *(*CreateExporterPlugin)();

CExporterManager *g_pExporterManager = NULL;
// Constructor.
CExporterManager::CExporterManager(uint32 p_nJobArraySize /*= 128*/)
	: m_pJobArray(NULL)
{
	g_pExporterManager = this;

	s_oExportRequest.m_aJobs = SAM_ALLOC_ARRAY(sam::SJob, p_nJobArraySize);
	s_oExportRequest.m_nSize = p_nJobArraySize;
	s_oExportRequest.m_nLastAddedJob.SetValue(p_nJobArraySize - 1);

	// create the worker thread.
	// for now we use an internal system instead of the job manager in the engine.
	// may be we should use it later.
	s_pWorkerThreads = SAM_NEW CExporterWorkerThread;
	s_pWorkerThreads->Create(4 * 1024);
	s_pWorkerThreads->Start();
}

CExporterManager::~CExporterManager()
{
	s_pWorkerThreads->WaitUntilIsExporting();

	SAM_FREE_ARRAY(s_oExportRequest.m_aJobs);
}

// Request a new export.
void CExporterManager::RequestExport(IResource *p_pResource, const String &p_sDestination, uint32 p_nOutputFormat, sam::ID p_nPlatformId)
{
	Exporters::iterator it = m_aExporters[p_pResource->GetResourceType()].begin(), it_end = m_aExporters[p_pResource->GetResourceType()].end();
	while(it != it_end)
	{
		IExporter *pExporter = (*it);
		if(pExporter->IsSupported(p_nOutputFormat))
		{
			// create subdirectory.
			sam::CreateDirectory(p_sDestination.c_str());

			// create job export.
			sam::SJob oJob = pExporter->CreateJob(p_pResource, p_sDestination, p_nPlatformId);
			s_oExportRequest.AddJob(oJob);
			break;
		}
	}

	SAM_ASSERT(it != it_end, "Unsupported output format");
}

// Register exporter.
void CExporterManager::RegisterExporter(const char *p_sExporterPath)
{
	Library pLibrary = SamLoadLibrary(p_sExporterPath);
	if(pLibrary)
	{
		CreateExporterPlugin pSymbol = (CreateExporterPlugin)SamGetSymbol(pLibrary, "CreateExporterPlugin");
		if(pSymbol)
		{
			IExporter *pExporter = pSymbol();
			m_aExporters[pExporter->GetResourceType()].push_back(pExporter);
		}
	}
}

// Register an exporter.
void CExporterManager::RegisterExporter(IExporter *p_pExporter)
{
	m_aExporters[p_pExporter->GetResourceType()].push_back(p_pExporter);
}

// Register listener.
void CExporterManager::RegisterListener(IExporterListener *p_pListener)
{	
	SAM_ASSERT(p_pListener != NULL, "p_pListener is null");

	m_aListeners.push_back(p_pListener);
}

// Submit export to the job manager.
void CExporterManager::Submit()
{
	
}

// Retrieves specific exporter.
IExporter *CExporterManager::GetExporter(EResourceType p_eResourceType, const char *p_sExporterName)
{
	Exporters::iterator oExporterIt = m_aExporters[p_eResourceType].begin();
	Exporters::iterator oExporterItEnd = m_aExporters[p_eResourceType].end();
	while(oExporterIt != oExporterItEnd)
	{
		if(strcmp((*oExporterIt)->GetName(), p_sExporterName) == 0)
		{
			return *oExporterIt;
		}

		++oExporterIt;
	}

	return NULL;
}