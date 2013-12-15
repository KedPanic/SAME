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

/// @brief Root class.
class CSamBox : public wxApp
{
public:
	/// @brief Constructor.
	CSamBox();
	~CSamBox();

	virtual bool OnInit();

	virtual int OnExit();

	/// @brief Called when the app is idle. We use the idle time to update the engine.
	void OnIdle(wxIdleEvent &p_oEvent);

	/// @brief Retrieves path of the data folder.
	/// 
	/// @return Path of the data folder.
	const wxString &GetDataPath() const {return m_sDataFolder;}

	/// @brief Retrieves user home path.
	/// 
	/// @return User home path.
	const wxString GetHomePath() const {return m_oStdPaths.GetUserDataDir();}

	/// @brief Add a supported platform could be used by a project.
	/// 
	/// @param p_sPlatformFilename Path of the platform configuration file.
	void AddPlatform(const wxString &p_sPlatformFilename);

	/// @brief Add a supported platform could be used by a project.
	/// 
	/// @param p_pPlatform Created platform.
	void AddPlatform(CPlatform *p_pPlatform);

	/// @brief Retrieves supported platforms.
	/// 
	/// @return Supported platforms.
	const Platforms &GetSupportedPlatforms() const {return m_aPlatforms;}

	/// @brief Retrieves current project.
	/// 
	/// @return Current project.
	CProject *GetCurrentProject() const {return m_pProject;}

	//////////////////////////////////////////////////////////////////////////
	//									RESOURCES							//
	//////////////////////////////////////////////////////////////////////////
	/// @brief Create a new package with a unique name.
	/// 
	/// @return created package.
	CFolder *CreateNewPackage();

	/// @brief Rename package. if the package already exist, it will be renamed automatically.
	/// 
	/// @param p_pPackage Package to rename.
	/// @param p_sName New name.
	void RenamePackage(CPackage *p_pPackage, const char *p_sName);

private:
	wxStandardPaths m_oStdPaths;
	wxString m_sDataFolder; ///< Root of the data folder.

	CProject *m_pProject;	///< Current project.
	Platforms m_aPlatforms; ///< Array of supported platforms.

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

	/// @brief Called when the project is completed
	void OnLoadingCompleted(CLoadingCompletedEvent &p_oEvent);
};

#endif // __SAMBOX_APP__
