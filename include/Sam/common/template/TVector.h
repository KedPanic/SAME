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
#ifndef __COMMON_TPL_VECTOR_H__
#define __COMMON_TPL_VECTOR_H__

namespace sam
{
	namespace tpl
	{
		template<typename T>
		class Vector
		{
		public:
			class Iterator
			{
			public:
				T operator*()
				{
					return m_current;
				}

				T operator->()
				{
					return m_current;
				}

				void operator++()
				{
					m_current = (uint8*)m_current + sizeof(T);
				}


			private:
				T m_current;
			};

			/// @brief Default constructor.
			/// 
			/// @param p_nGranularity Base size of the array.
			Vector(uint32 p_nGranularity = 8)
				: m_pData(NULL), m_nSize(0), m_nNbElements(0), m_nGranularity(p_nGranularity)
			{
				SAM_ASSERT(p_nGranularity != 0, "the granularity can't be equal to 0");
			}

			/// @brief Set the current size of the array.
			void SetSize(uint32 p_nSize)
			{
				Resize(p_nSize);
			}

			/// @brief Clear the vector.
			void Clear()
			{
				memset(m_pData, 0, sizeof(T) * m_nNbElements);
				m_nNbElements = 0;
			}

			/// @brief Retrieves if the vector is empty.
			///
			/// @return true if the vector is empty.
			bool IsEmpty() const {return m_nNbElements == 0;}

			/// @brief Retrieves the number of allocated elements.
			///
			/// @return the number of allocated elements.
			uint32 GetNbElements() const {return m_nNbElements;}

			T& Push(T p_Value)
			{
				if(m_nSize == m_nNbElements)
				{
					Resize(m_nSize + m_nGranularity);
				}

				++m_nNbElements;
				return m_pData[m_nNbElements - 1] = p_Value;
			}

			T& Alloc()
			{
				if(m_nSize == m_nNbElements)
				{
					Resize(m_nSize + m_nGranularity);
				}

				++m_nNbElements;
				return m_pData[m_nNbElements - 1];
			}

			T& operator[] (uint32 p_nIndex) const
			{
				SAM_ASSERT(p_nIndex < m_nNbElements, "Index is out of the number of elements.");

				return m_pData[p_nIndex];
			}

		private:
			T *m_pData;
			uint32 m_nSize;
			uint32 m_nNbElements;
			uint32 m_nGranularity;

			void Resize(uint32 p_nNewSize)
			{
				T *pOldData = m_pData;

				p_nNewSize += m_nGranularity;
				m_pData = SAM_ALLOC_ARRAY(T, p_nNewSize * sizeof(T));

				if(pOldData)
				{
					memcpy(m_pData, pOldData, m_nSize);
					SAM_FREE_ARRAY(pOldData);

					if(p_nNewSize < m_nNbElements)
					{
						m_nNbElements = p_nNewSize;
					}
				}

				m_nSize = p_nNewSize;
			}
		};


	}
}

#endif // __COMMON_TPL_VECTOR_H__
