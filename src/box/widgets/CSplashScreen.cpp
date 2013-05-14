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
#include "widgets/CSplashScreen.h"

#include "CSamBox.h"
#include "CInitializingThread.h"

// Constructor.
CSplashScreen::CSplashScreen(const wxBitmap& p_oBitmap, long p_nSplashStyle, 
int p_nMilliseconds, wxWindow* p_pParent, wxWindowID p_nId, 
const wxPoint& p_oPos /*= wxDefaultPosition*/, const wxSize& p_oSize /*= wxDefaultSize*/, 
long p_nStyle /*= wxSIMPLE_BORDER | wxFRAME_NO_TASKBAR | wxSTAY_ON_TOP*/)
: wxSplashScreen(p_oBitmap, p_nSplashStyle, p_nMilliseconds, p_pParent, p_nId, p_oPos, p_oSize, p_nStyle)
{
	// Create event table.
	Bind(wxEVT_COMMAND_TEXT_UPDATED, &CSplashScreen::OnTextUpdate, this);
	Bind(wxEVT_CLOSE_WINDOW, &CSplashScreen::OnCloseWindow, this);

	// Add static text to show message.
	wxWindow *pWindow = GetSplashWindow();
	m_pText = new wxStaticText(pWindow, wxID_ANY, wxT("Initializing :)"), wxPoint(0, pWindow->GetSize().GetHeight() - 15), wxDefaultSize);
}

// Override wxEventFilter method to remove auto hide on any user input.
int CSplashScreen::FilterEvent(wxEvent &p_oEvent)
{
	return Event_Skip;
}

// Event to update the text.
void CSplashScreen::OnTextUpdate(wxCommandEvent &p_oEvent)
{
	m_pText->SetLabelText(p_oEvent.GetString());
}

// Close event received.
void CSplashScreen::OnCloseWindow(wxCloseEvent &p_oEvent)
{	
	wxSplashScreen::OnCloseWindow(p_oEvent);
}
