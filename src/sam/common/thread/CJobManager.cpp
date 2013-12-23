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
#include "SamCommonPCH.h"
#include "template/TVector.h"
#include "thread/CJobManager.h"
#include "thread/CThread.h"
#include "thread/CMutex.h"

#include "thread/CAtomic.h"
#include "thread/CJobArray.h"

namespace sam
{
	//////////////////////////////////////////////////////////////////////////
	//							WORKER THREAD								//
	//////////////////////////////////////////////////////////////////////////
	static uint32 s_nMaxJobArrays = 0; ///< Size of the ring buffer.

	class CWorkerThread : public CThread
	{
	public:
		CWorkerThread();
		~CWorkerThread();

		void Create(uint32 p_nMaxJobArray, uint32 p_nStackSize, uint32 p_nAffinity);
		void AddJobArray(CJobArray *p_pJobArray);
		void RemoveJobArray(CJobArray *p_pJobArray);

	private:
		CJobArray  **m_aJobArrays;		///< Ring buffer of job arrays.
		uint32		m_nCurrentJobIndex;	///< Index of the current treated job queue.
		uint32		m_nLastJobIndex;	///< Index of the last job queue added.
		CMutex		m_oAddJobMutex;		///< Mutex use when we try to add a job queue in the ring buffer.

		virtual int32 Run();
	};

	CWorkerThread::CWorkerThread()
		: m_nCurrentJobIndex(0), m_nLastJobIndex(0)
	{

	}
	//SuceMabite
	CWorkerThread::~CWorkerThread()
	{
		SAM_FREE_ARRAY(m_aJobArrays);
	}

	void CWorkerThread::Create(uint32 p_nMaxJobArrays, uint32 p_nStackSize, uint32 p_nAffinity)
	{
		CThread::Create(p_nStackSize, p_nAffinity);

		s_nMaxJobArrays = p_nMaxJobArrays;
		m_aJobArrays = SAM_ALLOC_ARRAY(CJobArray*, s_nMaxJobArrays);
		memset(m_aJobArrays, 0, sizeof(CJobArray*) * s_nMaxJobArrays);
	}

	void CWorkerThread::AddJobArray(CJobArray *p_pJobArray)
	{
		m_aJobArrays[m_nLastJobIndex & (s_nMaxJobArrays - 1)] = p_pJobArray;
		m_nLastJobIndex = (m_nLastJobIndex + 1) & (s_nMaxJobArrays - 1);
	}

	void CWorkerThread::RemoveJobArray(CJobArray *p_pJobArray)
	{

	}

	int32 CWorkerThread::Run()
	{
		SWorkerThreadState *oWorkerThreadState = SAM_ALLOC_ARRAY(SWorkerThreadState, s_nMaxJobArrays);

		while(IsRunning())
		{
			if(m_nLastJobIndex != m_nCurrentJobIndex)
			{
				// clean the list.

				// run current job array.
				if(m_aJobArrays[m_nCurrentJobIndex])
				{
					// reset state.
					oWorkerThreadState[m_nCurrentJobIndex].m_nCurrentJob = 0;

					m_aJobArrays[m_nCurrentJobIndex]->Run(oWorkerThreadState[m_nCurrentJobIndex]);
					m_aJobArrays[m_nCurrentJobIndex] = NULL;
				}

				// go to next job array.
				m_nCurrentJobIndex = (m_nCurrentJobIndex + 1) & (s_nMaxJobArrays - 1);
			}			
		}

		SAM_FREE_ARRAY(oWorkerThreadState);

		return 0;
	}
	static CWorkerThread *s_pWorkerThreads;
	//////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////
	//								JOB MANAGER								//
	//////////////////////////////////////////////////////////////////////////
	CJobManager::CJobManager()
		: m_pNbThreads(0), m_aSubmitedJobArrays(8)
	{

	}

	CJobManager::~CJobManager()
	{
	}

	// Create and start n threads.
	void CJobManager::Initialize(uint32 p_nMaxJobArrays, uint32 p_nThreads, uint32 *p_aAffinities)
	{
		// Miaou !
		SAM_ASSERT(p_nThreads > 0, "p_nThreads can't be equal to 0");
		SAM_ASSERT(s_pWorkerThreads == NULL, "Worker thread are already created.");

		m_aSubmitedJobArrays.SetSize(p_nMaxJobArrays);

		s_pWorkerThreads = SAM_NEW_ARRAY CWorkerThread[p_nThreads];
		for(uint32 index = 0; index < p_nThreads; ++index)
		{
			s_pWorkerThreads[index].Create(p_nMaxJobArrays, 64 * 1024, p_aAffinities[index]);
			s_pWorkerThreads[index].Start();
		}

		m_pNbThreads = p_nThreads;
	}

	// Shutdown the created threads.
	void CJobManager::Shutdown()
	{
		SAM_ASSERT(s_pWorkerThreads != NULL, "Worker thread was not created");

		for(uint32 index = 0; index < m_pNbThreads; ++index)
		{
			s_pWorkerThreads[index].Stop();
		}

		SAM_DELETE_ARRAY s_pWorkerThreads;
		s_pWorkerThreads = NULL;
	}

	// Submit job list to the worker threads.
	void CJobManager::Submit(CJobArray *p_pJobArray)
	{
		m_aSubmitedJobArrays.Push(p_pJobArray);

		for(uint32 index = 0; index < m_pNbThreads; ++index)
		{
			s_pWorkerThreads[index].AddJobArray(p_pJobArray);
		}
	}

	// Remove ended job array.
	void CJobManager::Remove(CJobArray *p_pJobArray)
	{
		for(uint32 index = 0; index < m_pNbThreads; ++index)
		{
			s_pWorkerThreads[index].RemoveJobArray(p_pJobArray);
		}
	}

	// Wait for job list completion.
	void CJobManager::WaitJobListsCompletion()
	{
		for(uint32 index = 0; index < m_aSubmitedJobArrays.GetNbElements(); ++index)
		{
			m_aSubmitedJobArrays[index]->Wait();			
		}

		m_aSubmitedJobArrays.Clear();
	}
}
