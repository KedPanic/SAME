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
#ifndef __TEXTURE_LOADER__
#define __TEXTURE_LOADER__

namespace sam
{
    /// @brief Load a texture from memory buffer.
    /// 
    /// @param p_pBuffer Memory buffer.
    /// @param p_nSize Buffer size.
	///
    /// @return True if no error occurred.
    SAM_RENDERER_API inline ID3D11Resource *CreateTextureFromMemory(const void *p_pBuffer, const uint32 p_nSize);

    /// @brief Retrieves Sam Engine texture format.
    /// 
    /// @param p_eDGIFormat DirectX texture format.
	///
    /// @return Sam Engine texture format.
    SAM_RENDERER_API inline ETextureFormat GetFormat(DXGI_FORMAT p_eDGIFormat);

    /// @brief Retrieves bits per pixel from DirectX texture format.
    /// 
    /// @param p_eDGIFormat DirectX texture format.
	///
    /// @return BPP.
    SAM_RENDERER_API inline uint32 GetBitsPerPixel(DXGI_FORMAT p_eDGIFormat);
}

#endif // __TEXTURE_LOADER__
