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
#include "widgets/CProjectWizardDialog.h"
#include "CSamBox.h"
#include "CProject.h"
#include "LocalizationIDs.h"

// check if the project location is valid.
bool IsValidProject(wxString p_sPath)
{
	return true;
}

CProjectWizardDialog::CProjectWizardDialog(wxWindow *p_pParent)
{
	wxXmlResource::Get()->LoadObject(this, p_pParent, wxT("CProjectWizard"), wxT("wxDialog"));

	m_pProjectLocation = (wxTextCtrl*)FindWindowById(XRCID("ID_TEXTCTRL_PROJECTLOCATION"));
	m_pRecentProjects = (wxListBox *)FindWindowById(XRCID("ID_LISTBOX_RECENTPROJECTS"));

	CreateEventTable();

	wxString sRecentProjectFile = g_pSamBox->GetHomePath() + "/recentprojects.json";
	if(wxFile::Exists(sRecentProjectFile))
	{
		sam::CJSONSerializer oSerializer(sRecentProjectFile.GetData().AsChar());
		oSerializer.BeginSerialization(true, "projects");
		while(oSerializer.BeginElem("project"))
		{
			wxString sProjectPath = oSerializer.ReadValue("path");
			m_pRecentProjects->AppendString(sProjectPath);
			oSerializer.EndElem();
		}
		oSerializer.EndSerialization();
	}
}

CProjectWizardDialog::~CProjectWizardDialog()
{	
	wxArrayString asRecentProjects = m_pRecentProjects->GetStrings();
	wxString sRecentProjectFile = g_pSamBox->GetHomePath() + "/recentprojects.json";
	sam::CJSONSerializer oSerializer(sRecentProjectFile.GetData().AsChar());
	oSerializer.BeginSerialization(false, "projects");
	for(size_t index = 0; index < asRecentProjects.GetCount(); ++index)
	{
		oSerializer.BeginElem("project");
		oSerializer.WriteValue("path", asRecentProjects.Item(index).GetData().AsChar());
		oSerializer.EndElem();
	}
	oSerializer.EndSerialization();
}

// Create dynamic events.
void CProjectWizardDialog::CreateEventTable()
{
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CProjectWizardDialog::OnBrowseProjectLocation, this, XRCID("ID_BUTTON_BROWSE_PROJECTLOCATION"));
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CProjectWizardDialog::OnCreateProject, this, XRCID("ID_BUTTON_CREATE"));
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CProjectWizardDialog::OnOpenProject, this, XRCID("ID_BUTTON_OPEN_PROJECT"));
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CProjectWizardDialog::OnOpenOtherProject, this, XRCID("ID_BUTTON_OPEN_OTHER_PROJECT"));
}

//////////////////////////////////////////////////////////////////////////
//							EVENT CALLBACK								//
//////////////////////////////////////////////////////////////////////////
void CProjectWizardDialog::OnBrowseProjectLocation(wxCommandEvent &p_oEvent)
{
	while(true)
	{
		wxDirDialog oDirDialog(this, PROJECT_WIZARD_CHOOSE_LOCATION);
		if(oDirDialog.ShowModal() == wxID_OK)
		{
			wxString sPath = oDirDialog.GetPath();
			wxDir oDir(sPath);
			if(oDir.HasFiles() || oDir.HasSubDirs())
			{
				wxMessageBox(PROJECT_WIZARD_HAVE_TO_BE_EMPTY, COMMON_ERROR, wxICON_EXCLAMATION | wxOK);
				continue;
			}
						
			m_pProjectLocation->SetLabel(oDirDialog.GetPath());
		}

		return;
	}	
}

void CProjectWizardDialog::OnCreateProject(wxCommandEvent &p_oEvent)
{
	if(wxDir::Exists(m_pProjectLocation->GetLabel()))
	{
		m_pRecentProjects->Insert(m_pProjectLocation->GetLabel(), 0);

		// Creation configuration.
		CProject::SConfiguration *pConfiguration = SAM_ALLOC(CProject::SConfiguration);

		// Send event.
		CCreateProjectEvent *pEvent = new CCreateProjectEvent();
		pEvent->SetProjectParth(m_pProjectLocation->GetLabel());
		pEvent->SetEventObject(pConfiguration);
		g_pSamBox->QueueEvent(pEvent);

		Close();
	}	
}

void CProjectWizardDialog::OnOpenProject(wxCommandEvent &p_oEvent)
{
	if(!m_pRecentProjects->IsEmpty())
	{
		wxString sSelectedProject = m_pRecentProjects->GetStringSelection();
		if(wxDir::Exists(sSelectedProject))
		{
			// check if selected project is valid.
			if(IsValidProject(sSelectedProject))
			{
				// Send event.
				COpenProjectEvent *pEvent = new COpenProjectEvent();
				pEvent->SetProjectParth(sSelectedProject);
				pEvent->SetEventObject(this);
				g_pSamBox->QueueEvent(pEvent);
			}			
		}
		else
		{
			wxMessageBox(PROJECT_WIZARD_PROJECT_NOT_EXIST, COMMON_ERROR, wxICON_EXCLAMATION | wxOK);

			// remove the project.
			m_pRecentProjects->Delete(m_pRecentProjects->GetSelection());
		}
	}	
}

void CProjectWizardDialog::OnOpenOtherProject(wxCommandEvent &p_oEvent)
{
	wxDirDialog oDirDialog(this, PROJECT_WIZARD_OPEN_EXISTING);
	if(oDirDialog.ShowModal() == wxID_OK)
	{
		wxString sPath = oDirDialog.GetPath();

		// check if selected project is valid.
		if(IsValidProject(sPath))
		{
			m_pRecentProjects->Insert(sPath, 0);

			// Send event.
			COpenProjectEvent *pEvent = new COpenProjectEvent();
			pEvent->SetEventObject(this);
			g_pSamBox->QueueEvent(pEvent);
		}
	}
}
