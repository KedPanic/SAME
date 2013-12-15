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
#ifndef __SAMBOX_INITIALIZING_THREAD__
#define __SAMBOX_INITIALIZING_THREAD__

/// @brief Thread used when we launch the editor.
class CInitializingThread : public wxThread
{
public:
	/// @brief Constructor.
	/// 
	/// @param p_pSplashScreen Application.
	CInitializingThread(CSplashScreen *p_pSplashScreen);

	wxThread::ExitCode Entry();

private:
	CSamBox *m_pApp;
	CSplashScreen *m_pSplashScreen;

	/// @brief Send event to the splash screen.
	/// 
	/// @param p_sMessage New message to show.
	void SendEvent(const wxString &p_sMessage);
};

#endif // __SAMBOX_INITIALIZING_THREAD__
