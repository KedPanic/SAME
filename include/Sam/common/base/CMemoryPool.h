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
#ifndef __CMEMORY_POOL__
#define __CMEMORY_POOL__

namespace sam
{
    /// @brief Memory pool.
    class CMemoryPool
    {
    public:
        /// @brief Default constructor.
        /// 
        /// @param _pBuffer Memory block.
        /// @param _nSize Size of the memory block.
        CMemoryPool(void *_pBuffer, const uint32 _nSize)
            : m_pBeginMemoryBuffer(_pBuffer), m_pEndMemoryBuffer(_pBuffer + _nSize), m_pAvailableMemory(_pBuffer), m_pFreeMemoryBlocks(NULL)
        {
        }

        /// @brief Retrieves the size of the memory pool.
        /// 
        /// @return Size of the memory pool.
        uint32 GetSize(void) const {return m_pEndMemoryBuffer - m_pBeginMemoryBuffer;}

        /// @brief Retrieves the size of available memory.
        uint32 GetFreeSize(void) const
        {
            uint32 nAvailableMemory = m_pEndAvailableMemory - m_pAvailableMemory;

            // compute all freed memory.
            SFreeMemoryBlock *pNode = (SFreeMemoryBlock*)m_pEndAvailableMemory;
            while(pNode < m_pEndMemoryBuffer)
            {
                nAvailableMemory += pNode->m_nSize;

                pNode += sizeof(SFreeMemoryBlock);
            }

            return nAvailableMemory;
        }

        /// @brief Reset the memory pool.
        void Reset(void)
        {
            m_pAvailableMemory = m_pBeginMemoryBuffer;
            m_pEndAvailableMemory = m_pEndMemoryBuffer;
        }

        /// @brief Allocate some memory from the memory pool.
        /// 
        /// @param _nSize Size to allocate.
        /// @param _nAlign Alignment.
        /// @return Pointer to the allocated memory.
        void *Alloc(const uint32 _nSize, const uint32 _nAlign = 1)
        {            
            void* pAlignedMemory = NULL;

            // try to get a freed memory block.
            if(m_pAvailableMemory != m_pEndMemoryBuffer)
            {
                SFreeMemoryBlock *pNode = (SFreeMemoryBlock*)m_pEndAvailableMemory;
                while(pNode < m_pEndMemoryBuffer)
                {
                    pAlignedMemory = ALIGN(pNode->m_pMemoryBlock + sizeof(uint32), _nAlign);
                    int nAlignedDiffSize = (pNode->m_pMemoryBlock + sizeof(uint32)) - pAlignedMemory;

                    if(pNode->m_nSize + nAlignedDiffSize <= _nSize && pAlignedMemory < pNode->m_pMemoryBlock + pNode->m_nSize)
                    {
                        bool bFragmentation = false;
                        // not same alignment. fragmentation !
                        if(pNode->m_pMemoryBlock + sizeof(uint32) != pAlignedMemory)
                        {
                            bFragmentation = true;
                            pNode->m_nSize = nAlignedDiffSize;
                        }

                        // create a new freed memory block. fragmentation !
                        if(pNode->m_nSize - nAlignedDiffSize > _nSize)
                        {
                            if(bFragmentation)
                            {
                                bFragmentation = true;
                                m_pEndAvailableMemory
                            }
                            else
                            {
                                bFragmentation = true;
                                pNode->m_nSize -= _nSize;
                                pNode->m_pMemoryBlock = pAlignedMemory + _nSize;
                            }                            
                        }

                        // You're so lucky...
                        if(!bFragmentation)
                        {
                            if(pNode == m_pEndAvailableMemory)
                                m_pEndAvailableMemory += sizeof(SFreeMemoryBlock);
                            else
                            {
                                // remove front node.
                                SFreeMemoryBlock *pPrevNode = pNode - sizeof(SFreeMemoryBlock);
                                while(pPrevNode > m_pEndAvailableMemory)
                                {
                                    pNode->m_nSize = pPrevNode->m_nSize;
                                    pNode->m_pMemoryBlock =pPrevNode->m_pMemoryBlock;

                                    pNode -= sizeof(SFreeMemoryBlock);
                                    pPrevNode -= sizeof(SFreeMemoryBlock);
                                }

                                m_pEndAvailableMemory = pNode;
                            }
                        }

                        return pAlignedMemory;
                    }

                    pNode += sizeof(SFreeMemoryBlock);
                }
            }

            // allocated a new memory block.
            SAM_ASSERT((ALIGN(m_pAvailableMemory, _nAlign) + _nSize) >= m_pEndMemoryBuffer, "Unable to allocate more memory");
         
            pAlignedMemory = ALIGN(m_pAvailableMemory + sizeof(uint32), _nAlign);
            ((uint32*)m_pAvailableMemory)[0] = _nSize;
            m_pAvailableMemory = pAlignedMemory + _nSize;

            return pAlignedMemory;
        }

        /// @brief Freed a memory block.
        void Free(void *_pMemoryBlock)
        {
            SAM_ASSERT(_pMemoryBlock != NULL, "Memory block is null");
            SAM_ASSERT(m_pEndAvailableMemory - sizeof(SFreeMemoryBlock) > m_pAvailableMemory, "Unable to freed more memory block");

            SFreeMemoryBlock *pNode = (SFreeMemoryBlock*)(m_pEndAvailableMemory - sizeof(SFreeMemoryBlock));
            pNode->m_pMemoryBlock = _pMemoryBlock - sizeof(uint32);
            pNode->m_nSize = ((uint32*)pNode->m_pMemoryBlock)[0];
        }

    private:
        void *m_pBeginMemoryBuffer;
        void *m_pEndMemoryBuffer;

        void *m_pAvailableMemory;
        void *m_pEndAvailableMemory;

        struct SFreeMemoryBlock
        {
            uint32 m_nSize;       ///< Size of the memory block.
            void *m_pMemoryBlock; ///< Pointer to the free memory block.
        };
    };
}

#endif // __CMEMORY_POOL__
