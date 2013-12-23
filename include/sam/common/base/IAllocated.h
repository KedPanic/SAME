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
#ifndef __IALLOCATED__
#define __IALLOCATED__

#include <common/SamConfig.h>
#include <common/base/CAllocator.h>

namespace sam
{
	/// @brief Base class to manage the memory of allocated object.
	class IAllocated
	{
	public:
		explicit IAllocated()
		{ }

		~IAllocated()
		{ }

#ifdef SAM_DEBUG
		/// @brief Allocate memory
		/// 
		/// @param p_nSize Memory size to allocate.
		/// @param p_pAddr Pre-allocated emplacement.
		void *operator new(size_t p_nSize, void *p_pAddr)
		{
			return p_pAddr;
		}

		/// @brief Allocate memory
		/// 
		/// @param _iSize Memory size to allocate.
		/// @param _sFile Name of the file.
		/// @param _iLine Line number in the file.
		void* operator new(size_t _iSize, const char* _sFile = __FILE__, int _iLine = __LINE__)
		{
			return CAllocator::Alloc(_iSize, _sFile, _iLine);
		}

		/// @brief Allocate memory
		/// 
		/// @param _iSize Memory size to allocate.
		/// @param _sFile Name of the file.
		/// @param _iLine Line number in the file.
		void* operator new[] (size_t _iSize, const char* _sFile = __FILE__, int _iLine = __LINE__)
		{
			return CAllocator::Alloc(_iSize, _sFile, _iLine);
		}

		/// @brief Deallocate memory
		/// 
		/// @param _pPtr Pointer to free.
		void operator delete(void* _pPtr, void*)
		{
			CAllocator::Free(_pPtr);
		}

		/// @brief Deallocate memory
		/// 
		/// @param _pPtr Pointer to free.
		void operator delete(void* _pPtr, const char*, int)
		{
			CAllocator::Free(_pPtr);
		}

		/// @brief Deallocate memory
		/// 
		/// @param _pPtr Pointer to free.
		void operator delete[] (void* _pPtr, const char*, int)
		{
			CAllocator::Free(_pPtr);
		}
#else
		/// @brief Allocate memory
		/// 
		/// @param _iSize Memory size to allocate.
		void* operator new(size_t _iSize)
		{
			return CAllocator::Alloc(_iSize);
		}
	
		/// @brief Allocate memory
		/// 
		/// @param _iSize Memory size to allocate.
		void* operator new[](size_t _iSize)
		{
			return CAllocator::Alloc(_iSize);
		}			
#endif // SAM_DEBUG

		/// @brief Deallocate memory
		/// 
		/// @param _pPtr Pointer to free.
		void operator delete(void* _pPtr)
		{
			CAllocator::Free(_pPtr);
		}

		/// @brief Deallocate memory
		/// 
		/// @param _pPtr Pointer to free.
		void operator delete[] (void* _pPtr)
		{
			CAllocator::Free(_pPtr);
		}
	};
}

#ifdef SAM_DEBUG
// external type
#	define SAM_ALLOC(T) new (sam::CAllocator::Alloc(sizeof(T), __FILE__, __LINE__))T
#   define SAM_ALLOC_ARRAY(T, Nb) (T*)(sam::CAllocator::Alloc(sizeof(T) * Nb, __FILE__, __LINE__))
#   define SAM_FREE(Ptr) sam::CAllocator::Free((void*)Ptr)
#	define SAM_FREE_ARRAY(Ptr) sam::CAllocator::Free((void*)Ptr)
// internal type
#	define SAM_NEW			new (__FILE__, __LINE__)
#	define SAM_NEW_ARRAY	new (__FILE__, __LINE__)
#	define SAM_DELETE		delete
#   define SAM_DELETE_ARRAY delete[]
#else
// external type
#	define SAM_ALLOC(T) new T
#   define SAM_ALLOC_ARRAY(T, Nb) new T[Nb]
#   define SAM_FREE(Ptr) delete Ptr
#   define SAM_FREE_ARRAY(Ptr) delete[] Ptr
// internal type
#	define SAM_NEW			new
#	define SAM_NEW_ARRAY	new
#	define SAM_DELETE		delete
#   define SAM_DELETE_ARRAY delete[]
#endif

#endif // __IALLOCATED__
