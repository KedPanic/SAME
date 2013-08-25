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
#ifndef __CJOB_QUEUE__
#define __CJOB_QUEUE__

namespace sam
{
	/// @brief Worker thread running state.
	struct SWorkerThreadState
	{
		uint32 m_nCurrentJob; ///< Current job index treated by a thread.

	};

	/// @brief A job to be executed by the thread pool.
	struct SAM_COMMON_API SJob
	{
		typedef void (*JobCallback)(void *p_pData);

		JobCallback m_pfCallback;	///< The function called when the job is executed.
		void *m_pData;				///< The data to send to the callback.
	};

	/// @brief A job array is shared between all worker threads. Each thread can access to the job and execute n job.
	class SAM_COMMON_API CJobArray : public IAllocated
	{
	public:
		/// @brief Default constructor.
		/// 
		/// @param p_nSize Size of the array.
		CJobArray(uint32 p_nSize);
		~CJobArray();

		/// @brief Add a new job.
		/// 
		/// @param p_oJob New job to add in the queue.
		void AddJob(const SJob &p_oJob);

		/// @brief Execute n job.
		/// 
		/// @param p_oState Worker thread state.
		void Run(SWorkerThreadState &p_oState);

		/// @brief Wait for completion.
		void Wait();

	private:
		tpl::Vector<SJob> m_aJobs;  ///< Job array.
		CAtomicInteger m_nCurrentJob;
		CAtomicInteger m_nNbThreads; ///< Number of thread are executing the job array.
		CMutex m_oMutex;
	};
}

#endif // __CJOB_QUEUE__
