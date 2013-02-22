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
#include "renderer/SamPCH.h"
#include "renderer/CTexture.h"
#include "renderer/CTextureManager.h"

#ifdef SAM_PLATFORM_WIN
//#   include "renderer/DirectX11/TextureUtilsDX11.h"
#endif

namespace sam
{
	/// @brief Constructor.
	CTextureManager::CTextureManager()
		: m_iCurrentTextureID(0)
	{

	}

	// Destructor.
	CTextureManager::~CTextureManager()
	{
		UnloadAllTextures();
	}

	// Load texture from file.
	CTexture *CTextureManager::LoadTexture(IStream *p_pTexture, ETextureType _eType, ETextureUsage _eUsage)
	{
        SAM_ASSERT(_eUsage != e_TextureUsage_RenderTarget, "Could not create render target from file");

		// Retrieves file buffer.
        CTexture *pTexture = SAM_NEW CTexture;
        if(pTexture->CreateTexture(p_pTexture->Data(), p_pTexture->Size(), _eUsage, _eType))
        {
			pTexture->Release();
            SAM_DELETE pTexture;
            return NULL;
        }

        m_aTextures[m_iCurrentTextureID] = pTexture;
        m_iCurrentTextureID++;

		return NULL;
	}

    // Create empty texture.
    CTexture *CTextureManager::CreateTexture(uint32 p_nWidth, uint32 p_nHeight, ETextureFormat p_eFormat, ETextureType p_eType, ETextureUsage p_eUsage)
    {
        // Create texture.
        CTexture *pTexture = NULL;
        if(p_eUsage == e_TextureUsage_RenderTarget)
        {
            //pTexture = SAM_NEW CRenderTarget;
        }
        else
        {
            CTexture *pTexture = SAM_NEW CTexture;
            if(pTexture->CreateTexture(p_nWidth, p_nHeight, p_eFormat, p_eType, p_eUsage))
            {
                pTexture->Release();
                SAM_DELETE pTexture;
                return NULL;
            }

            m_aTextures[m_iCurrentTextureID] = pTexture;
            m_iCurrentTextureID++;
        }

		return NULL;
    }

	/// @brief Retrieves texture by id.
	/// 
	/// @param _iID The unique id of the texture.
	/// 
	/// @return Pointer to the texture or null if not found.
	CTexture *CTextureManager::GetTexture(uint32 _iID) const
	{
		Textures::const_iterator it = m_aTextures.find(_iID);
		if(it != m_aTextures.end())
			return it->second;

		return 0;
	}


	/// @brief Unload the specified texture.
	/// 
	/// @param _iID The unique id of the texture.
	void CTextureManager::UnloadTexture(uint32 _iID)
	{
		Textures::iterator it = m_aTextures.find(_iID);
		if(it != m_aTextures.end())
		{
			SAM_DELETE it->second;
			m_aTextures.erase(it);
		}
	}

	/// @brief Unload all textures.
	void CTextureManager::UnloadAllTextures()
	{
		Textures::iterator it = m_aTextures.begin(), it_end = m_aTextures.end();
		while(it != it_end)
		{
			SAM_DELETE it->second;
			it = m_aTextures.erase(it);
		}

		m_iCurrentTextureID = 0;
	}

    /// @brief Retrieves pitch from texture format.
    /// 
    /// @param p_eFormat Texture format.
    ///
    /// @return Pitch.
    uint32 CTextureManager::GetPitch(ETextureFormat p_eFormat)
    {
        switch(p_eFormat)
        {
        case e_TextureFormat_R8G8B8:
            return 3;

        case e_TextureFormat_R8G8B8A8:
            return 4;

        case e_TextureFormat_R16G16B16A16F:
            return 8;

        case e_TextureFormat_R32G32B32A32F:
            return 16;

        case e_TextureFormat_BC1:
            return 8;

        case e_TextureFormat_BC3:
        case e_TextureFormat_BC5:
            return 16;
        }

        SAM_ASSERT(0, "Texture format not supported");
        return 0;
    }
}
