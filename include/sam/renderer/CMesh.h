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
#ifndef __CMESH__
#define __CMESH__

namespace sam
{
	/// @enum Mesh version
	enum EMeshVersion
	{
		e_MeshVersion_0 = 0,
	};

	class SAM_RENDERER_API CMesh : public IAllocated
	{
	public:
		CMesh();
		~CMesh();

		/// @brief Create mesh from memory buffer.
		/// 
		/// @param p_pBuffer Memory buffer.
		/// @param p_nSize Buffer size.
		/// 
		/// @return true if no error occurred.
		bool CreateMesh(uint8 *p_pBuffer, uint32 p_nSize);

		/// @brief Retrieves the vertex buffer.
		/// 
		/// @return the vertex buffer.
		CVertexBuffer *GetVertexBuffer() const {return m_pVertexBuffer;}

		/// @brief Retrieves the index buffer.
		/// 
		/// @return the index buffer.
		CIndexBuffer *GetIndexBuffer() const {return m_pIndexBuffer;}

	private:
		CVertexBuffer *m_pVertexBuffer; ///< Vertices.
		CIndexBuffer *m_pIndexBuffer;	///< Indices.
	};
}

#endif // __CMESH__
