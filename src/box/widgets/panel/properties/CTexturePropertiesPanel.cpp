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
#include "widgets/panel/properties/CTexturePropertiesPanel.h"

#include "CSamBox.h"
#include "CProject.h"
#include "CPlatform.h"
#include "exporter/CExporterManager.h"
#include "exporter/IExporter.h"
#include "resources/CTextureResource.h"

CTexturePropertiesPanel::CTexturePropertiesPanel(wxWindow *p_pParent)
	: m_pTextureResource(NULL)
{
	wxXmlResource::Get()->LoadObject(this, p_pParent, wxT("CTexturePropertiesPanel"), wxT("wxPanel"));

	// Common
	m_pTextureWrapMode = (wxComboBox*)FindWindowById(XRCID("ID_COMBOBOX_WRAPMODE"));
	m_pTextureWrapMode->Append(wxT("Mirror")); // sam::e_TextureWrap_Mirror
	m_pTextureWrapMode->Append(wxT("Repeat")); // sam::e_TextureWrap_Repeat
	m_pTextureWrapMode->Append(wxT("Clamp"));  // sam::e_TextureWrap_Clamp

	m_pTextureFilterMode = (wxComboBox*)FindWindowById(XRCID("ID_COMBOBOX_FILTERMODE"));
	m_pTextureFilterMode->Append(wxT("Point"));		// e_TextureFilter_Point
	m_pTextureFilterMode->Append(wxT("Bilinear"));	// e_TextureFilter_Bilinear
	m_pTextureFilterMode->Append(wxT("Trilinear")); // e_TextureFilter_Trilinear

	// Mip Maps
	m_pMipMapGenerate = (wxCheckBox *)FindWindowById(XRCID("ID_CHECKBOX_GENERATE"));
	m_pMipMapGenerate->SetValue(true);

	m_pMipMapFilter = (wxComboBox*)FindWindowById(XRCID("ID_COMBOBOX_MIPMAPFILTER"));
	m_pMipMapFilter->Append(wxT("Box"));		// e_MipMapFilter_Box
	m_pMipMapFilter->Append(wxT("Triangle"));	//	e_MipMapFilter_Triangle
	m_pMipMapFilter->Append(wxT("Kaiser"));		// e_MipMapFilter_Kaiser

	m_pTargetSettings = (wxNotebook*)FindWindowById(XRCID("ID_NOTEBOOK_TARGET"));

	CreateEventTable();
}

void CTexturePropertiesPanel::CreateEventTable()
{	
	Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &CTexturePropertiesPanel::OnTextureWrap, this, XRCID("ID_COMBOBOX_WRAPMODE"));
	Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &CTexturePropertiesPanel::OnTextureFilter, this, XRCID("ID_COMBOBOX_FILTERMODE"));
	Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &CTexturePropertiesPanel::OnMipMapGenerate, this, XRCID("ID_CHECKBOX_GENERATE"));
	Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &CTexturePropertiesPanel::OnMipMapFilter, this, XRCID("ID_COMBOBOX_MIPMAPFILTER"));
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CTexturePropertiesPanel::OnApply, this, XRCID("ID_BUTTON_APPLY"));	

	sam::g_Env->pSignalManager->Connect(e_CustomSignal_ProjectInitialized, this, &CTexturePropertiesPanel::OnNewProject);
}

// set the current texture resource
void CTexturePropertiesPanel::SetTextureResource(CTextureResource *p_pTextureResource) 
{	
	m_pTextureResource = p_pTextureResource;
	const STextureMetadata &oMetadata = m_pTextureResource->GetMetadata();
	m_oLocalMetadata = oMetadata;

	// update the properties panel.
	m_pTextureWrapMode->SetSelection(oMetadata.m_eTextureWrap);
	m_pTextureFilterMode->SetSelection(oMetadata.m_eTextureFilter);
	m_pMipMapGenerate->SetValue(oMetadata.m_bGenerateMipMap);
	m_pMipMapFilter->SetSelection(oMetadata.m_eMipMapFilter);

	for(uint32 nIndex = 0; nIndex < oMetadata.m_aTargetSettings.size(); ++nIndex)
	{
		int nSelectionIndex = 7;
		uint32 nMaxSize = oMetadata.m_aTargetSettings[nIndex].m_nMaxSize;
		while(nMaxSize > 32 /* min size */)
		{
			nMaxSize >>= 1;
			--nSelectionIndex;
		}

		m_aTargetSettings[nIndex]->m_pSizeMax->SetSelection(7 - nSelectionIndex);
		m_aTargetSettings[nIndex]->m_pFormat->SetSelection(oMetadata.m_aTargetSettings[nIndex].m_nFormat);
	}
}

void CTexturePropertiesPanel::CreateTargetSettingPage(CPlatform *p_pPlatform)
{
	STargetSettings *pTargetSetting = SAM_ALLOC(STargetSettings);
	pTargetSetting->m_nTargetId = p_pPlatform->GetId();

	// create a new page.
	wxPanel *pPanel = new wxPanel(m_pTargetSettings, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	wxFlexGridSizer *pFlexGridSizer = new wxFlexGridSizer(2);
	pFlexGridSizer->AddGrowableCol(1);

	// create max size options.
	wxStaticText *pMaxSizeLabel = new wxStaticText(pPanel, wxID_ANY, wxT("Max Size"));
	pFlexGridSizer->Add(pMaxSizeLabel, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

	sam::String sSizeMaxId = "ID_COMBOBOX_SIZEMAX_" + p_pPlatform->GetName();
	int nSizeMaxId = XRCID(sSizeMaxId.c_str());
	pTargetSetting->m_pSizeMax = new wxComboBox(pPanel, nSizeMaxId, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
	for(uint32 nMaxSize = 32; nMaxSize <= 4096; nMaxSize <<= 1)
	{
		wxString sValue;
		sValue << nMaxSize;
		pTargetSetting->m_pSizeMax->Append(sValue);		
	}
	pTargetSetting->m_pSizeMax->SetSelection(0);
	Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &CTexturePropertiesPanel::OnSizeMax, this, nSizeMaxId);
	pFlexGridSizer->Add(pTargetSetting->m_pSizeMax, 1, wxALL | wxEXPAND, 5);

	// create format options.
	wxStaticText *pFormatLabel = new wxStaticText(pPanel, wxID_ANY, wxT("Format"));
	pFlexGridSizer->Add(pFormatLabel, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

	sam::String sFormatId = "ID_COMBOBOX_FORMAT_" + p_pPlatform->GetName();
	int nFormatId = XRCID(sFormatId.c_str());
	pTargetSetting->m_pFormat = new wxComboBox(pPanel, nFormatId, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
	IExporter *pExporter = g_pExporterManager->GetExporter(e_ResourceType_Texture, p_pPlatform->GetExporterName(e_ResourceType_Texture).c_str());
 	const IExporter::SFormat *pFormats = pExporter->GetFormat();
 	for(uint32 nIndex = 0; nIndex < pExporter->GetNbSupportedFormats(); ++nIndex)
 	{
 		pTargetSetting->m_pFormat->Append(pFormats[nIndex].m_sReadableName, (void*)&pFormats[nIndex].m_nFormat); 		
 	}
	pTargetSetting->m_pFormat->SetSelection(0);
	Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &CTexturePropertiesPanel::OnExportFormat, this, nFormatId);
	pFlexGridSizer->Add(pTargetSetting->m_pFormat, 1, wxALL | wxEXPAND, 5);

	// set the sizer.	
	pPanel->SetSizer(pFlexGridSizer);
	pFlexGridSizer->Layout();

	// add the created page.
	m_pTargetSettings->AddPage(pPanel, p_pPlatform->GetName().c_str());

	m_aTargetSettings.push_back(pTargetSetting);
}

void CTexturePropertiesPanel::OnNewProject(sam::ISignal *p_pSignal)
{
	CProjectInitializedSignal *pProjectInit = (CProjectInitializedSignal *)p_pSignal;
	CProject *pProject = pProjectInit->GetProject();

	const Platforms &aPlatforms = pProject->GetConfiguration().m_aPlatforms;
	Platforms::const_iterator oPlatformIt = aPlatforms.begin();
	Platforms::const_iterator oPlatformItEnd = aPlatforms.end();
	while(oPlatformIt != oPlatformItEnd)
	{
		CreateTargetSettingPage((*oPlatformIt));

		++oPlatformIt;
	}	
}

//////////////////////////////////////////////////////////////////////////
// UI EVENTS
//////////////////////////////////////////////////////////////////////////
void CTexturePropertiesPanel::OnTextureWrap(wxCommandEvent &p_oEvent)
{
	m_oLocalMetadata.m_eTextureWrap = (sam::ETextureWrap)p_oEvent.GetSelection();
}

void CTexturePropertiesPanel::OnTextureFilter(wxCommandEvent &p_oEvent)
{
	m_oLocalMetadata.m_eTextureFilter = (ETextureFilter)p_oEvent.GetSelection();
}

void CTexturePropertiesPanel::OnMipMapGenerate(wxCommandEvent &p_oEvent)
{
	m_oLocalMetadata.m_bGenerateMipMap = p_oEvent.IsChecked();

	m_pMipMapFilter->Enable(p_oEvent.IsChecked());
}

void CTexturePropertiesPanel::OnMipMapFilter(wxCommandEvent &p_oEvent)
{
	m_oLocalMetadata.m_eMipMapFilter = (EMipMapFilter)p_oEvent.GetSelection();
}

void CTexturePropertiesPanel::OnSizeMax(wxCommandEvent &p_oEvent)
{
	m_oLocalMetadata.m_aTargetSettings[m_pTargetSettings->GetSelection()].m_nMaxSize = p_oEvent.GetSelection();
}

void CTexturePropertiesPanel::OnExportFormat(wxCommandEvent &p_oEvent)
{
	m_oLocalMetadata.m_aTargetSettings[m_pTargetSettings->GetSelection()].m_nFormat = p_oEvent.GetSelection();
}

void CTexturePropertiesPanel::OnApply(wxCommandEvent &p_oEvent)
{
	CProject *pProject = g_pSamBox->GetCurrentProject();

	// save the settings.
	m_pTextureResource->SetMetadata(m_oLocalMetadata);

	sam::String sMetadataPath = m_pTextureResource->GetPath() + ".metadata";
	sam::CJSONSerializer oSerializer(sMetadataPath.c_str());
	oSerializer.BeginSerialization(false, sMetadataPath.c_str());
	m_pTextureResource->Write(&oSerializer);
	oSerializer.EndSerialization();

	TargetSettings::iterator oTargetSettingIt = m_aTargetSettings.begin();
	TargetSettings::iterator oTargetSettingItEnd = m_aTargetSettings.end();
	while(oTargetSettingIt != oTargetSettingItEnd)
	{		
		wxFileName oNativeFilenamePath(pProject->GetProjectPath() + "/build/PC/");
		sam::String sDestination = oNativeFilenamePath.GetFullPath().ToStdString();
		uint32 nFormat = *(uint32*)(*oTargetSettingIt)->m_pFormat->GetClientData((*oTargetSettingIt)->m_pFormat->GetCurrentSelection());

		g_pExporterManager->RequestExport(m_pTextureResource, sDestination, nFormat, (*oTargetSettingIt)->m_nTargetId);

		++oTargetSettingIt;
	}
}