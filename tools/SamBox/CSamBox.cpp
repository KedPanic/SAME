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
#include "CSamBox.h"
#include "CProject.h"
#include "CWorld.h"
#include "CFolder.h"

#include "resources/CRequestManager.h"
#include "resources/CTextureResourceFactory.h"

// Widgets.
#include "qt/CProjectWizard.h"
#include "qt/CMainWindow.h"
#include "qt/CSaveDialog.h"

#include <QtWidgets/QSplashScreen>

namespace sam
{
	namespace box
	{
		int CSamBox::Message(const QString &p_sMessage)
		{
			QMessageBox oMessage(QMessageBox::Information, "SamBox", p_sMessage, QMessageBox::Yes | QMessageBox::No, CSamBox::GetInstance()->m_pMainWindow);
			return oMessage.exec();
		}

		CSamBox *CSamBox::m_pInstance = NULL;
		CSamBox::CSamBox(const QString &p_sAppPath)
			: m_pMainWindow(NULL), m_pProjectWizard(NULL), m_sAppPath(p_sAppPath), m_pCurrentProject(NULL), m_pCurrentWorld(NULL)
		{
			m_pInstance = this;
		}

		CSamBox::~CSamBox()
		{
			CloseCurrentProject();

			if(m_pProjectWizard)
			{
				delete m_pProjectWizard;
			}

			if(m_pMainWindow)
			{
				delete m_pMainWindow;
			}		
		}

		// Initialization.
		void CSamBox::Initialize()
		{
			// Create splash screen.
			QSplashScreen oSplashScreen(QPixmap("bernie.jpg"));
			oSplashScreen.show();
			oSplashScreen.showMessage("Initialization...");
			Sleep(1000);

			// Initialize engine.
			sam::CreateRenderManager(g_Env);

			// Create request manager and register default factory.
			g_pRequestManager = SAM_NEW CRequestManager;
			g_pRequestManager->RegisterFactory(SAM_NEW CTextureResourceFactory);
			LoadExporters();

			// Create project wizard.
			m_pProjectWizard = new qt::CProjectWizard;
			m_pProjectWizard->show();
		}

		// Open SamBox
		void CSamBox::OpenSamBox()
		{
			m_pProjectWizard->hide();			

			// Create and show the main window.
			m_pMainWindow = new qt::CMainWindow;			

			// Populate informations from current project.
			m_pMainWindow->SetProjectFolder(m_pCurrentProject->GetPath().absolutePath());

			// Show it.
			m_pMainWindow->show();

			UpdateTitle();
		}

		//////////////////////////////////////////////////////////////////////////
		//							FILE SYSTEM									//
		//////////////////////////////////////////////////////////////////////////
		// Create a new folder in the file tree (archetype, package, world).
		void CSamBox::CreateFolder()
		{
			m_pMainWindow->CreateFolder();
		}

		// Delete focused folder in the file tree (archetype, package, world).
		void CSamBox::DeleteFolder()
		{
			m_pMainWindow->DeleteFolder();
		}

		//////////////////////////////////////////////////////////////////////////
		//								PROJECT									//
		//////////////////////////////////////////////////////////////////////////
		// Create a new project.
		bool CSamBox::CreateProject(const QString &p_sPath)
		{
			if(CloseCurrentWorld() && CloseCurrentProject())
			{
				m_pCurrentProject = SAM_NEW CProject(p_sPath);

				// Create empty world.
				CreateWorld();

				UpdateTitle();

				return true;
			}

			return false;
		}

		// Open project.
		void CSamBox::OpenProject(const QString &p_sPath)
		{
			if(CloseCurrentProject())
			{
				m_pCurrentProject = SAM_NEW CProject(p_sPath);

				UpdateTitle();
			}
		}

		// Close current project.
		bool CSamBox::CloseCurrentProject()
		{	
			if(m_pCurrentProject && CloseCurrentWorld())
			{
				m_pCurrentProject->Save();

				SAM_DELETE m_pCurrentProject;
				m_pCurrentProject = NULL;
			}

			return true;
		}

		// Save current project.
		void CSamBox::SaveCurrentProject()
		{
		}

		//////////////////////////////////////////////////////////////////////////
		//									WORLD								//
		//////////////////////////////////////////////////////////////////////////
		// Create a new world.
		void CSamBox::CreateWorld()
		{
			if(CloseCurrentWorld())
			{
			}
		}

		// Open world.
		void CSamBox::OpenWorld(const QString &p_sPath)
		{
			if(CloseCurrentWorld())
			{
				m_pCurrentWorld = SAM_NEW CWorld(p_sPath);
			}
		}

		// Close current world.
		bool CSamBox::CloseCurrentWorld()
		{
			if(m_pCurrentWorld)
			{
				if(m_pCurrentWorld->HasChanged())
				{
					qt::CSaveDialog oDialog("Do you want to save the world " + m_pCurrentWorld->GetPath() + " ?", m_pMainWindow);
					switch(oDialog.exec())
					{
					case qt::CSaveDialog::e_Save:
						m_pCurrentWorld->Save();
						break;

					case qt::CSaveDialog::e_Cancel:
						return false;
					}
				}

				// delete current world.
				SAM_DELETE m_pCurrentWorld;
				m_pCurrentWorld = NULL;
			}

			return true;
		}

		//////////////////////////////////////////////////////////////////////////
		//								PACKAGE									//
		//////////////////////////////////////////////////////////////////////////
		// Create a new package.
		void CSamBox::CreatePackage()
		{
			QDir sPackageDir = m_pCurrentProject->GetPath().absolutePath() + "/packages/";
		
			// Create a unique folder !
			int nFolderNumber = 1;
			QString sFolderName = "New_Folder";
			while(sPackageDir.mkdir(sFolderName) == false)
			{
				sFolderName = "New_Folder" + QString::number(nFolderNumber);
				nFolderNumber++;
			}

			// Add package !
			m_pMainWindow->AddPackage(sPackageDir.absolutePath() + "/" + sFolderName);
		}

		// Import asset.
		void CSamBox::ImportAsset()
		{
			QFileDialog oDialog(m_pMainWindow, "Import Asset");
			oDialog.setFileMode(QFileDialog::AnyFile);
			oDialog.show();
			if(oDialog.exec() == QDialog::Accepted)
			{
				QString sFile = oDialog.selectedFiles()[0];				

				CFolder *pFolder = m_pMainWindow->GetCurrentFolder();
				g_pRequestManager->RequestImport(sFile, pFolder->GetDir().absolutePath());
			}			
		}



		// Update window title.
		void CSamBox::UpdateTitle()
		{
			if(m_pMainWindow)
			{
				QString sTitle = "SamBox - " + m_pCurrentProject->GetPath().dirName();
				m_pMainWindow->setWindowTitle(sTitle);
			}
		}

		// Load exporter plugins.
		void CSamBox::LoadExporters()
		{
			QStringList aFilters;
			aFilters << QString("*") + SHARED_LIBRARY_EXT;

			// Load each exporter in the plugins folder.
			QString sFolder = QDir::currentPath() + "/plugins/exporters/";
			QDir oDir(sFolder);
			QStringList aResults = oDir.entryList(aFilters, QDir::Files);
			for(int nIndex = 0; nIndex < aResults.size(); ++nIndex)
			{
				g_pRequestManager->RegisterExporter(oDir.absoluteFilePath(aResults[nIndex]));
			}
		}
	}
}
