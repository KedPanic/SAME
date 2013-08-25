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
#include "renderer/TextureUtilsPlf.h"
#include "renderer/CRenderWindow.h"

namespace sam
{
//     /// @brief Load a texture from file name.
//     /// 
//     /// @param _sFilename Name of the file.
//     /// @return True if no error occured.
//     ID3D11Resource *LoadTextureFromFile(const char *_sFilename)
//     {
//         ID3D11Resource *pTexture = NULL;
//         HRESULT hResult = D3DX11CreateTextureFromFile(g_pRenderWindow->GetD3DDevice(), _sFilename, NULL, NULL, &pTexture, NULL);
//         if(hResult != S_OK)
//         {
//             g_pRenderWindow->LogError(hResult, _sFilename);
//             return NULL;
//         }
// 
// 
//         return pTexture;
//     }

    // Load a texture from memory buffer.
    ID3D11Resource *CreateTextureFromMemory(const void *p_pBuffer, const uint32 p_nSize)
    {
        ID3D11Resource *pTexture = NULL;
        HRESULT hResult = D3DX11CreateTextureFromMemory(g_Env->pRenderWindow->GetD3DDevice(), p_pBuffer, p_nSize, NULL, NULL, &pTexture, NULL);
        if(hResult != S_OK)
        {
            g_Env->pRenderWindow->LogError(hResult);
            return NULL;
        }


        return pTexture;
    }


    // Retrieves Sam Engine texture format.
    ETextureFormat GetFormat(DXGI_FORMAT p_eDGIFormat)
    {
        switch(p_eDGIFormat)
        {
        case DXGI_FORMAT_R32G32B32A32_FLOAT:
            return e_TextureFormat_R32G32B32A32F;

        case DXGI_FORMAT_R16G16B16A16_FLOAT:
            return e_TextureFormat_R16G16B16A16F;

        case DXGI_FORMAT_R8G8B8A8_TYPELESS:
        case DXGI_FORMAT_R8G8B8A8_UNORM:
            return e_TextureFormat_R8G8B8A8;

        case DXGI_FORMAT_BC1_UNORM:
            return e_TextureFormat_BC1;

        case DXGI_FORMAT_BC3_UNORM:
            return e_TextureFormat_BC3;

        case DXGI_FORMAT_BC5_UNORM:
            return e_TextureFormat_BC5;

        default:
            SAM_ASSERT(0, "Unsupported texture format");
            return e_TextureFormat_Unknown;
        }
    }

	// Retrieves bits per pixel from DirectX texture format.
	uint32 GetBitsPerPixel(DXGI_FORMAT p_eDGIFormat)
	{
		switch(p_eDGIFormat)
		{
		case DXGI_FORMAT_R32G32B32A32_FLOAT:
			return 128;

		case DXGI_FORMAT_R16G16B16A16_FLOAT:
			return 64;

		case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		case DXGI_FORMAT_R8G8B8A8_UNORM:
			return 32;

		case DXGI_FORMAT_BC1_UNORM:
			return 4;

		case DXGI_FORMAT_BC3_UNORM:
		case DXGI_FORMAT_BC5_UNORM:
			return 32;

		default:
			SAM_ASSERT(0, "Unsupported texture format");
			return 0;
		}
	}
}
