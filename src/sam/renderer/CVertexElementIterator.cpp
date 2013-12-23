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
#include "SamRendererPCH.h"
#include "renderer/CVertexElementIterator.h"
#include "renderer/CVertexBuffer.h"

namespace sam
{    
    /// @brief Constructor.
    CVertexElementIterator::CVertexElementIterator(CVertexBuffer *p_pVertexBuffer)
        : m_pVertexBuffer(p_pVertexBuffer), m_pBuffer(NULL), m_nCurrentIndex(0), m_nCurrentVertex(0)
    {
		
    }

    /// @brief Reset.
    void CVertexElementIterator::Reset(void)
    {
        m_nCurrentIndex = 0;
        m_nCurrentVertex = 0;
    }

    // Goto the next vertex.
    bool CVertexElementIterator::Next(void)
    {
        m_nCurrentVertex++;
        if(m_pVertexBuffer->GetNbVertices() <= m_nCurrentVertex)
		{
            return false;
		}

        m_pBuffer += m_pVertexBuffer->GetStride();
        return true;
    }

    // Patch the vertex buffer with new data.
    void CVertexElementIterator::Write(void *_pBuffer, uint32 _nSize)
    {
        SAM_ASSERT(m_pVertexBuffer->GetSize(m_nCurrentIndex) >= _nSize, "Bad size of the vertex element");

        memcpy(m_pBuffer, _pBuffer, _nSize);
        Next();
    }

    // Release the vertex buffer.
    void CVertexElementIterator::Close()
    {
        m_pVertexBuffer->Unmap();
    }

	// Retrieves pointer to the buffer for the specified element.
    template<typename T>
    T &CVertexElementIterator::Get(uint32 p_nIndice, uint32 p_nIndex)
    {
        SAM_ASSERT(p_nIndex > m_pVertexBuffer->GetNbElements(), "Bad index to access to the specified vertex element");

        return ((T*)(m_pBuffer + m_pVertexBuffer->GetOffset(p_nIndex)))[p_nIndex];
    }

	CVertexElementIterator& CVertexElementIterator::operator++()
	{
		Next();

		return *this;
	}

	// Retrieves the size of the vertex buffer. 
	uint32 CVertexElementIterator::End() const
	{
		return m_pVertexBuffer->GetNbVertices();
	}
}
