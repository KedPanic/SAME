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
	namespace
	{
		// See: http://msdn.microsoft.com/en-us/library/xcb2z8hs(VS.90).aspx
		typedef struct tagTHREADNAME_INFO
		{
			DWORD dwType; // must be 0x1000
			LPCSTR szName; // pointer to name (in user addr space)
			DWORD dwThreadID; // thread ID (-1=caller thread)
			DWORD dwFlags; // reserved for future use, must be zero
		} THREADNAME_INFO;

		void SetThreadName( DWORD dwThreadID, LPCSTR szThreadName)
		{
			const DWORD MS_VC_EXCEPTION = 0x406D1388;

			THREADNAME_INFO info;
			info.dwType = 0x1000;
			info.szName = szThreadName;
			info.dwThreadID = dwThreadID;
			info.dwFlags = 0;

			__try
			{
				RaiseException(MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(DWORD), (DWORD*)&info );
			}
			__except(EXCEPTION_CONTINUE_EXECUTION)
			{
			}
		}

		/// @brief Entry point for the thread.
		/// 
		/// @param p_pData This pointer.
		static DWORD WINAPI ThreadEntry(LPVOID p_pData);
	}

	// Default constructor.
	CThread::CThread()
		: m_pThread(NULL), m_nID(-1), m_bIsRunning(false)
	{
	}

	CThread::~CThread()
	{
	}

	// Create the thread.
	bool CThread::Create(uint32 p_nStackSize, uint32 p_nAffinity /*= e_Processor_Any*/)
	{
		SAM_ASSERT(m_pThread == NULL, "Thread is already created");
			
		m_pThread = CreateThread(0, p_nStackSize, &CThread::ThreadEntry, this, CREATE_SUSPENDED, (LPDWORD)&m_nID);

		if(m_pThread)
		{
			SetThreadName(m_nID, "ROBERT");

			return SetThreadAffinityMask(m_pThread, p_nAffinity) != 0;
		}

		SamLogError("Unable to create thread");
		return false;
	}

	// Start the thread.
	bool CThread::Start()
	{
		SAM_ASSERT(m_pThread != NULL, "Thread was not created");

		m_bIsRunning = true;
		return ResumeThread(m_pThread) != -1;
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
		SwitchToThread();
	}

	/// @brief Wait until the thread is not finish.
	void CThread::Wait()
	{
		WaitForSingleObject(m_pThread, INFINITE);
	}

	// Entry point for the thread.
	DWORD CThread::ThreadEntry(LPVOID p_pData)
	{
		CThread *pThread = (CThread*)p_pData;

		return pThread->Run();
	}
}
