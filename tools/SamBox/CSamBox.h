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
#ifndef __SAMBOX_CSAMBOX_H__
#define __SAMBOX_CSAMBOX_H__

namespace sam
{
	namespace box
	{
		/// @brief Root of the application.
		class CSamBox
		{
		public:
			static CSamBox *GetInstance() {return m_pInstance;}

			static int Message(const QString &p_sMessage);

			/// @brief Default constructor.
			/// 
			/// @param p_sAppPath Application folder used to save configurations files.
			CSamBox(const QString &p_sAppPath);
			~CSamBox();

			/// @brief Retrieve app folder.
			/// 
			/// @return App folder.
			const QString &GetAppFolder() const {return m_sAppPath;}

			/// @brief Initialization.
			void Initialize();

			/// @brief Open SamBox
			void OpenSamBox();

			//////////////////////////////////////////////////////////////////////////
			//							FILE SYSTEM									//
			//////////////////////////////////////////////////////////////////////////
			/// @brief Signal when a directory change (renamed, removed).
			/// 
			/// @param p_sDirectory 
			void OnDirectoryChange(const QString &p_sDirectory);

			void OnFileChange(const QString &p_sFile);

			/// @brief Create a new folder in the file tree (archetype, package, world).
			void CreateFolder();

			/// @brief Delete focused folder in the file tree (archetype, package, world).
			void DeleteFolder();

			//////////////////////////////////////////////////////////////////////////
			//								PROJECT									//
			//////////////////////////////////////////////////////////////////////////
			/// @brief Create a new project.
			/// 
			/// @param p_sPath Project folder.
			///
			/// @return True if project is created.
			bool CreateProject(const QString &p_sPath);

			/// @brief Open project.
			/// 
			/// @param p_sPath Project folder.
			void OpenProject(const QString &p_sPath);

			/// @brief Close current project.
			/// 
			/// @return True if current project has been closed.
			bool CloseCurrentProject();

			/// @brief Save current project.
			void SaveCurrentProject();

			//////////////////////////////////////////////////////////////////////////
			//									WORLD								//
			//////////////////////////////////////////////////////////////////////////
			/// @brief Create a new world.
			void CreateWorld();

			/// @brief Open world.
			/// 
			/// @param p_sPath World path.
			void OpenWorld(const QString &p_sPath);

			/// @brief Close current world.
			/// 
			/// @return True if current world has been closed.
			bool CloseCurrentWorld();

			/// @brief Save current world.
			void SaveCurrentWorld();

			/// @brief Set world path.

			//////////////////////////////////////////////////////////////////////////
			//								PACKAGE									//
			//////////////////////////////////////////////////////////////////////////
			/// @brief Create a new package.
			void CreatePackage();

			/// @brief Import asset.
			void ImportAsset();

		private:
			static CSamBox *m_pInstance; ///< Unique instance of CSamBox.

			qt::CMainWindow *m_pMainWindow;
			qt::CProjectWizard *m_pProjectWizard;
			QString m_sAppPath;				///< Application folder.
			CProject *m_pCurrentProject;
			CWorld *m_pCurrentWorld;		///< Current open world.			

			/// @brief Update window title.
			void UpdateTitle();

			/// @brief Load exporter plugins.
			void LoadExporters();
		};
	}
}

#endif // __SAMBOX_CSAMBOX_H__
