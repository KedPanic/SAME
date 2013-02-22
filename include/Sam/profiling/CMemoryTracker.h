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
#ifndef __CMEMORY_TRACKER__
#define __CMEMORY_TRACKER__

namespace sam
{
    /// @brief Memory tracking to check memory leak.
    class SAM_PROFILING_API CMemoryTracker
    {
    public:
        /// @brief Constructor.
        CMemoryTracker(void);

        /// @brief Get the unique instance.
        /// 
        /// @return The unique instance of CMemoryTracker
        static CMemoryTracker *GetInstance(void);

        /// @brief Destroy the unique instance of CMemoryTracker
        static void Release(void);	

        /// @brief Register a memory allocation.
        /// 
        /// @param _pPtr  Memory address.
        /// @param _iSize Allocated memory size.
        /// @param _sFile Name of the file.
        /// @param _iLine Line number in the file.
        void RegisterAlloc(void *_pPtr, size_t _iSize, const char *_sFile, int _iLine);

        /// @brief Register a memory deallocation.
        /// 
        /// @param _pPtr  Memory address.
        void RegisterFree(void *_pPtr);

        /// @brief Log the memory.
        void Log();

    private:
        /// @brief Define a memory bloc
        struct MemoryBloc
        {
            void *ptr;			///< Pointer to the allocated memory.
            char *file;         ///< File where the memory has allocated.
            int line;			///< Line where the memory has allocated.
        };

        typedef std::map<void*, MemoryBloc*> MemoryBlocs;
        MemoryBlocs m_aMemoryBlocs; ///< Array of allocated memory bloc.

        static CMemoryTracker *m_pMemoryTracker; ///< Unique instance
    };
}

#endif // __CMEMORY_MANAGER__
