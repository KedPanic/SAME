//===========================================
// Copyright (C) 2013-2014 Stone Age Machine
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
#include "SamBox.h"
#include "CProject.h"
#include "CSamBox.h"
#include "CPlatform.h"
#include "resources/CFolder.h"

// Default constructor.
CProject::CProject(const sam::String &p_sName, const sam::String &p_sPath)
    : m_sName(p_sName), m_sPath(p_sPath), m_bIsDirty(false), m_pPackagesFolder(NULL)
{
    m_pPackagesFolder = SAM_NEW CFolder("Packages", m_sPath + "/packages/", "");

	// send the event.
    // sam::g_Env->pSignalManager->QueueSignal(new CCreateFolderSignal(m_pPackagesFolder));
}

/// @brief Destructor.
CProject::~CProject()
{
    SAM_FREE(m_pPackagesFolder);
}

// Initialize the project.
bool CProject::Initialize(SConfiguration *p_pConfig)
{
    m_oConfiguration.m_eMode = p_pConfig->m_eMode;
    m_oConfiguration.m_sSceneManager = p_pConfig->m_sSceneManager;
    m_oConfiguration.m_sLastScene = p_pConfig->m_sLastScene;

    // copy supported platform.
    Platforms::iterator oPlatformIt = p_pConfig->m_aPlatforms.begin();
    Platforms::iterator oPlatformItEnd = p_pConfig->m_aPlatforms.end();
    while(oPlatformIt != oPlatformItEnd)
    {
        m_oConfiguration.m_aPlatforms.push_back(*oPlatformIt);
        ++oPlatformIt;
    }

	return true;
}

// Serialize the object
void CProject::Read(sam::ISerializer *p_pContext)
{
    m_oConfiguration.m_eMode = (EMode)p_pContext->ReadIntValue("editor_mode");
    char *sSceneManager = p_pContext->ReadValue("scene_manager");
    m_oConfiguration.m_sSceneManager = sSceneManager;
    SAM_FREE_ARRAY(sSceneManager);
    char *sLastScene = p_pContext->ReadValue("last_scene");
    m_oConfiguration.m_sSceneManager = sLastScene;
    SAM_FREE_ARRAY(sLastScene);

    while(p_pContext->BeginElem("platform"))
    {
        // retrieves the supported platforms
        uint32 nId = ~0;
        p_pContext->ReadValue("id", nId);
        const char *pPlatformName = p_pContext->ReadValue("name");

        CPlatform *pPlatform = g_pSamBox->GetPlatform(nId);
        if(pPlatform)
        {
            m_oConfiguration.m_aPlatforms.push_back(pPlatform);
        }
        else
        {
            QMessageBox oMsgBox(QMessageBox::Critical, "SamBox - Error", QString("Unable to found platform configuration for the platform '%1'").arg(pPlatformName), QMessageBox::Ok);
            oMsgBox.exec();
        }

        p_pContext->EndElem();
    }
}

// Serialize the object
void CProject::Write(sam::ISerializer *p_pContext)
{
	Platforms::iterator oPlatformIt = m_oConfiguration.m_aPlatforms.begin();
	Platforms::iterator oPlatformItEnd = m_oConfiguration.m_aPlatforms.end();
	while(oPlatformIt != oPlatformItEnd)
	{
        p_pContext->WriteValue("editor_mode", m_oConfiguration.m_eMode);
        p_pContext->WriteValue("scene_manager", m_oConfiguration.m_sSceneManager.c_str());
        p_pContext->WriteValue("last_scene", m_oConfiguration.m_sLastScene.c_str());

		p_pContext->BeginElem("platform");
        p_pContext->WriteValue("id", (*oPlatformIt)->GetId());
		p_pContext->WriteValue("name", (*oPlatformIt)->GetName().c_str());        
		p_pContext->EndElem();

        ++oPlatformIt;
    }
}

// Create new package.
CFolder *CProject::CreatePackage(const sam::String &p_sName)
{
	// create the folder.
    CFolder *pFolder = SAM_NEW CFolder(p_sName, m_pPackagesFolder->GetPath() + p_sName, p_sName, m_pPackagesFolder);

	// add the package to the root folder.
    m_pPackagesFolder->AddResource(pFolder);

	// send the event.
    // sam::g_Env->pSignalManager->QueueSignal(new CResourceCreatedSignal(pFolder));
    SAM_UNIMPLEMENTED;

	return pFolder;
}

// Load the project.
void CProject::LoadProject()
{
    sam::String sFilename = m_sPath + "/project.cfg";
    sam::CJSONSerializer oSerializer(sFilename.c_str());
    oSerializer.BeginSerialization(true, "project");
    Read(&oSerializer);
    oSerializer.EndSerialization();
}

// Save the project.
void CProject::SaveProject()
{
    sam::String sFilename = m_sPath + "/project.cfg";
    sam::CJSONSerializer oSerializer(sFilename.c_str());
    oSerializer.BeginSerialization(false, "project");
    Write(&oSerializer);
    oSerializer.EndSerialization();
}


// Helper method to create a new project.
CProject *CreateNewProject(const sam::String &p_sName, const sam::String &p_sPath, CProject::SConfiguration *p_pConfig)
{
    // create folder.
    sam::CreateDirectory(p_sPath.c_str());
    sam::CreateDirectory((p_sPath + "/packages").c_str());
    sam::CreateDirectory((p_sPath + "/build").c_str());
    for(uint32 i = 0; i < p_pConfig->m_aPlatforms.size(); ++i)
    {
        sam::CreateDirectory((p_sPath + "/build/" + p_pConfig->m_aPlatforms[i]->GetName()).c_str());
    }

    // copie base project.
#if defined(SAM_PLATFORM_WIN)
#else
    SAM_UNIMPLEMTED;
#endif

    // create project.
    CProject *pProject = new CProject(p_sName, p_sPath);
    pProject->Initialize(p_pConfig);
    pProject->SaveProject();

    return pProject;
}
