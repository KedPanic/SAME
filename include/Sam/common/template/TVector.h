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

			Vector(uint32 p_nNbElements)
				: m_nNbElements(p_nNbElements)
			{
				
			}

			T& Push(T p_Value)
			{
				m_pData[m_nSize] = p_Value;
				++m_nSize;

				if(m_nSize == m_nNbElements)
				{
					Reallocate();
				}
			}

			T& operator[] (uint32 p_nIndex)
			{
				SAM_ASSERT(p_nIndex < m_nNbElements);

				return m_pData[p_nIndex];
			}

		private:
			T *m_pData;
			uint32 m_nSize;
			uint32 m_nNbElements;			

			void Allocate()
			{
				m_pData = SAM_ALLOC_ARRAY(T, m_nNbElements);
			}

			void Reallocate()
			{
				m_nNbElements *= 2;
				m_pData = realloc(m_pData, m_nNbElements * sizeof(T))
			}
		};
	}
}

#endif // __COMMON_TPL_VECTOR_H__
