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
#ifndef __CVERTEX_BUFFER_PLF__
#define __CVERTEX_BUFFER_PLF__

#include "renderer/CVertexElementIterator.h"

namespace sam
{
    /// @brief DX11 vertex buffer.
    class SAM_RENDERER_API CVertexBuffer : public IAllocated
    {
    public:
        /// @brief Constructor.
        CVertexBuffer(void);

        /// @brief Destructor.
        ~CVertexBuffer(void);

        /// @brief Initialize the vertex buffer.
        ///
        /// @param _nNbElements Number of elements.
        /// @param _nNbVertices Number of vertex.
        ///
        /// @return True if initialized successfully.
        bool Initialize(const SVertexDeclaration *_pVertexDeclarations, uint32 _nNbElements, uint32 _nNbVertices);

        /// @brief Retrieves the stride of the vertex buffer.
        /// 
        /// @return Stride of the vertex buffer.
        uint32 GetStride(void) const;

        /// @brief Retrieves the number of vertices.
        /// 
        /// @return The number of vertices.
        uint32 GetNbVertices(void) const;

        /// @brief Retrieves the number of different elements.
        /// 
        /// @return The number of different elements.
        uint32 GetNbElements(void) const;

        /// @brief Retrieves the semantic by index.
        /// 
        /// @param _nIndex Index of the element.
        /// 
        /// @return The semantic or VS_Nb if not found.
        EVertexSemantic GetSemantic(uint32 _nIndex) const;

        /// @brief Retrieves type id.
        /// 
        /// @param _nIndex Index of the element.
        /// 
        /// @return Type ID.
        ETypeID GetTypeID(uint32 _nIndex) const;

        /// @brief Retrieves the offset by index.
        /// 
        /// @param _nIndex Index of the element.
        /// 
        /// @return The offset or 0 if not found.
        uint32 GetOffset(uint32 _nIndex) const;

        /// @brief Retrieves size of the element.
        ///
        /// @param _nIndex Index of the element.
        /// 
        /// @return The size or 0.
        uint32 GetSize(uint32 _nIndex) const;

        /// @brief Retrieves the number of component.
        /// 
        /// @param _nIndex Index of the element.
        ///
        /// @return The number of component.
        uint32 GetNbComponent(uint32 _nIndex) const;

        /// @brief Lock vertex buffer.
        /// 
        /// @param _nIndex Index of the vertex buffer.
        /// @param _pBuffer Vertex buffer.
        /// @param _nSize Size to write.
        /// 
        /// @return True if it mapped successfully.
        bool MapWrite(uint32 _nIndex, void *_pBuffer, uint32 _nSize);

        /// @brief Lock vertex buffer.
        /// 
        /// @param _nIndex Index of the vertex buffer.
        /// @param _pBuffer Vertex buffer.
        /// @param _nSize Size to read.
        /// 
        /// @return True if it mapped successfully.
        bool MapRead(uint32 _nIndex, void *_pBuffer, uint32 _nSize);

        /// @brief Unlock vertex buffer.
        void Unmap(void);

        /// @brief Retrieves vertex element iterator.
        /// 
        /// @return Pointer to the vertex element iterator.
        CVertexElementIterator *GetIterator(void);

        /// @brief Retrieves the D3D11 Vertex buffer.
        /// 
        /// @return The D3D11 vertex buffer.
        ID3D11Buffer *GetD3DBuffer(void) const {return m_pBuffer;}

    private:
        ID3D11Buffer *m_pBuffer;    ///< Vertex buffer.
        uint32 m_nNbVertices;       ///< Number of vertices.
        uint32 m_nNbElements;       ///< Number of element per vertex.
        uint32 m_nStride;           ///< Stride to one vertex buffer.

        SVertexDeclaration *m_pVertexDeclaration;

        CVertexElementIterator m_Iterator;
    };
}
#endif // __CVERTEX_BUFFER_PLF__
