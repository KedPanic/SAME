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
#include "common/thread/CThread.h"

namespace sam
{
	// Default constructor.
	CThread::CThread()
		: m_oThread(NULL), m_nID(-1), m_bIsRunning(false), m_nStackSize(0), m_nAffinity(0)
	{
	}

	CThread::~CThread()
	{
	}

	// Create the thread.
	bool CThread::Create(uint32 p_nStackSize, uint32 p_nAffinity /*= e_Processor_Any*/)
	{
		SAM_ASSERT(m_oThread == NULL, "Thread is already created");

        m_nStackSize = p_nStackSize;
        m_nAffinity = p_nAffinity;

		return true;
	}

	// Start the thread.
	bool CThread::Start()
	{
		SAM_ASSERT(m_oThread == NULL, "Thread is already created");

		// set stack size.
        pthread_attr_t oAttributes;
        pthread_attr_init(&oAttributes);
        pthread_attr_setstacksize(&oAttributes, m_nStackSize);

        m_nID = pthread_create(&m_oThread, &oAttributes, &CThread::ThreadEntry, this);
		if(!m_nID)
		{
            pthread_setname_np(m_oThread, "ROBERT");

            // set affinity.
            cpu_set_t oCPUSet;
            CPU_ZERO(&oCPUSet);

            for(uint32 nIndex = 1; nIndex <= 8; ++nIndex)
            {
                if(m_nAffinity & 1 << nIndex)
                {
                    CPU_SET(nIndex, &oCPUSet);
                }
            }

            m_bIsRunning = true;
            return pthread_setaffinity_np(m_oThread, sizeof(cpu_set_t), &oCPUSet) == 0;
		}

		return false;
	}

	// Stop the thread.
	void CThread::Stop()
	{
		m_bIsRunning = false;
	}

	// Retrieves if the thread is running.
	bool CThread::IsRunning()
	{
		return m_bIsRunning;
	}

	// Yield the execution to another thread on the current processor.
	void CThread::Yield()
	{
		pthread_yield();
	}

	// Wait until the thread is not finish.
	void CThread::Wait()
	{
        while(m_nID != 0)
        {
            sleep(50);
        }
	}

	// Entry point for the thread.
	void *CThread::ThreadEntry(void *p_pData)
	{
		CThread *pThread = (CThread*)p_pData;

        pThread->Run();
        pthread_exit(NULL);

        pThread->m_nID = 0;
		return NULL;
	}
}
