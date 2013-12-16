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
#include "renderer/CVertexBuffer.h"
#include "renderer/CRenderWindow.h"

namespace sam
{
    uint8 GetSizeByType(ETypeID _eType)
    {
        switch(_eType)
        {
        case e_Type_Int:
        case e_Type_UInt:
            return 4;

        case e_Type_Short:
        case e_Type_UShort:
            return 2;

        case e_Type_Char:
        case e_Type_UChar:
            return 1;

        case e_Type_Float:
        case e_Type_Half:
        default:
            return 4;
        }
    }

    D3D11_MAP GetDX11Map(EVertexUsage _eUsage)
    {
        switch(_eUsage)
        {
        case VU_Read_Only:
            return D3D11_MAP_READ;

        case VU_Dynamic:
            return D3D11_MAP_READ_WRITE;

        case VU_Write_Only:
        default:
            return D3D11_MAP_WRITE_DISCARD;
        }
    }

    /// @brief Constructor.
    CVertexBuffer::CVertexBuffer(void)
        : m_pBuffer(NULL), m_nNbVertices(0), m_nNbElements(0), m_nStride(0), m_pVertexDeclaration(NULL)
    {
    }

    /// @brief Destructor.
    CVertexBuffer::~CVertexBuffer(void)
    {
        if(m_pBuffer)
        {
            m_pBuffer->Release();
        }

        if(m_pVertexDeclaration)
        {
            SAM_FREE_ARRAY(m_pVertexDeclaration);
        }
    }

    /// @brief Initialize the vertex buffer.
    ///
    /// @param _nNbElements Number of elements.
    /// @param _nNbVertices Number of vertex.
    ///
    /// @return True if initialized successfully.
    bool CVertexBuffer::Initialize(const SVertexDeclaration *_pVertexDeclarations, uint32 _nNbElements, uint32 _nNbVertices)
    {
        SAM_ASSERT(m_pBuffer == NULL, "Vertex buffer already allocated");
        SAM_ASSERT(_pVertexDeclarations != NULL, "Vertex declaration is null");

        m_nNbVertices = _nNbVertices;
        m_nNbElements = _nNbElements;

        // Compute the stride.
        m_nStride = _pVertexDeclarations[m_nNbElements - 1].m_nOffset;
        m_nStride += GetSizeByType(_pVertexDeclarations[m_nNbElements - 1].m_eType) * _pVertexDeclarations[m_nNbElements - 1].m_nNbComponents;

        // Setup the vertex buffer.
        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufferDesc.ByteWidth = m_nStride * m_nNbVertices;
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        HRESULT hResult = g_Env->pRenderWindow->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_pBuffer);
        if(hResult != S_OK)
        {
            g_Env->pRenderWindow->LogError(hResult);
            return false;
        }

        // Memorize the configuration.
        m_pVertexDeclaration = SAM_ALLOC_ARRAY(SVertexDeclaration, m_nNbElements);
        memcpy(m_pVertexDeclaration, _pVertexDeclarations, sizeof(SVertexDeclaration) * m_nNbElements);

        return true;
    }

    /// @brief Retrieves the stride of the vertex buffer.
    /// 
    /// @return Stride of the vertex buffer.
    uint32 CVertexBuffer::GetStride(void) const
    {
        return m_nStride;
    }

    /// @brief Retrieves the number of vertices.
    /// 
    /// @return The number of vertices.
    uint32 CVertexBuffer::GetNbVertices(void) const
    {
        return m_nNbVertices;
    }

    /// @brief Retrieves the number of different elements.
    /// 
    /// @return The number of different elements.
    uint32 CVertexBuffer::GetNbElements(void) const
    {
        return m_nNbElements;
    }

    /// @brief Retrieves the semantic by index.
    /// 
    /// @param _nIndex Index of the element.
    /// 
    /// @return The semantic or VS_Nb if not found.
    EVertexSemantic CVertexBuffer::GetSemantic(uint32 _nIndex) const
    {
        SAM_ASSERT(_nIndex < m_nNbElements, "Index is out of range");

        return m_pVertexDeclaration[_nIndex].m_eSemantic;
    }

    /// @brief Retrieves type id.
    /// 
    /// @param _nIndex Index of the element.
    /// 
    /// @return Type ID.
    ETypeID CVertexBuffer::GetTypeID(uint32 _nIndex) const
    {
        SAM_ASSERT(_nIndex < m_nNbElements, "Index is out of range");

        return m_pVertexDeclaration[_nIndex].m_eType;
    }

    /// @brief Retrieves the offset by index.
    /// 
    /// @param _nIndex Index of the element.
    /// 
    /// @return The offset or 0 if not found.
    uint32 CVertexBuffer::GetOffset(uint32 _nIndex) const
    {
        SAM_ASSERT(_nIndex < m_nNbElements, "Index is out of range");

        return m_pVertexDeclaration[_nIndex].m_nOffset;
    }

    /// @brief Retrieves size of the element.
    ///
    /// @param _nIndex Index of the element.
    /// 
    /// @return The size or 0.
    uint32 CVertexBuffer::GetSize(uint32 _nIndex) const
    {
        SAM_ASSERT(_nIndex < m_nNbElements, "Index is out of range");

        return GetSizeByType(m_pVertexDeclaration[_nIndex].m_eType) * m_pVertexDeclaration[_nIndex].m_nNbComponents;
    }

    /// @brief Retrieves the number of component.
    /// 
    /// @param _nIndex Index of the element.
    ///
    /// @return The number of component.
    uint32 CVertexBuffer::GetNbComponent(uint32 _nIndex) const
    {
        SAM_ASSERT(_nIndex < m_nNbElements, "Index is out of range");

        return m_pVertexDeclaration[_nIndex].m_nNbComponents;
    }

    /// @brief Lock vertex buffer.
    /// 
    /// @param _nIndex Index of the vertex buffer.
    /// @param _pBuffer Vertex buffer.
    /// @param _nSize Size to write.
    /// 
    /// @return True if it mapped successfully.
    bool CVertexBuffer::MapWrite(uint32 _nIndex, void *_pBuffer, uint32 _nSize)
    {
        SAM_ASSERT(_pBuffer != NULL, "Buffer is null");
        SAM_ASSERT(_nIndex < m_nNbVertices, "Index is out of range");

        // Lock the vertex buffer.
        D3D11_MAPPED_SUBRESOURCE subressource;
        ZeroMemory(&subressource, sizeof(D3D11_MAPPED_SUBRESOURCE));

        HRESULT hResult = g_Env->pRenderWindow->GetD3DContext()->Map(m_pBuffer, _nIndex, GetDX11Map(VU_Write_Only), 0, &subressource);
        if(hResult != S_OK)
        {
            g_Env->pRenderWindow->LogError(hResult);
            return false;
        }

        memcpy(subressource.pData, _pBuffer, _nSize);
        Unmap();

        return true;
    }

    /// @brief Lock vertex buffer.
    /// 
    /// @param _nIndex Index of the vertex buffer.
    /// @param _pBuffer Vertex buffer.
    /// @param _nSize Size to read.
    /// 
    /// @return True if it mapped successfully.
    bool CVertexBuffer::MapRead(uint32 _nIndex, void *_pBuffer, uint32 _nSize)
    {
        SAM_ASSERT(_pBuffer != NULL, "Buffer is null");
        SAM_ASSERT(_nIndex < m_nNbVertices, "Index is out of range");

        // Lock the vertex buffer.
        D3D11_MAPPED_SUBRESOURCE subressource;
        ZeroMemory(&subressource, sizeof(D3D11_MAPPED_SUBRESOURCE));

        HRESULT hResult = g_Env->pRenderWindow->GetD3DContext()->Map(m_pBuffer, _nIndex, GetDX11Map(VU_Read_Only), 0, &subressource);
        if(hResult != S_OK)
        {
            g_Env->pRenderWindow->LogError(hResult);
            return false;
        }

        _pBuffer = subressource.pData;
        return true;
    }

    /// @brief Unlock vertex buffer.
    void CVertexBuffer::Unmap(void)
    {
        g_Env->pRenderWindow->GetD3DContext()->Unmap(m_pBuffer, 0);
    }
}
