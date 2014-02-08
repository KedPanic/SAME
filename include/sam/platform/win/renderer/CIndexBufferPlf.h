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
#ifndef __CINDEX_BUFFER_PLF__
#define __CINDEX_BUFFER_PLF__

namespace sam
{
	/// @brief DX11 index buffer.
	class SAM_RENDERER_API CIndexBuffer : public IAllocated
	{
	public:
		/// @brief Constructor.
		CIndexBuffer();

		/// @brief Destructor.
		~CIndexBuffer();

		/// @brief Initialize the index buffer.
		///
		/// @param p_anIndices Array of indices.
		/// @param p_nNbIndices Number of indices.
		///
		/// @return True if initialized successfully.
		bool Initialize(const uint16 *p_anIndices, uint32 p_nNbIndices);

		/// @brief Retrieves the number of indices.
		/// 
		/// @return The number of indices.
		uint32 GetNbIndices() const {return m_nNbIndices;}

		/// @brief Retrieves the D3D11 index buffer.
		/// 
		/// @return The D3D11 index buffer.
		ID3D11Buffer *GetD3DBuffer() const {return m_pBuffer;}

	private:
		ID3D11Buffer *m_pBuffer;    ///< Index buffer.
		uint32 m_nNbIndices;		///< Number of indices.
	};
}

#endif // __CINDEX_BUFFER_PLF__
