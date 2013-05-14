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
#ifndef __SAMBOX_APP__
#define __SAMBOX_APP__

#include "CInitializingThread.h"

/// @brief Root class.
class CSamBox : public wxApp
{
public:
	/// @brief Constructor.
	CSamBox();

	virtual bool OnInit();

	virtual int OnExit();

	/// @brief Retrieves path of the data folder.
	/// 
	/// @return Path of the data folder.
	const wxString &GetDataPath() const {return m_sDataFolder;}

	/// @brief Retrieves user home path.
	/// 
	/// @return User home path.
	const wxString GetHomePath() const {return m_oStdPaths.GetUserDataDir();}

private:
	wxStandardPaths m_oStdPaths;
	wxString m_sDataFolder; ///< Root of the data folder.

	CProject *m_pProject; ///< Current project. 

	/// @brief Close current project.
	/// 
	/// @return True if project was closed.
	bool CloseCurrentProject();

	/// @brief Called when initializing finished.
	void OnInitCompleted(CInitCompletedEvent &p_oEvent);

	/// @brief Called when user request to open a project.
	void OnOpenProject(COpenProjectEvent &p_oEvent);

	/// @brief Called when user request to create a project.
	void OnCreateProject(CCreateProjectEvent &p_oEvent);
};

#endif // __SAMBOX_APP__
