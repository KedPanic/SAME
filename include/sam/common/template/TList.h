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
#ifndef __TPL_LIST__
#define __TPL_LIST__

namespace sam
{
    namespace tpl
    {
        /// @brief Template of chained list.
        template<typename T>
        class TList
        {
        public:
            /// @brief Default constructor.
            TList(void) : m_pNext(NULL), m_pPrev(NULL) {}

            /// @brief Retrieves previous node.
            ///
            /// @return Previous node.
            T *GetPrev(void) const {return m_pPrev;}

            /// @brief Retrieves next node.
            ///
            /// @return Next node.
            T *GetNext(void) const {return m_pNext;}

			/// @brief Add to the end.
			///
			/// @param p_pPtr Node to add.
			///
			/// @return true if no error occurred.
			bool Add(T *p_pPtr)
			{
				SAM_ASSERT(p_pPtr != NULL, "p_pPtr is NULL");

				T *pCurrent = (T*)this;
				while(pCurrent->m_pNext)
				{
#ifdef SAM_DEBUG
					if(pCurrent == p_pPtr)
						return false;
#endif
					pCurrent = pCurrent->m_pNext;
				}

				p_pPtr->m_pPrev = pCurrent;
				pCurrent->m_pNext = p_pPtr;

				return true;
			}

			/// @brief Remove specified node.
			///
			/// @param p_pPtr Node to add.
			///
			/// @return next node if p_pPtr is the head, previous node or null if not found.
			T *Remove(T *p_pPtr)
			{
				SAM_ASSERT(p_pPtr != NULL, "p_pPtr is NULL");

				T *pCurrent = (T*)this;
				while(pCurrent->m_pNext)
				{
					if(pCurrent == p_pPtr)
					{
						// is head ?
						if(pCurrent->m_pPrev == NULL)
						{
							if(pCurrent->m_pNext != NULL)
								pCurrent->m_pNext->m_pPrev = NULL;

							return pCurrent->m_pNext;
						}

						pCurrent->m_pNext->m_pPrev = pCurrent->m_pPrev;
						pCurrent->m_pPrev->m_pNext = pCurrent->m_pNext;
						return pCurrent->m_pPrev;
					}

					pCurrent = pCurrent->m_pNext;
				}

				return NULL; // not found.
			}

        protected:
            T *m_pNext; ///< Next node in the chained list.
            T *m_pPrev; ///< Precedent node in the chained list.
        };

		/// @brief Template of linked list.
		template<class T>
		class List : public IAllocated
		{
		private:
			/// @brief Node.
			template<class V>
			struct Link : public IAllocated
			{
				V *value;
				Link<V> *next;
				Link<V> *prev;
			};

			Link<T> *m_pHead;
			Link<T> *m_pTail;

		public:
			/// @brief Default constructor.
			List() : m_pHead(NULL), m_pTail(NULL) {}

			//----------------------------------------------------------//
			//						ITERATOR							//
			//----------------------------------------------------------//
			/// @brief Iterator.
			template<class I>
			class Iterator : public IAllocated
			{
			public:
				/// @brief Constructor.
				///
				/// @param _pCurrent Current node.
				Iterator(Link<I> *_pCurrent) : current(_pCurrent) {}

				/// @brief Go to next node.
				Iterator<I> &operator++()
				{
					current = current->next;
					return *this;
				}

			private:
				Link<I> *current;
			};
		};
    }
}

#endif // __TPL_LIST__
