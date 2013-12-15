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
#include "widgets/panel/CAssetBrowserPanel.h"
#include "widgets/panel/CAssetPanel.h"
#include "resources/CFolder.h"

//////////////////////////////////////////////////////////////////////////
// Asset Viewer
//////////////////////////////////////////////////////////////////////////
class CAssetViewer : public wxScrolledWindow
{
public:
	CAssetViewer(wxWindow *p_pParent, int32 p_nDefaultItemSize);

private:
	static const int32 margin = 5;	///< border
	int32 m_nItemSize;				///< Item size.
	CFolder *m_pCurrentFolder;		///< Pointer to the current folder to display.

	void CreateEventTable();
	void OnPaint(wxPaintEvent &p_oEvent);
	void OnResize(wxSizeEvent &p_oEvent);
	void OnZoomChanged(wxScrollEvent &p_oEvent);
	void SetCurrentFolder(sam::ISignal *p_pSignal);

	void RefreshView(bool p_bUpdateScrollBar = false);
};

CAssetViewer::CAssetViewer(wxWindow *p_pParent, int32 p_nDefaultItemSize)
	: wxScrolledWindow(p_pParent, wxID_ANY, wxDefaultPosition, wxDefaultSize/*, wxNO_FULL_REPAINT_ON_RESIZE | wxCLIP_CHILDREN*/), m_nItemSize(p_nDefaultItemSize)
{
	CreateEventTable();
	SetDoubleBuffered(true);	

	sam::g_Env->pSignalManager->Connect(e_CustomSignal_ResourceSelected, this, &CAssetViewer::SetCurrentFolder);
}

void CAssetViewer::CreateEventTable()
{
	Bind(wxEVT_SIZE, &CAssetViewer::OnResize, this);
	Bind(wxEVT_SCROLL_CHANGED, &CAssetViewer::OnZoomChanged, this, XRCID("ID_SLIDER_ZOOM"));
	Bind(wxEVT_PAINT, &CAssetViewer::OnPaint, this);
}

// called when the panel need to paint.
void CAssetViewer::OnPaint(wxPaintEvent &p_oEvent)
{
	RefreshView();
}

// called when the panel has been resized.
void CAssetViewer::OnResize(wxSizeEvent &p_oEvent)
{
	RefreshView(true);
}

// set the item size.
void CAssetViewer::OnZoomChanged(wxScrollEvent &p_oEvent)
{
	m_nItemSize = p_oEvent.GetPosition();
	Refresh(true);
}

// set the current folder.
void CAssetViewer::SetCurrentFolder(sam::ISignal *p_pSignal)
{
	CResourceSelected *pResourceSelected = (CResourceSelected *)p_pSignal;
	if(pResourceSelected->GetType() == e_ResourceType_Folder)
	{
		m_pCurrentFolder = (CFolder*)pResourceSelected->GetResource();

		// create resources.

		RefreshView(true);
	}		
}

void CAssetViewer::RefreshView(bool p_bUpdateScrollBar /*= false*/)
{
	wxBufferedPaintDC p_oDC(this, wxBUFFER_CLIENT_AREA);

	p_oDC.SetBackground(*wxWHITE_BRUSH);
	p_oDC.Clear();

	// retrieves the resources.
	const CFolder::Resources &aResources = m_pCurrentFolder->GetResources();

	// retrieves current virtual window area (area - scrollbar).
	int sizeX, sizeY;
	GetVirtualSize(&sizeX, &sizeY);
	//p_oDC.SetClippingRegion();

	int realSizeX, realSizeY;
	GetClientSize(&realSizeX, &realSizeY);

	// compute drawable region.
	float regionWidth = sizeX - (margin * 2.0f);
	float fMaxNbItemX = regionWidth / (float)(m_nItemSize);
	float aligning = 5.0f;
	if(fMaxNbItemX < aResources.size())
	{
		aligning = ((regionWidth / (int)fMaxNbItemX) - m_nItemSize) / 2.f;
	}

	// configure the scrollbar.
	int currentPosX, currentPosY;
	GetViewStart(&currentPosX, &currentPosY);

	int nbRows = ceil(aResources.size() / floor(fMaxNbItemX));
	if(p_bUpdateScrollBar)
	{
		SetScrollbars(1, 1, -1, nbRows * 100 + 10, 0, currentPosY, true);
	}

	int maxNbItemX = fMaxNbItemX;
	if(maxNbItemX < 1)
	{
		maxNbItemX = 1;
	}

	currentPosX = GetScrollPos(wxVERTICAL);
	uint32 firstItemDisplayed = floor(GetScrollPos(wxVERTICAL) / 100.f) * maxNbItemX;
	uint32 lastItemDisplayed = (ceil(realSizeY / 100.f) * maxNbItemX) + firstItemDisplayed;
	if(lastItemDisplayed > aResources.size())
	{
		lastItemDisplayed = aResources.size();
	}
	
	for(uint32 nIndex = firstItemDisplayed; nIndex < lastItemDisplayed; ++nIndex)
	{
		IResource *pResource = aResources[nIndex];

		int col = nIndex % maxNbItemX;
		int row = nIndex / maxNbItemX;

		float posX = margin + (aligning * (col + 1.0f)) + (col * m_nItemSize) + (aligning * (float)col);
		int posY = (margin + (row * m_nItemSize)) - currentPosY;

		p_oDC.DrawBitmap(*pResource->GetThumbnail(), posX + 18, posY);
		p_oDC.DrawText(pResource->GetName(), posX + 18, posY + 64);

		wxString sText;
		sText << nIndex;
		p_oDC.DrawText(sText, posX, posY);		
	}
}
//////////////////////////////////////////////////////////////////////////


CAssetBrowserPanel::CAssetBrowserPanel(wxWindow *p_pParent)
{
	wxXmlResource::Get()->LoadObject(this, p_pParent, wxT("CAssetBrowserPanel"), wxT("wxPanel"));	
	wxPanel *pAssetViewer = (wxPanel*)FindWindow(XRCID("ID_PANEL_ASSETVIEWER"));
	wxSlider *pZoom = (wxSlider*)FindWindow(XRCID("ID_SLIDER_ZOOM"));

	// create viewer.
	m_pAssetViewer = SAM_ALLOC(CAssetViewer)(pAssetViewer, pZoom->GetValue());
	pAssetViewer->SetMinSize(wxSize(150, 150));
	pAssetViewer->GetSizer()->Add(m_pAssetViewer, 1, wxEXPAND);

	// buttons event.	
	//Bind(wxEVT_LEFT_DOWN, &CAssetBrowserPanel::OnImportPackage, this, pImportPackage->GetId());
}
