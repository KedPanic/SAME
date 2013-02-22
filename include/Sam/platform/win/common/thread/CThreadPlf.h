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
#ifndef __CTHREAD_PLF_H__
#define __CTHREAD_PLF_H__

namespace sam
{	
	class SAM_COMMON_API CThread : public IAllocated
	{
	public:
		typedef int32 (*ThreadRoutine)(void *);

		/// @brief Default constructor.
		///
		/// @param p_pfRoutine Pointer function called by the thread.
		/// @param p_pData Data sent to the pointer function.
		CThread(ThreadRoutine p_pfRoutine, void *p_pData);
		~CThread();

		/// @brief Create the thread.
		/// 
		/// @param p_nStackSize Size of the stack.
		/// @param p_nAffinity Bitmask to set processor affinity. 
		///
		/// @return True if no error occurred.
		bool Create(uint32 p_nStackSize, uint32 p_nAffinity = e_Processor_Any);

		/// @brief Start the thread.
		/// 
		/// @return True if no error occurred.
		bool Start();

	private:
		HANDLE m_pThread;
		uint32 m_nID;

		ThreadRoutine m_pfRoutine;
		void *m_pData;

		/// @brief Entry point for the thread.
		/// 
		/// @param p_pData This pointer.
		static DWORD WINAPI ThreadEntry(LPVOID p_pData);

		/// @brief Call the routine.
		/// 
		/// @return Thread return.
		int32 Run();
	};
}

#endif // __CTHREAD_PLF_H__
