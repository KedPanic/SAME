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
#include "widgets/panel/CProjectPanel.h"

#include "widgets/panel/CPackagesPanel.h"
#include "widgets/panel/CAssetBrowserPanel.h"

CProjectPanel::CProjectPanel(wxWindow *p_pParent)
	: wxPanel(p_pParent)
{
	m_pAuiManager = SAM_ALLOC(wxAuiManager)(this, wxAUI_MGR_LIVE_RESIZE);

	//////////////////////////////////////////////////////////////////////////
	// Left pane.
	//////////////////////////////////////////////////////////////////////////
	wxAuiPaneInfo oLeftPaneInfo;
	oLeftPaneInfo.Name(wxT("LeftNotebook"));
	oLeftPaneInfo.Left();
	oLeftPaneInfo.MinSize(150, 150);
	oLeftPaneInfo.Caption(wxT("Packages"));
	oLeftPaneInfo.CaptionVisible(false);
	oLeftPaneInfo.Dockable(false);

	CPackagesPanel *pPackagesPanel = SAM_ALLOC(CPackagesPanel)(this);
	m_pAuiManager->AddPane(pPackagesPanel, oLeftPaneInfo);

	//////////////////////////////////////////////////////////////////////////
	// Right pane.
	//////////////////////////////////////////////////////////////////////////
	wxAuiPaneInfo oRightPaneInfo;
	oRightPaneInfo.Name(wxT("RightNotebook"));
	oRightPaneInfo.CenterPane();
	oRightPaneInfo.MinSize(150, 150);
	oRightPaneInfo.Caption(wxT("Browser"));
	oRightPaneInfo.CaptionVisible(false);
	oRightPaneInfo.Dockable(false);

	CAssetBrowserPanel *pAssetBrowserPanel = SAM_ALLOC(CAssetBrowserPanel)(this);
	pAssetBrowserPanel->SetMinSize(wxSize(150, 150));
	m_pAuiManager->AddPane(pAssetBrowserPanel, oRightPaneInfo);

	m_pAuiManager->Update();
}

CProjectPanel::~CProjectPanel()
{
	m_pAuiManager->UnInit();
}