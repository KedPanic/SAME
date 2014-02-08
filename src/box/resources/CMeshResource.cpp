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
#include "resources/CMeshResource.h"

#include "CSamBox.h"
#include "CProject.h"
#include "CPlatform.h"

// Constructor.
CMeshResource::CMeshResource(const sam::String &p_sName, const sam::String &p_sPath)
	: IResource(p_sName, p_sPath)
{
	// set to default the metadata.
	

	// add the platform settings.
	CProject *pProject = g_pSamBox->GetCurrentProject();		
	const CProject::SConfiguration &oConfiguration = pProject->GetConfiguration();		
	for(uint32 nIndex = 0; nIndex < oConfiguration.m_aPlatforms.size(); ++nIndex)
	{
		CPlatform *pPlatform = oConfiguration.m_aPlatforms[nIndex];

		SMeshMetadata::STargetSettings oTargetSetting;
		oTargetSetting.m_nTargetId = pPlatform->GetId();

		m_oMetadata.m_aTargetSettings.push_back(oTargetSetting);
	}
}

CMeshResource::~CMeshResource()
{
	//if(m_pEngineMesh)
	{
		Unload();
	}
}

// Load resource.
bool CMeshResource::Load()
{
	return false;
}

// Unload resource.
bool CMeshResource::Unload()
{
	return false;
}

// Serialize the object
void CMeshResource::Read(sam::ISerializer *p_pContext)
{	
	p_pContext->BeginElem("targetSettings");
	{
		while(p_pContext->BeginElem("target"))
		{
			SMeshMetadata::STargetSettings oTargetSettings;
			oTargetSettings.m_nTargetId = p_pContext->ReadIntValue("target");

			p_pContext->EndElem();
		}
	}
	p_pContext->EndElem();
}

// Serialize the object
void CMeshResource::Write(sam::ISerializer *p_pContext)
{
	p_pContext->BeginElem("targetSettings");
	{
		for(uint32 nIndex = 0; nIndex < m_oMetadata.m_aTargetSettings.size(); ++nIndex)
		{
			SMeshMetadata::STargetSettings &oTargetSettings = m_oMetadata.m_aTargetSettings[nIndex];

			p_pContext->BeginElem("target");
			{
				p_pContext->WriteValue("target", oTargetSettings.m_nTargetId);
			}
			p_pContext->End();
		}
	}
	p_pContext->EndElem();
}

// Update the metadata.
void CMeshResource::SetMetadata(SMeshMetadata &p_oMetadata)
{
	m_oMetadata = p_oMetadata;
}
