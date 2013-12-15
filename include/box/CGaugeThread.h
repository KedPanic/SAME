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
#ifndef __SAMBOX_GAUGE_THREAD__
#define __SAMBOX_GAUGE_THREAD__

/// @brief Thread used when we load a project
class CGaugeThread : public wxThread
{
public:
	/// @brief Constructor.
	/// 
	/// @param p_pSplashScreen Application.
	CGaugeThread(CProject *p_pProject);

	wxThread::ExitCode Entry();

private:
	CProject *m_pProject;
	wxProgressDialog *m_pProgressDialog;

	void ParseFolder(CFolder *p_pParentFolder);

	/// @brief Send event to the splash screen.
	/// 
	/// @param p_sMessage New message to show.
	void SendEvent(const wxString &p_sMessage);
};

#endif // __SAMBOX_GAUGE_THREAD__
