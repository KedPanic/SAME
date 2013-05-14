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
#include "widgets/aui/boxAuiNotebook.h"

#include "widgets/CMainFrame.h"
#include "widgets/CProjectWizardDialog.h"

#include "CSamBox.h"
#include "CProject.h"

// Create menu bar.
wxMenuBar *CreateMenuBar()
{
	/*
	- FILE
	  Open World
	  Save World
	  ----------
	  New Project
	  Open Project
	  Save Project
	  ----------
	  Exit
	*/
	wxMenu *pMenuFile = new wxMenu();
	pMenuFile->Append(CMainFrame::e_Menu_OpenWorld, wxT("Open World"));
	pMenuFile->Append(CMainFrame::e_Menu_SaveWorld, wxT("Save World"));
	pMenuFile->AppendSeparator();
	pMenuFile->Append(CMainFrame::e_Menu_NewProject, wxT("New Project"));
	pMenuFile->Append(CMainFrame::e_Menu_OpenProject, wxT("Open Project"));
	pMenuFile->Append(CMainFrame::e_Menu_SaveProject, wxT("Save Project"));
	pMenuFile->AppendSeparator();
	pMenuFile->Append(CMainFrame::e_Menu_Exit, wxT("Exit"));

	wxMenuBar *pMenuBar = new wxMenuBar();
	pMenuBar->Append(pMenuFile, wxT("File"));
	return pMenuBar;
}

// Create unique ID.
const long CMainFrame::ID_MAIN_NOTEBOOK = wxNewId();
const long CMainFrame::ID_RIGHT_NOTEBOOK = wxNewId();
const long CMainFrame::ID_BOTTOM_NOTEBOOK = wxNewId();

// Constructor.
CMainFrame::CMainFrame(wxWindow *p_pParent, wxWindowID p_nId /*= -1*/)
{
	wxXmlResource::Get()->LoadObject(this, p_pParent, wxT("CMainFrame"), wxT("wxFrame"));
	Maximize(true);

	SetMenuBar(CreateMenuBar());

	m_pAuiManager = SAM_ALLOC(wxAuiManager)(this, wxAUI_MGR_DEFAULT);

	// Main notebook.
	m_pMainNotebook = SAM_ALLOC(boxAuiNotebook)(this, ID_MAIN_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);	
	wxAuiPaneInfo oPaneInfo;
	oPaneInfo.Name(wxT("MainNotebook"));
	oPaneInfo.CenterPane();
	oPaneInfo.Caption(wxT("Test"));
	m_pAuiManager->AddPane(m_pMainNotebook, oPaneInfo);

	// Right notebook.
	m_pRightNotebook = SAM_ALLOC(boxAuiNotebook)(this, ID_RIGHT_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
	wxAuiPaneInfo oRightPaneInfo;
	oRightPaneInfo.Name(wxT("RightNotebook"));
	oRightPaneInfo.CaptionVisible(true);
	oRightPaneInfo.PinButton(true);
	oRightPaneInfo.Right();
	oRightPaneInfo.MinSize(150, 150);
	oRightPaneInfo.Caption(wxT("Properties"));
	m_pAuiManager->AddPane(m_pRightNotebook, oRightPaneInfo);

	// Bottom notebook.
	m_pBottomNotebook = SAM_ALLOC(boxAuiNotebook)(this, ID_BOTTOM_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
	wxAuiPaneInfo oBottomPaneInfo;
	oBottomPaneInfo.Name(wxT("BottomNotebook"));
	oBottomPaneInfo.CaptionVisible(true);
	oBottomPaneInfo.PinButton(true);
	oBottomPaneInfo.Bottom();
	oBottomPaneInfo.MinSize(150, 150);
	oBottomPaneInfo.Caption(wxT("Tools"));
	m_pAuiManager->AddPane(m_pBottomNotebook, oBottomPaneInfo);

	m_pAuiManager->Update();

	CreateEventTable();
}

CMainFrame::~CMainFrame()
{
	m_pAuiManager->UnInit();	
}

// Create dynamic events.
void CMainFrame::CreateEventTable()
{
	// Menu
	Bind(wxEVT_COMMAND_MENU_SELECTED, &CMainFrame::OnNewProject, this, e_Menu_NewProject);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &CMainFrame::OnOpenProject, this, e_Menu_OpenProject);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &CMainFrame::OnSaveProject, this, e_Menu_SaveProject);
}

// Serialize the object
void CMainFrame::Read(sam::ISerializer *p_pContext)
{

}

// Serialize the object
void CMainFrame::Write(sam::ISerializer *p_pContext)
{

}

//////////////////////////////////////////////////////////////////////////
//							EVENT CALLBACK								//
//////////////////////////////////////////////////////////////////////////
void OpenProjectWizard(CMainFrame *pMainFrame, int p_nPage)
{
	CProjectWizardDialog *pProjectWizard = new CProjectWizardDialog(pMainFrame);
	wxNotebook *pNotebook = (wxNotebook*)pProjectWizard->FindWindowById(XRCID("ID_NOTEBOOK1"));
	pNotebook->ChangeSelection(p_nPage);
	if(pProjectWizard->ShowModal() == wxID_CANCEL)
	{
		
	}

	pProjectWizard->Destroy();
}

void CMainFrame::OnNewProject(wxCommandEvent &p_oEvent)
{
	OpenProjectWizard(this, 1);	
}

void CMainFrame::OnOpenProject(wxCommandEvent &p_oEvent)
{
	OpenProjectWizard(this, 0);
}

void CMainFrame::OnSaveProject(wxCommandEvent &p_oEvent)
{

}