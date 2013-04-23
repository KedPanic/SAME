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
    CVertexElementIterator::CVertexElementIterator()
        : m_pVertexBuffer(NULL), m_pBuffer(NULL), m_nCurrentIndex(0), m_nCurrentVertex(0)
    {
    }

    /// @brief Reset.
    void CVertexElementIterator::Reset(void)
    {
        m_nCurrentIndex = 0;
        m_nCurrentVertex = 0;
    }

    /// @brief Goto the next vertex.
    /// 
    /// @return True if there is no more vertex
    bool CVertexElementIterator::Next(void)
    {
        m_nCurrentVertex++;
        if(m_pVertexBuffer->GetNbVertices() <= m_nCurrentVertex)
            return true;

        m_pBuffer += m_pVertexBuffer->GetStride();
        return false;
    }

    /// @brief Patch the vertex buffer with new data.
    /// 
    /// @param _pBuffer New data.
    /// @param _nSize Size of the buffer.
    /// 
    /// @remarks
    ///     Be careful, the size of the buffer have to be strictly lesser-equal to the destination.
    void CVertexElementIterator::Write(void *_pBuffer, uint32 _nSize)
    {
        SAM_ASSERT(m_pVertexBuffer->GetSize(m_nCurrentIndex) >= _nSize, "Bad size of the vertex element");

        memcpy(m_pBuffer, _pBuffer, _nSize);
        Next();
    }

    /// @brief Release the vertex buffer.
    void CVertexElementIterator::Close(void)
    {
        m_pVertexBuffer->Unmap();
    }

    template<typename T>
    T *CVertexElementIterator::operator[](uint32 _nIndex)
    {
        SAM_ASSERT(_nIndex > m_pVertexBuffer->GetNbElements(), "Bad index to access to the specified vertex element");

        return (T*)(m_pBuffer + m_pVertexBuffer->GetOffset(_nIndex));
    }

    /// @brief Set owner.
    ///
    /// @param _pVertexBuffer Owner.
    void CVertexElementIterator::SetOwner(CVertexBuffer *_pVertexBuffer)
    {
        m_pVertexBuffer = _pVertexBuffer;
    }
}
