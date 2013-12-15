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
#include "widgets/panel/CAssetPanel.h"

CAssetPanel::CAssetPanel(wxWindow *p_pParent, const wxString &p_sName, wxBitmap *p_pThumbnail)
	: wxPanel(p_pParent, wxID_ANY), m_pThumbnail(NULL), m_pName(NULL)
{
	wxBoxSizer *pBoxSizer = new wxBoxSizer(wxVERTICAL);

	// create thumbnail.
	m_pThumbnail = new wxStaticBitmap(this, wxID_ANY, *p_pThumbnail);
	pBoxSizer->Add(m_pThumbnail, 1, wxEXPAND | wxALL, 5);

	// create text.
	m_pName = new wxTextCtrl(this, wxID_ANY, p_sName, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_CENTER);
	pBoxSizer->Add(m_pName, 0, wxEXPAND | wxALL, 5);

	SetSizer(pBoxSizer);
	Centre();
}
