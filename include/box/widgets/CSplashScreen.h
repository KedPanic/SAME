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
#ifndef __SAMBOX_SPLASHSCREEN__
#define __SAMBOX_SPLASHSCREEN__

/// @brief Splash screen used when we launch the editor.
/// 
/// @see wxSplashScreen
class CSplashScreen : public wxSplashScreen
{
public:
	/// @brief Constructor.
	CSplashScreen(const wxBitmap& p_oBitmap, long p_nSplashStyle, 
		int p_nMilliseconds, wxWindow* p_pParent, wxWindowID p_nId, 
		const wxPoint& p_oPos = wxDefaultPosition, const wxSize& p_oSize = wxDefaultSize, 
		long p_nStyle = wxSIMPLE_BORDER | wxFRAME_NO_TASKBAR | wxSTAY_ON_TOP);

	/// @brief Override wxEventFilter method to remove auto hide on any user input.
	virtual int FilterEvent(wxEvent &p_oEvent);

	/// @brief Event to update the text.
	/// 
	/// @param p_oEvent Received event.
	void OnTextUpdate(wxCommandEvent &p_oEvent);

	/// @brief Close event received.
	/// 
	/// @param p_oEvent Received event.
	void OnCloseWindow(wxCloseEvent &p_oEvent);

private:
	wxStaticText *m_pText; ///< Message to show the advance.
};

#endif // __SAMBOX_SPLASHSCREEN__
