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
#ifndef __ETEXTURE__
#define __ETEXTURE__

namespace sam
{
    /// @enum Texture type.
    enum ETextureType
    {
        e_Texture_1D,
        e_Texture_2D,
        e_Texture_3D,
        e_Texture_CubeMap,

        e_Texture_Unknown,
    };

    /// @enum Texture format.
    enum ETextureFormat
    {
        e_TextureFormat_Unknown,
        e_TextureFormat_R8G8B8,			///< 24 bits
        e_TextureFormat_R8G8B8A8,		///< 32 bits
        e_TextureFormat_R16G16B16A16F,	///< 64 bits
        e_TextureFormat_R32G32B32A32F,	///< 128 bits

        e_TextureFormat_BC1,			///< DirectX compressed format.
        e_TextureFormat_BC3,			///< DirectX compressed format.
        e_TextureFormat_BC5,			///< DirectX compressed format.

        e_TextureFormat_D24S8,			///< Depth buffer.
    };

    /// @enum Texture usage.
    enum ETextureUsage
    {
        e_TextureUsage_Default,         ///< Read/Write access by GPU.
        e_TextureUsage_Immutable,       ///< Read only by GPU.
        e_TextureUsage_Dynamic,         ///< Read only by GPU and write only by CPU.
        e_TextureUsage_RenderTarget,
    };

    /// @enum Texture mapping access.
    enum ETextureMap
    {
        e_TextureMap_Read,            ///< Read access.
        e_TextureMap_Write,           ///< Write access.
        e_TextureMap_ReadWrite,       ///< R/W access.
    };	
}

#endif // __ETEXTURE__
