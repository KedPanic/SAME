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
#include "widgets/CSplashScreen.h"
#include "widgets/CMainFrame.h"
#include "widgets/CProjectWizardDialog.h"

#include <common/SamModuleInit.h>

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

	return true;
}

//////////////////////////////////////////////////////////////////////////
//							EVENT CALLBACK								//
//////////////////////////////////////////////////////////////////////////
// Called when initializing finished.
void CSamBox::OnInitCompleted( CInitCompletedEvent &p_oEvent)
{
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
}

// Called when user request to open a project.
void CSamBox::OnOpenProject(COpenProjectEvent &p_oEvent)
{
	if(!CloseCurrentProject())
	{

	}
}

// Called when user request to create a project.
void CSamBox::OnCreateProject(CCreateProjectEvent &p_oEvent)
{
	if(!CloseCurrentProject())
	{
		CProject::SConfiguration *pConfiguration = (CProject::SConfiguration*)p_oEvent.GetEventObject();

		m_pProject = SAM_NEW(CProject);
		m_pProject->Initialize(pConfiguration);
	}
}
