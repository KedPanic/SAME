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
#include "SamBoxPCH.h"
#include "resources/CTextureResource.h"

#include "CSamBox.h"
#include "CProject.h"
#include "CPlatform.h"

// Constructor.
CTextureResource::CTextureResource(const sam::String &p_sName, const sam::String &p_sPath)
	: IResource(p_sName, p_sPath), m_pEngineTexture(NULL)
{
	// set to default the metadata.
	m_oMetadata.m_eTextureWrap = sam::e_TextureWrap_Clamp;
	m_oMetadata.m_eTextureFilter = e_TextureFilter_Bilinear;
	m_oMetadata.m_bGenerateMipMap = true;
	m_oMetadata.m_eMipMapFilter = e_MipMapFilter_Box;

	// add the platform settings.
	CProject *pProject = g_pSamBox->GetCurrentProject();		
	const CProject::SConfiguration &oConfiguration = pProject->GetConfiguration();		
	for(uint32 nIndex = 0; nIndex < oConfiguration.m_aPlatforms.size(); ++nIndex)
	{
		CPlatform *pPlatform = oConfiguration.m_aPlatforms[nIndex];

		STextureMetadata::STargetSettings oTargetSetting;
		oTargetSetting.m_nTargetId = pPlatform->GetId();
		oTargetSetting.m_nMaxSize = 1024;
		oTargetSetting.m_nFormat = 0;

		m_oMetadata.m_aTargetSettings.push_back(oTargetSetting);
	}
}

CTextureResource::~CTextureResource()
{
	if(m_pEngineTexture)
	{
		Unload();
	}
}

// Load resource.
bool CTextureResource::Load()
{
	return false;
}

// Unload resource.
bool CTextureResource::Unload()
{
	return false;
}

// Serialize the object
void CTextureResource::Read(sam::ISerializer *p_pContext)
{
	p_pContext->BeginElem("textureSettings");
	{
		m_oMetadata.m_eTextureWrap = (sam::ETextureWrap)p_pContext->ReadIntValue("WrapMode");
		m_oMetadata.m_eTextureFilter = (ETextureFilter)p_pContext->ReadIntValue("FilterMode");
	}
	p_pContext->EndElem();

	p_pContext->BeginElem("mipmaps");
	{
		p_pContext->ReadValue("enable", m_oMetadata.m_bGenerateMipMap);
		m_oMetadata.m_eMipMapFilter = (EMipMapFilter)p_pContext->ReadIntValue("filter");
	}
	p_pContext->EndElem();

	p_pContext->BeginElem("targetSettings");
	{
		while(p_pContext->BeginElem("target"))
		{
			STextureMetadata::STargetSettings oTargetSettings;
			oTargetSettings.m_nTargetId = p_pContext->ReadIntValue("target");
			oTargetSettings.m_nMaxSize = p_pContext->ReadIntValue("maxSize");
			oTargetSettings.m_nFormat = p_pContext->ReadIntValue("format");

			p_pContext->EndElem();
		}
	}
	p_pContext->EndElem();
}

// Serialize the object
void CTextureResource::Write(sam::ISerializer *p_pContext)
{
	p_pContext->BeginElem("textureSettings");
	{
		p_pContext->WriteValue("WrapMode", m_oMetadata.m_eTextureWrap);
		p_pContext->WriteValue("FilterMode", m_oMetadata.m_eTextureFilter);
	}
	p_pContext->EndElem();

	p_pContext->BeginElem("mipmaps");
	{
		p_pContext->WriteValue("enable", m_oMetadata.m_bGenerateMipMap);
		p_pContext->WriteValue("filter", m_oMetadata.m_eMipMapFilter);
	}
	p_pContext->EndElem();

	p_pContext->BeginElem("targetSettings");
	{
		for(uint32 nIndex = 0; nIndex < m_oMetadata.m_aTargetSettings.size(); ++nIndex)
		{
			STextureMetadata::STargetSettings &oTargetSettings = m_oMetadata.m_aTargetSettings[nIndex];

			p_pContext->BeginElem("target");
			{
				p_pContext->WriteValue("target", oTargetSettings.m_nTargetId);
				p_pContext->WriteValue("maxSize", oTargetSettings.m_nMaxSize);
				p_pContext->WriteValue("format", oTargetSettings.m_nFormat);
			}
			p_pContext->End();
		}
	}
	p_pContext->EndElem();
}

// Update the metadata.
void CTextureResource::SetMetadata(STextureMetadata &p_oMetadata)
{
	m_oMetadata = p_oMetadata;
}