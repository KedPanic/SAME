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
#ifndef __CVERTEX_ELEMENT_ITERATOR__
#define __CVERTEX_ELEMENT_ITERATOR__

namespace sam
{
    /// @brief Helper class to patch the vertex buffer.
    /// 
    /// CVertexElementIterator vertexEltIt = m_pVertexBuffer->GetIterator();
    /// for(int i = 0; i < vertexEltIt->End(); vertexEltIt++)
    /// {
    ///     vertexEltIt<f32>[0] = pfPosition[i];
    ///     vertexEltIt<f32>[1] = pfColor[i];
    ///     vertexEltIt<f32>[2] = pfCoord[i];
    /// }
    /// vertexEltIt.Close();
    class CVertexElementIterator
    {
        friend class CVertexBuffer;

    public:
        /// @brief Constructor.        
        CVertexElementIterator(CVertexBuffer *p_pVertexBuffer);

        /// @brief Reset.
        void Reset();

        /// @brief Goto the next vertex.
        /// 
        /// @return True if there is no more vertex
        bool Next();

        /// @brief Patch the vertex buffer with new data.
        /// 
        /// @param _pBuffer New data.
        /// @param _nSize Size of the buffer.
        /// 
        /// @remarks
        ///     Be careful, the size of the buffer have to be strictly lesser-equal to the destination.
        void Write(void *_pBuffer, uint32 _nSize);

        /// @brief Release the vertex buffer.
        void Close(void);

		/// @brief Retrieves pointer to the buffer for the specified element.
		/// 
		/// @param p_nIndice Vertex indice.
		/// @param p_nIndex	Index in the buffer.
		/// 
		/// @return Pointer to the buffer.
        template<typename T>
        T &Get(uint32 p_nIndice, uint32 p_nIndex);

		/// @brief Goto the next vertex.
		CVertexElementIterator& operator++();

		/// @brief Retrieves the size of the vertex buffer.
		/// 
		/// @return Size of the vertex buffer.
		uint32 End() const;

    private:
        CVertexBuffer *m_pVertexBuffer; ///< Owner.
        char *m_pBuffer;                ///< Vertex buffer.
        uint32 m_nCurrentIndex;         ///< Current index element.
        uint32 m_nCurrentVertex;        ///< Current vertex.        
    };
}

#endif // __CVERTEX_ELEMENT_ITERATOR__
