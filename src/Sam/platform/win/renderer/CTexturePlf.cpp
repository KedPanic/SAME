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
#include "renderer/CTexture.h"
#include "renderer/CRenderWindow.h"
#include "renderer/CTextureManager.h"
#include "renderer/TextureUtilsPlf.h"

namespace sam
{
    // Constructor.
    CTexture::CTexture()
        : m_pTexture(NULL), m_pShaderResourceView(NULL), m_iID(-1), m_iWidth(0), m_iHeight(0), m_eType(e_Texture_Unknown) {}

    // Destructor.
    CTexture::~CTexture()
    {
    }

    // Create texture from buffer.
    bool CTexture::CreateTexture(void *p_pBuffer, uint32 p_nSize, ETextureUsage p_eUsage, ETextureType p_eType)
    {
        SAM_ASSERT(p_pBuffer != NULL, "Memory buffer is null.");

        // retrieves image information.
        D3DX11_IMAGE_INFO imageInfo;
        HRESULT hResult = D3DX11GetImageInfoFromMemory(p_pBuffer, p_nSize, NULL, &imageInfo, NULL);
        if(hResult != S_OK)
        {
            g_Env->pRenderWindow->LogError(hResult);
            return false;
        }
        m_iWidth = imageInfo.Width;
        m_iHeight = imageInfo.Height;
        m_nMipLevels = imageInfo.MipLevels;

        m_eType = p_eType;
        switch(m_eType)
        {
        case e_Texture_1D:
            break;

        case e_Texture_2D:
        case e_Texture_CubeMap:
            return CreateTexture2D(p_pBuffer, p_eUsage, imageInfo.Format);

        case e_Texture_3D:
            break;

        default:
            SamLogError("Unsupported texture type %d", m_eType);
        };        

        return false;
    }

    // Create empty texture.
    bool CTexture::CreateTexture(uint32 p_nWidth, uint32 p_nHeight, ETextureFormat p_eFormat, ETextureType p_eType, ETextureUsage p_eUsage)
    {
		return false;
    }

    // Release the texture.
    void CTexture::Release(void)
    {
        if(m_pTexture)
        {
            m_pTexture->Release();
            m_pTexture = NULL;
        }

        g_Env->pTextureManager->UnloadTexture(m_iID);
    }

    // Map the texture for CPU access.
    uint8 *CTexture::Map(ETextureMap p_eAccess, uint32 p_nLevel /*= 0*/, uint32 p_nSide /*= 0*/) 
    {
        SAM_ASSERT(m_pTexture != NULL, "Texture is not loaded");

        D3D11_MAPPED_SUBRESOURCE mappedSubResource;
        // Set access.
        D3D11_MAP map = D3D11_MAP_READ;
        if(p_eAccess == e_TextureMap_Write)
		{
            map = D3D11_MAP_WRITE;
		}
        else if(p_eAccess == e_TextureMap_ReadWrite)
		{
            map = D3D11_MAP_READ_WRITE;
		}

        HRESULT hResult = g_Env->pRenderWindow->GetD3DContext()->Map(m_pTexture, p_nLevel + (p_nSide * m_nMipLevels), map, D3D11_MAP_FLAG_DO_NOT_WAIT, &mappedSubResource);
        if(hResult != S_OK)
        {
            g_Env->pRenderWindow->LogError(hResult);
            return NULL;
        }

        return (uint8*)mappedSubResource.pData;
    }

    // Unmap the texture data and re-enable the GPU's access.
    void CTexture::Unmap(uint32 p_nLevel /*= 0*/, uint32 p_nSide /*= 0*/)
    {
        SAM_ASSERT(m_pTexture != NULL, "Texture is ot loaded");

         g_Env->pRenderWindow->GetD3DContext()->Unmap(m_pTexture, p_nLevel + (p_nSide * m_nMipLevels));
    }

    // Create 2D texture.
    bool CTexture::CreateTexture2D(void *p_pBuffer, ETextureUsage p_eUsage, DXGI_FORMAT p_eFormat)
    {
        // setup texture.
        D3D11_TEXTURE2D_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
        desc.ArraySize  = 1;
        desc.Format     = p_eFormat;
        desc.Height     = m_iHeight;
        desc.Width      = m_iWidth;
        desc.MipLevels  = m_nMipLevels;
        desc.MiscFlags  = 0;  
        desc.BindFlags  = D3D11_BIND_SHADER_RESOURCE;

		D3D11_SHADER_RESOURCE_VIEW_DESC oShaderResourceViewDesc;
		ZeroMemory(&oShaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		oShaderResourceViewDesc.Format = p_eFormat;

        if(p_eUsage == e_TextureUsage_Dynamic)
        {
            desc.Usage          = D3D11_USAGE_DYNAMIC;
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;          
        }
        else
        {
            desc.Usage          = p_eUsage == e_TextureUsage_Default?D3D11_USAGE_DEFAULT:D3D11_USAGE_IMMUTABLE;
            desc.CPUAccessFlags = 0;               
        }

        // its a cubemap.		
        if(m_eType == e_Texture_CubeMap)
        {
            desc.MiscFlags |= D3D11_RESOURCE_MISC_TEXTURECUBE;
            desc.ArraySize = 6;
			
			oShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
			oShaderResourceViewDesc.TextureCube.MipLevels = m_nMipLevels;
        }
		else
		{
			oShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			oShaderResourceViewDesc.Texture2D.MipLevels = m_nMipLevels;
			oShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		}
		
        SamLog("Have to implement Texture Settings Quality");
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;

		// compute pitch
		uint8 nBytePerPixel = GetBitsPerPixel(p_eFormat) / 8;
		uint32 nPitch = 0;
		for(uint32 level = 1; level <= m_nMipLevels; ++level)
		{
			nPitch += (m_iWidth / level) * nBytePerPixel;
		}

        // set data.
        D3D11_SUBRESOURCE_DATA *initialData = SAM_ALLOC_ARRAY(D3D11_SUBRESOURCE_DATA, m_nMipLevels);
		ZeroMemory(&initialData[0], sizeof(D3D11_SUBRESOURCE_DATA));        
		initialData[0].pSysMem = p_pBuffer;
		initialData[0].SysMemPitch = nPitch;
		for(uint32 level = 1; level < m_nMipLevels; ++level)
		{
			ZeroMemory(&initialData[level], sizeof(D3D11_SUBRESOURCE_DATA));

			initialData[level].pSysMem = ((uint8*)initialData[level - 1].pSysMem) + ((m_iWidth / level) * nBytePerPixel);
			initialData[level].SysMemPitch = nPitch;
		}
        HRESULT hResult =  g_Env->pRenderWindow->GetD3DDevice()->CreateTexture2D(&desc, initialData, (ID3D11Texture2D**)&m_pTexture);
		SAM_FREE_ARRAY(initialData);
		if(hResult == S_OK)
		{
			// Create shader view.			
			HRESULT hResult =  g_Env->pRenderWindow->GetD3DDevice()->CreateShaderResourceView(m_pTexture, &oShaderResourceViewDesc, &m_pShaderResourceView);
			if(hResult != S_OK)
			{
				g_Env->pRenderWindow->LogError(hResult);
			}

			return true;
		}
		
		g_Env->pRenderWindow->LogError(hResult);
		return false;
    }
}
