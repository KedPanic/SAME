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
#include "CSamBox.h"
#include "CProject.h"
#include "resources/CFolder.h"
#include "widgets/CSplashScreen.h"
#include "widgets/CMainFrame.h"
#include "widgets/CProjectWizardDialog.h"

#include "CInitializingThread.h"
#include "CGaugeThread.h"

#include <common/SamModuleInit.h>

#include "CPlatform.h"

wxIMPLEMENT_APP(CSamBox);

CSamBox *g_pSamBox = NULL;
// Constructor.
CSamBox::CSamBox()
	: m_pProject(NULL)
{
	g_pSamBox = this;

	// Create bind event.
	Bind(boxEVT_INIT_COMPLETED, &CSamBox::OnInitCompleted, this);
	Bind(boxEVT_OPEN_PROJECT, &CSamBox::OnOpenProject, this);
	Bind(boxEVT_CREATE_PROJECT, &CSamBox::OnCreateProject, this);
	Bind(boxEVT_LOADING_COMPLETED, &CSamBox::OnLoadingCompleted, this);	
}

CSamBox::~CSamBox()
{
}

bool CSamBox::OnInit()
{	
	m_sDataFolder = wxT("../data/sambox/");		

	// Initialize user data.
	if(wxDir::Exists(GetHomePath()) == false)
	{
		wxDir::Make(GetHomePath());
	}

	wxImage::AddHandler(new wxPNGHandler);

	// Create splash screen.
	wxBitmap oBitmap;	
	if(!oBitmap.LoadFile(m_sDataFolder + wxT("images/splash.png"), wxBITMAP_TYPE_PNG))
	{
		wxMessageBox(wxT("Unable to load splash screen image '" + m_sDataFolder + "images/splash.png'"));
		return false;
	}	
	CSplashScreen *pSplashScreen = new CSplashScreen(oBitmap, wxSPLASH_CENTRE_ON_SCREEN, 0, NULL, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER | wxSTAY_ON_TOP);
	SetTopWindow(pSplashScreen->GetSplashWindow());

	// Create thread.
	CInitializingThread *pThread = new CInitializingThread(pSplashScreen);
	if(pThread->Create() != wxTHREAD_NO_ERROR)
	{
		wxMessageBox(wxT("Unable to run create thread initializer"));
		return false;
	}

	if(pThread->Run() != wxTHREAD_NO_ERROR)
	{
		wxMessageBox(wxT("Unable to run thread initializer"));
		return false;
	}	

	return true;
}

int CSamBox::OnExit()
{
	// Shutdown Sam Engine.
	sam::ShutdownCommon();

	return 0;
}

// Called when the app is idle. We use the idle time to update the engine.
void CSamBox::OnIdle(wxIdleEvent &p_oEvent)
{
	sam::g_Env->pSignalManager->Dispatch();
}

// Add a supported platform could be used by a project.
void CSamBox::AddPlatform(const wxString &p_sPlatformFilename)
{
	CPlatform *pPlatform = SAM_NEW CPlatform;
	pPlatform->Initialize(p_sPlatformFilename.c_str().AsChar());

	AddPlatform(pPlatform);
}

// Add a supported platform could be used by a project.
void CSamBox::AddPlatform(CPlatform *p_pPlatform)
{
	SAM_ASSERT(p_pPlatform != NULL, "Platform is null");

	m_aPlatforms.push_back(p_pPlatform);
}

//////////////////////////////////////////////////////////////////////////
//									RESOURCES							//
//////////////////////////////////////////////////////////////////////////
// Create a new package with a unique name.
CFolder *CSamBox::CreateNewPackage()
{
	// create a unique folder name.
	wxString sBaseName(COMMON_NEW_FOLDER);
	wxString sFolderName(COMMON_NEW_FOLDER);
	uint32 nNumber = 0;

	while(wxFileName::Exists(m_pProject->GetAssetFolder()->GetPath() + sFolderName))
	{
		nNumber++;
		sFolderName = sBaseName + " " << nNumber;
	}

	// create package.
	sam::String sFinalFolderName = sFolderName;
	return m_pProject->CreatePackage(sFinalFolderName);
}

// Rename package. if the package already exist, it will be renamed automatically.
void CSamBox::RenamePackage(CPackage *p_pPackage, const char *p_sName)
{

}

// Close current project.
bool CSamBox::CloseCurrentProject()
{
	if(!m_pProject)
	{
		return true;
	}


	if(m_pProject->IsDirty())
	{
		switch(wxMessageBox(wxT("Do you want to save your project ?"), wxT(""), wxCANCEL | wxYES_NO))
		{
		case wxYES:
			
			break;

		case wxCANCEL:
			return false;
		}
	}

	// delete the project.
	SAM_DELETE m_pProject;
	m_pProject = NULL;
	return true;
}

//////////////////////////////////////////////////////////////////////////
//							EVENT CALLBACK								//
//////////////////////////////////////////////////////////////////////////
// Called when initializing finished.
void CSamBox::OnInitCompleted( CInitCompletedEvent &p_oEvent)
{
	CPlatform plf;
	sam::String sPlatformFilename = m_sDataFolder + "platforms/generic.json";
	plf.Initialize(sPlatformFilename.c_str());

	// Create the main window.
	CMainFrame *pFrame = new CMainFrame(NULL);
	pFrame->Show();
	SetTopWindow(pFrame);

	// Close the splash screen.
	CSplashScreen *pSplashScreen = (CSplashScreen *)p_oEvent.GetEventObject();
	pSplashScreen->Close();

	// Check if there is a recent project.
	wxCommandEvent *pEvent = NULL;
	wxString sRecentProjectFile = GetHomePath() + "/recentprojects.json";
	if(wxFile::Exists(sRecentProjectFile))
	{
		pEvent = new wxCommandEvent(wxEVT_COMMAND_MENU_SELECTED, CMainFrame::e_Menu_OpenProject);
	}
	else
	{
		pEvent = new wxCommandEvent(wxEVT_COMMAND_MENU_SELECTED, CMainFrame::e_Menu_NewProject);		
	}
	pFrame->GetEventHandler()->QueueEvent(pEvent);

	//
	Bind(wxEVT_IDLE, &CSamBox::OnIdle, this);
}

// Called when user request to open a project.
void CSamBox::OnOpenProject(COpenProjectEvent &p_oEvent)
{
	if(CloseCurrentProject())
	{
		CProjectWizardDialog *pProjectWizard = (CProjectWizardDialog*)p_oEvent.GetEventObject();

		sam::String sProjectName = wxFileName::FileName(p_oEvent.GetProjectPath()).GetName().ToStdString();
		m_pProject = SAM_NEW CProject(sProjectName, p_oEvent.GetProjectPath().ToStdString());

		// Create loading thread.
		CGaugeThread *pThread = new CGaugeThread(m_pProject);
		if(pThread->Create() == wxTHREAD_NO_ERROR && pThread->Run() == wxTHREAD_NO_ERROR)
		{
			pProjectWizard->Close();
		}
		else
		{
			wxMessageBox(wxT("Unable to run thread loading"));
		}
	}
}

// Called when user request to create a project.
void CSamBox::OnCreateProject(CCreateProjectEvent &p_oEvent)
{
	if(CloseCurrentProject())
	{
 		CProject::SConfiguration *pConfiguration = (CProject::SConfiguration*)p_oEvent.GetEventObject();
 
		sam::String sProjectName = wxFileName::FileName(p_oEvent.GetProjectPath()).GetName().ToStdString();
		m_pProject = SAM_NEW CProject(sProjectName, p_oEvent.GetProjectPath().ToStdString());
		m_pProject->Initialize(pConfiguration);
	}
}

// Called when the project is completed
void CSamBox::OnLoadingCompleted(CLoadingCompletedEvent &p_oEvent)
{

}
