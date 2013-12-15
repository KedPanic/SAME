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
#include "widgets/panel/CPropertiesPanel.h"
#include "widgets/panel/properties/CTexturePropertiesPanel.h"

#include "resources/IResource.h"

CPropertiesPanel::CPropertiesPanel(wxWindow *p_pParent)
	: m_pCurrentPanel(NULL)
{
	wxXmlResource::Get()->LoadObject(this, p_pParent, wxT("CPropertiesPanel"), wxT("wxPanel"));

	// retrieves widgets.
	m_pResourceName = (wxStaticText *)FindWindowById(XRCID("ID_STATICTEXT_NAME"));
	m_pResourceIcon = (wxStaticBitmap *)FindWindowById(XRCID("ID_STATICBITMAP_ICON"));
	m_pPropertiesPanel = (wxScrolledWindow *)FindWindowById(XRCID("ID_SCROLLEDWINDOW_PROPERTIES"));
	CreateEventTable();

	// create properties panel per resource type.
	m_pTexturePropertiesPanel = new CTexturePropertiesPanel(m_pPropertiesPanel);
	m_pTexturePropertiesPanel->Hide();	
}

void CPropertiesPanel::CreateEventTable()
{
	sam::g_Env->pSignalManager->Connect(e_CustomSignal_ResourceSelected, this, &CPropertiesPanel::SetCurrentResource);
}

// set the current resource.
void CPropertiesPanel::SetCurrentResource(sam::ISignal *p_pSignal)
{
	CResourceSelected *pResourceSelected = (CResourceSelected *)p_pSignal;
	IResource *pResource = pResourceSelected->GetResource();
	m_pResourceName->SetLabelText(pResource->GetName());

	m_pResourceIcon->SetIcon(GetIcon(pResource));

	// hide the current properties panel.
	if(m_pCurrentPanel)
	{
		m_pPropertiesPanel->GetSizer()->Clear();
		m_pCurrentPanel->Hide();
	}

	// display the properties panel.
	if(pResource->GetResourceType() == e_ResourceType_Texture)
	{
		m_pTexturePropertiesPanel->Show();
		m_pTexturePropertiesPanel->SetTextureResource((CTextureResource*)pResource);
		m_pPropertiesPanel->GetSizer()->Add(m_pTexturePropertiesPanel, 0, wxEXPAND | wxALIGN_LEFT, 1);

		m_pCurrentPanel = m_pTexturePropertiesPanel;
	}

	Refresh();
}