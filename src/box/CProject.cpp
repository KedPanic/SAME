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
#include "CProject.h"
#include "CSamBox.h"
#include "CPlatform.h"
#include "resources/CFolder.h"

// Default constructor.
CProject::CProject(const String &p_sName, const String &p_sPath)
	: m_sName(p_sName), m_sPath(p_sPath), m_bIsDirty(false), m_pAssetFolder(NULL)
{
	m_pAssetFolder = SAM_NEW CFolder("Packages", m_sPath + "/assets/");

	// send the event.
	// sam::g_Env->pSignalManager->QueueSignal(new CCreateFolderSignal(m_pAssetFolder));

	// add the PC platform (it is the default platform).
	SAM_TRAP(g_pSamBox->GetSupportedPlatforms().empty() == false);
	CPlatform *pPlatform = *g_pSamBox->GetSupportedPlatforms().begin();
	SAM_TRAP(pPlatform->GetName() == "PC");
	m_oConfiguration.m_aPlatforms.push_back(pPlatform);
}

/// @brief Destructor.
CProject::~CProject()
{
	SAM_FREE(m_pAssetFolder);
}

// Initialize the project.
bool CProject::Initialize(SConfiguration *p_pConfig)
{
	return true;
}

// Serialize the object
void CProject::Read(sam::ISerializer *p_pContext)
{

}

// Serialize the object
void CProject::Write(sam::ISerializer *p_pContext)
{
	Platforms::iterator oPlatformIt = m_oConfiguration.m_aPlatforms.begin();
	Platforms::iterator oPlatformItEnd = m_oConfiguration.m_aPlatforms.end();
	while(oPlatformIt != oPlatformItEnd)
	{
		p_pContext->BeginElem("platform");
		p_pContext->WriteValue("id", (*oPlatformIt)->GetId());
		p_pContext->WriteValue("name", (*oPlatformIt)->GetName().c_str());
		p_pContext->EndElem();
	}			
}

// Create new package.
CFolder *CProject::CreatePackage(const String &p_sName)
{
	// create the folder.
	CFolder *pFolder = SAM_NEW CFolder(p_sName, m_pAssetFolder->GetPath() + p_sName, m_pAssetFolder);

	// add the package to the root folder.
	m_pAssetFolder->AddResource(pFolder);

	// send the event.
	sam::g_Env->pSignalManager->QueueSignal(new CResourceCreatedSignal(pFolder));

	return pFolder;
}