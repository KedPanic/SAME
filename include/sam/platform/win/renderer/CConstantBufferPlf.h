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
#ifndef __CCONSTANT_BUFFER_PLF_
#define __CCONSTANT_BUFFER_PLF_

namespace sam
{
	/// @brief DX11 constant buffer.
	class SAM_RENDERER_API CConstantBuffer : public IAllocated
	{
	public:
		/// @brief Constructor.
		CConstantBuffer();

		/// @brief Destructor.
		~CConstantBuffer();

		/// @brief Initialize the constant buffer.
		///
		/// @param p_nSize Constant buffer size requested
		///
		/// @return True if initialized successfully.
		bool Initialize(uint32 p_nSize);

		/// @brief Lock constant buffer.
		/// 
		/// @param p_pBuffer constant buffer.
		/// @param p_nSize Size to write.
		/// 
		/// @return True if it mapped successfully.
		bool MapWrite(void *p_pBuffer, uint32 p_nSize);

		/// @brief Lock constant buffer.
		/// 
		/// @param p_pBuffer constant buffer.
		/// @param p_nSize Size to read.
		/// 
		/// @return True if it mapped successfully.
		bool MapRead(void *p_pBuffer, uint32 p_nSize);

		/// @brief Unlock constant buffer.
		void Unmap();

		/// @brief Retrieves the D3D11 constant buffer.
		/// 
		/// @return The D3D11 constant buffer.
		ID3D11Buffer *GetD3DBuffer() const {return m_pBuffer;}

	private:
		ID3D11Buffer *m_pBuffer;    ///< Constant buffer.
	};
}

#endif // __CCONSTANT_BUFFER_PLF_
