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
#ifndef __TOBJECT_POOL__
#define __TOBJECT_POOL__

namespace sam
{
	namespace core
	{
		/// @brief Object pool. Allocate an array of N object of type T.
		/// 
		/// @remarks
		/// 
		/// We have a roster which is an array of indices into the instance pool.
		/// We use a index for the partition between allocated and free pool index.
		/// The partition is an array of roster index per pool object.
		/// 
		/// Partition			Roster			Pool
		/// [ roster index ]	[ pool index ]	[ object ]
		/// 
		template<typename T>
		class TObjectPool
		{
		public:
			/// @brief Default constructor.
			/// 
			/// @param p_nSize Number of allocable objects.
			TObjectPool(uint32 p_nSize)
				: m_apInstancePool(NULL), m_nPoolSize(p_nSize), m_anRoster(NULL), m_nCurrentPos(0), m_anPartition(NULL)
			{
				m_apInstancePool = SAM_ALLOC_ARRAY(T, m_nPoolSize);				
				m_anRoster = SAM_ALLOC_ARRAY(uint32, m_nPoolSize);
				m_anPartition = SAM_ALLOC_ARRAY(uint32, m_nPoolSize);

				for(uint32 index = 0; index < m_nPoolSize; ++index)
				{
					m_anRoster[index]	  = index;
					m_anPartition[index]  = ~0;
				}
			}

			/// @brief Destructor.
			~TObjectPool()
			{
				FreeAll();
			}

			/// @brief Allocate a new instance.
			/// 
			/// @return Pointer to the allocated object or null if there is no more place.
			T *Alloc()
			{
				SAM_ASSERT(m_nCurrentPos < m_nPoolSize, "Insufficient size of the pool");

				if(m_nCurrentPos < m_nPoolSize)
				{
					// retrieve the next free node.
					uint32 nFreeNode = m_anRoster[m_nCurrentPos];
					m_anPartition[nFreeNode] = m_nCurrentPos;
					m_nCurrentPos++;

					// create the object.
					return new(&m_apInstancePool[nFreeNode])T;
				}

				return NULL;
			}

			/// @brief Release an allocated object.
			/// 
			/// @param p_pObject Allocated object to release.
			void Free(T *p_pObject)
			{
				SAM_ASSERT(IsFrom(p_pObject) == true, "p_pObject has not been allocated by this pool");
				SAM_ASSERT(m_nCurrentPos > 0, "The pool is empty.");

				// retrieves the pool and roster index.
				uint32 nPoolIndex = p_pObject - m_apInstancePool;
				uint32 nRosterIndex = m_anPartition[nPoolIndex];
				--m_nCurrentPos;

				// call the destructor.
				p_pObject->~T();
				m_anPartition[nPoolIndex] = ~0;

				// swap the indices between the last allocated object and the freed one.
				if(m_nCurrentPos)
				{					
					m_anRoster[nRosterIndex] = m_anRoster[m_nCurrentPos];
					m_anRoster[m_nCurrentPos] = nPoolIndex;

					// update the partition.
					m_anPartition[m_anRoster[nRosterIndex]] = nRosterIndex;
				}
			}

			/// @brief Retrieves if the specified object has been allocated by the pool.
			/// 
			/// @param p_pObject Allocated object to check if it has been allocated by this pool.
			///
			/// @return True if it has been allocated by this pool.
			bool IsFrom(T *p_pObject) const
			{
				return p_pObject >= m_apInstancePool && p_pObject <= &m_apInstancePool[m_nPoolSize - 1];
			}

			/// @brief Free all instance and reset the pool.
			void FreeAll()
			{
				for(uint32 nIndex = 0; nIndex < m_nCurrentPos; ++nIndex)
				{
					uint32 nPoolIndex = m_anRoster[nIndex];
					m_anPartition[nPoolIndex] = ~0;

					m_apInstancePool[nPoolIndex].~T();
				}

				m_nCurrentPos = 0;
			}

		private:
			T *m_apInstancePool;	///< Array of allocated memory.
			uint32	m_nPoolSize;	///< Number of allocated objects (T * m_nPoolSize = size in memory).

			uint32  *m_anRoster;	///< Indirection table.
			uint32	m_nCurrentPos;	///< Current position in the table.
			uint32	*m_anPartition;	///< Contain roster index of an instance.
		};
	}	
}

#endif // __TOBJECT_POOL__
