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
#include "widgets/panel/CPackagesPanel.h"
#include "CSamBox.h"
#include "resources/CFolder.h"
#include "CProject.h"

//////////////////////////////////////////////////////////////////////////
//								TREE ITEM DATA							//
//////////////////////////////////////////////////////////////////////////
class CResourceTreeItemData : public wxTreeItemData
{
public:
	CResourceTreeItemData(IResource *p_pResource)
		: m_pResource(p_pResource)
	{
	}

	IResource *GetResource() const {return m_pResource;}

private:
	IResource *m_pResource;
};
//////////////////////////////////////////////////////////////////////////

CPackagesPanel::CPackagesPanel(wxWindow *p_pParent)
{
	wxXmlResource::Get()->LoadObject(this, p_pParent, wxT("CPackagesPanel"), wxT("wxPanel"));	

	// create the root list.
	m_pPackagesList = (wxTreeCtrl*)FindWindowById(XRCID("ID_TREECTRL_PACKAGES"));
	m_pPackagesList->AssignImageList(GetImageList());

	CreateEventTable();
}

// Create dynamic events.
void CPackagesPanel::CreateEventTable()
{
	// buttons.
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CPackagesPanel::OnNewPackage, this, XRCID("ID_BUTTON_NEWPACKAGE"));
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CPackagesPanel::OnImportPackage, this, XRCID("ID_BUTTON_IMPORTPACKAGE"));

	// List events.
	Bind(wxEVT_COMMAND_TREE_SEL_CHANGED, &CPackagesPanel::OnItemSelected, this, XRCID("ID_TREECTRL_PACKAGES"));

	// project events.
	sam::g_Env->pSignalManager->Connect(e_CustomSignal_ProjectInitialized, this, &CPackagesPanel::OnProjectInitialized);
}

void CPackagesPanel::OnNewPackage(wxEvent &p_oEvent)
{
	CFolder *p_pPackage = g_pSamBox->CreateNewPackage();
	//sam::g_Env->pSignalManager->QueueSignal(new CCreateFolderSignal(p_pPackage));
}

void CPackagesPanel::OnImportPackage(wxEvent &p_oEvent)
{

}

void CPackagesPanel::OnCreatePackage(CCreatePackageEvent &p_oEvent)
{	
}

void CPackagesPanel::OnItemSelected(wxTreeEvent &p_oEvent)
{
	CResourceTreeItemData *pTreeItemData = (CResourceTreeItemData*)m_pPackagesList->GetItemData(p_oEvent.GetItem());
	sam::g_Env->pSignalManager->QueueSignal(new CResourceSelected(pTreeItemData->GetResource()));
}

// called when a package has been created.
void CPackagesPanel::OnProjectInitialized(sam::ISignal *p_pSignal)
{
	CProjectInitializedSignal *p_pProjectInitializedSignal = (CProjectInitializedSignal*)p_pSignal;

	// retrieves folder and the item id of the parent.
	CFolder *pFolder = p_pProjectInitializedSignal->GetProject()->GetAssetFolder();
	wxTreeItemId nItemId = m_pPackagesList->AppendItem(m_pPackagesList->GetSelection(), pFolder->GetName(), e_Icon_Folder);
	m_pPackagesList->SetItemData(nItemId, new CResourceTreeItemData(pFolder));
	m_pPackagesList->SelectItem(nItemId);
	AddFolder(pFolder);
	
	
// 	wxTreeItemId nParentItemId = m_pPackagesList->GetRootItem();
// 	if(m_pPackagesList->GetSelection() != m_pPackagesList->GetRootItem())
// 	{
// 		CFolderTreeItemData *pItemData = (CFolderTreeItemData*)m_pPackagesList->GetItemData(m_pPackagesList->GetSelection());
// 		if(pItemData->GetFolder() == pFolder->GetParent())
// 		{
// 			nParentItemId = m_pPackagesList->GetSelection();
// 		}
// 		else if(pItemData->GetFolder()->GetParent() == pFolder->GetParent())
// 		{
// 			nParentItemId = m_pPackagesList->GetItemParent(m_pPackagesList->GetSelection());
// 		}
// 	}	
// 
// 	wxTreeItemId nItemId = m_pPackagesList->AppendItem(nParentItemId, pFolder->GetName(), e_Icon_Folder);
// 	m_pPackagesList->SetItemData(nItemId, new CFolderTreeItemData(pFolder));
// 	m_pPackagesList->SelectItem(nItemId);
// 	m_pPackagesList->EditLabel(nItemId);
}

void CPackagesPanel::AddFolder(const CFolder *p_pFolder)
{
	const CFolder::Resources &aResources = p_pFolder->GetResources();
	CFolder::Resources::const_iterator it = aResources.begin();
	CFolder::Resources::const_iterator it_end = aResources.end();
	while(it != it_end)
	{
		IResource *pResource = *it;

		wxTreeItemId nItemId = m_pPackagesList->AppendItem(m_pPackagesList->GetSelection(), pResource->GetName());
		m_pPackagesList->SetItemData(nItemId, new CResourceTreeItemData(pResource));
		m_pPackagesList->SetItemImage(nItemId, GetIconFromResource(pResource));

		if(pResource->GetResourceType() == e_ResourceType_Folder)
		{			
			m_pPackagesList->SelectItem(nItemId);
			AddFolder((CFolder*)pResource);
			m_pPackagesList->SelectItem(m_pPackagesList->GetItemParent(nItemId));
		}

		++it;
	}
}