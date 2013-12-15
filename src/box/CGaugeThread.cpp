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
#include "CGaugeThread.h"
#include "CProject.h"
#include "resources/CFolder.h"
#include "resources/CResourceManager.h"
#include "CSamBox.h"

// Constructor.
CGaugeThread::CGaugeThread(CProject *p_pProject)
	: m_pProject(p_pProject), m_pProgressDialog(NULL)
{

}

wxThread::ExitCode CGaugeThread::Entry()
{
	m_pProgressDialog = new wxProgressDialog(LOADING_TITLE + ":" + m_pProject->GetProjectName(), LOADING_PARSING_FOLDER);

	// read the project configuration.
	String sFilename = m_pProject->GetProjectPath() + "/project.cfg";
	sam::CJSONSerializer oSerializer(sFilename.c_str());
	oSerializer.BeginSerialization(true, "project");
	m_pProject->Read(&oSerializer);
	oSerializer.EndSerialization();
	
	ParseFolder(m_pProject->GetAssetFolder());
	// send event to select the asset folder.
	sam::g_Env->pSignalManager->QueueSignal(new CProjectInitializedSignal(m_pProject));
	sam::g_Env->pSignalManager->QueueSignal(new CResourceSelected(m_pProject->GetAssetFolder()));

	// send event.
	CLoadingCompletedEvent *pEvent = new CLoadingCompletedEvent();
	g_pSamBox->QueueEvent(pEvent);

	delete m_pProgressDialog;
	return 0;
}

void CGaugeThread::ParseFolder(CFolder *p_pParentFolder)
{
	m_pProgressDialog->Update(0, LOADING_PARSING_FOLDER + p_pParentFolder->GetName());
	wxDir oCurrentDir(p_pParentFolder->GetPath());

	// retrieves files.
	wxString sFile;
	for(bool bContinue = oCurrentDir.GetFirst(&sFile, wxEmptyString, wxDIR_FILES); bContinue; bContinue = oCurrentDir.GetNext(&sFile))
	{
		wxFileName oFilename(sFile);
		if(oFilename.GetExt() != "metadata")
		{
			String sFilename = oFilename.GetName();
			String sFullPath = oCurrentDir.GetNameWithSep() + sFile;

			// we create the resource but it won't be loaded here.
			IResource *pResource = g_pResourceManager->Create(sFilename, sFullPath);
			if(pResource != NULL)
			{
				p_pParentFolder->AddResource(pResource);
			}
		}		
	}

	// retrieves sub-folder.
	wxString sSubFolder;
	for(bool bContinue = oCurrentDir.GetFirst(&sSubFolder, wxEmptyString, wxDIR_DIRS); bContinue; bContinue = oCurrentDir.GetNext(&sSubFolder))
	{
		String sDirname = sSubFolder;		

		CFolder *pSubFolder = NULL;
		if(p_pParentFolder->IsRoot())
		{
			pSubFolder = m_pProject->CreatePackage(sDirname);
		}
		else
		{
			String sFullDirname = oCurrentDir.GetNameWithSep() + sSubFolder;

			pSubFolder = SAM_NEW CFolder(sDirname, sFullDirname, p_pParentFolder);
			p_pParentFolder->AddResource(pSubFolder);
		}		

		ParseFolder(pSubFolder);
	}
}