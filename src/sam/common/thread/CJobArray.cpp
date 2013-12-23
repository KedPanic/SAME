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
#include "thread/CMutex.h"
#include "thread/CAtomic.h"
#include "thread/CJobArray.h"

namespace sam
{
	CJobArray::CJobArray(uint32 p_nSize)
		: m_aJobs(), m_oMutex()
	{
		m_aJobs.SetSize(p_nSize);
	}

	CJobArray::~CJobArray()
	{

	}

	// Add a new job.
	void CJobArray::AddJob(const SJob &p_oJob)
	{
		SAM_ASSERT(p_oJob.m_pfCallback != NULL, "Job callback is null");

		SJob &oJob = m_aJobs.Alloc();
		oJob.m_pData = p_oJob.m_pData;
		oJob.m_pfCallback = p_oJob.m_pfCallback;
	}

	// Get the next job and remove it from the queue.
	void CJobArray::Run(SWorkerThreadState &p_oState)
	{
		m_nNbThreads.Increment();

		while(m_aJobs.GetNbElements() > (uint32)m_nCurrentJob.GetValue())
		{
			p_oState.m_nCurrentJob = m_nCurrentJob.Increment();

			if(p_oState.m_nCurrentJob < m_aJobs.GetNbElements())
			{
				m_aJobs[p_oState.m_nCurrentJob].m_pfCallback(m_aJobs[p_oState.m_nCurrentJob].m_pData);
			}
		}

		m_nNbThreads.Decrement();

		// check if there is no more thread executing this job array.
		if(m_nNbThreads.GetValue() == 0)
		{
			// TODO: send a signal to erase this job array.
//			g_Env->pJobManager->suceUneBite(maBite); //Error: Ma bite is too big
		}
	}

	// Wait for completion.
	void CJobArray::Wait()
	{
		// we wait for the jobs completion.
		while(m_aJobs.GetNbElements() > (uint32)m_nCurrentJob.GetValue())
		{
			
		}

		// we want to be sure there no thread in the run function.
		while(m_nNbThreads.GetValue() > 0)
		{

		}
	}
}
