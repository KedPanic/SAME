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
#include "qt/CMainWindow.h"
#include "qt/GeneratedFiles/ui_sambox.h"

#include "qt/CPropertiesTexture.h"

#include "CSamBox.h"
#include "CFolder.h"
#include "resources/CRequestManager.h"

#include <QCloseEvent>
#include <QtWidgets/QFileSystemModel>

namespace sam
{
	namespace box
	{
		namespace qt
		{
			CMainWindow::CMainWindow(QWidget *parent) 
				: QMainWindow(parent), ui(new Ui::SamBox)
			{
				ui->setupUi(this);

				// Initialize renderer.
				ui->scene->Initialize();

				ApplyDefaultLayout();

				m_pTreeArchetypes = ui->projectsTreeWidget->findItems("Archetypes", Qt::MatchExactly)[0];
				m_pTreePackages = ui->projectsTreeWidget->findItems("Packages", Qt::MatchExactly)[0];
				m_pTreeWorlds = ui->projectsTreeWidget->findItems("Worlds", Qt::MatchExactly)[0];

				//////////////////////////////////////////////////////////////////////////
				// SLOT
				//////////////////////////////////////////////////////////////////////////

				/* Projects */
				connect(ui->projectsTreeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowProjectsMenu(const QPoint&)));
				connect(ui->projectsTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(OnFolderSelected(QTreeWidgetItem*, int)));
				connect(ui->folderZoomSlider, SIGNAL(valueChanged(int)), this, SLOT(OnZoomChanged(int)));

				/* FILE/DIRECTORY NOTIFICATIONS */
				connect(&m_oFileSystemWatcher, SIGNAL(directoryChanged(const QString&)), this, SLOT(OnDirectoryChange(const QString&)));
				connect(&m_oFileSystemWatcher, SIGNAL(fileChanged(const QString&)), this, SLOT(OnFileChange(const QString&)));				
			}

			CMainWindow::~CMainWindow()
			{
				delete ui;
			}

			void CMainWindow::ApplyDefaultLayout()
			{
				ui->projectsTreeWidget->header()->setSortIndicator(0, Qt::AscendingOrder);

				QFileSystemModel *pModel = new QFileSystemModel;
				pModel->setRootPath("D:\\workspace\\samengine\\trunk\\samples\\graphics\\blending\\packages");
				ui->folderViewer->setModel(pModel);

				CPropertiesTexture *pPropertiesTexture = new CPropertiesTexture(ui->propertiesContents);
				ui->propertiesLayout->addWidget(pPropertiesTexture);

				// 		CRendererWidget *pRenderer = new CRendererWidget(this);
				// 		setCentralWidget(pRenderer);
				// 		pRenderer->Initialize();
				// 		ui->verticalLayout_2->addWidget(pRenderer);
				// 		ui->verticalLayout_2->setStretch(0, 1);
			}

			void CMainWindow::closeEvent(QCloseEvent *p_pEvent)
			{
				if(!CSamBox::GetInstance()->CloseCurrentProject())
				{
					p_pEvent->ignore();
				}

				p_pEvent->ignore();

				QMainWindow::closeEvent(p_pEvent);
			}

			void CMainWindow::SetProjectFolder(const QDir &p_oProjectDir)
			{
				m_pTreeArchetypes->setData(0, Qt::UserRole, qVariantFromValue(SAM_NEW CFolder(p_oProjectDir.absoluteFilePath("Archetypes"))));
				m_pTreePackages->setData(0, Qt::UserRole, qVariantFromValue(SAM_NEW CFolder(p_oProjectDir.absoluteFilePath("Packages"))));
				m_pTreeWorlds->setData(0, Qt::UserRole, qVariantFromValue(SAM_NEW CFolder(p_oProjectDir.absoluteFilePath("Worlds"))));

				ParseFolder(m_pTreeArchetypes, p_oProjectDir.absoluteFilePath("Archetypes"));
				ParseFolder(m_pTreePackages, p_oProjectDir.absoluteFilePath("Packages"));
				ParseFolder(m_pTreeWorlds, p_oProjectDir.absoluteFilePath("Worlds"));

				m_pTreeArchetypes->setExpanded(false);
				m_pTreePackages->setExpanded(false);
				m_pTreeWorlds->setExpanded(false);
			}

			//////////////////////////////////////////////////////////////////////////
			//							FILE SYSTEM									//
			//////////////////////////////////////////////////////////////////////////
			void CMainWindow::OnDirectoryChange(const QString &p_sDirectory)
			{
				//CSamBox::GetInstance()->OnDirectoryChange(p_sDirectory);				
			}

			void CMainWindow::OnFileChange(const QString &p_sFile)
			{
				//CSamBox::GetInstance()->OnFileChange(p_sFile);
			}

			// Create a new folder in the file tree (archetype, package, world).
			void CMainWindow::CreateFolder()
			{
				QTreeWidgetItem *pCurrentItem = ui->projectsTreeWidget->currentItem();
				CFolder *pFolder = pCurrentItem->data(0, Qt::UserRole).value<CFolder*>();

				SAM_ASSERT(pFolder && pFolder->GetDir().exists(), "Current directory doesn't exist!");

				// Create a unique folder !
				QDir oParentDir = pFolder->GetDir();
				int nFolderNumber = 1;
				QString sFolderName = "New_Folder";
				while(oParentDir.mkdir(sFolderName) == false)
				{
					sFolderName = "New_Folder" + QString::number(nFolderNumber);
					nFolderNumber++;
				}

				QTreeWidgetItem *pItem = CreateFolder(pCurrentItem, oParentDir.absoluteFilePath(sFolderName));
			}

			// Delete focused folder in the file tree (archetype, package, world).
			void CMainWindow::DeleteFolder()
			{
				QTreeWidgetItem *pCurrentItem = ui->projectsTreeWidget->currentItem();
				CFolder *pFolder = pCurrentItem->data(0, Qt::UserRole).value<CFolder*>();

				SAM_ASSERT(pFolder && pFolder->GetDir().exists(), "Current directory doesn't exist!");

				QString sMessage = "Are you sure you want to delete ";
				if(pCurrentItem->parent() == m_pTreePackages)
				{
					sMessage += "the package '";
				}
				else
				{
					sMessage += "the folder '";
				}

				// Ask the user to be sure.
				switch(CSamBox::Message(sMessage + pFolder->GetDir().dirName() + "' ?"))
				{
				case QMessageBox::No:
				case QMessageBox::Cancel:
					return;
				}

				// Delete the content.
				pFolder->GetDir().removeRecursively();
				delete pCurrentItem;
				SAM_DELETE pFolder;
			}

			// Retrieve current folder.
			CFolder *CMainWindow::GetCurrentFolder()
			{
				QTreeWidgetItem *pCurrentItem = ui->projectsTreeWidget->currentItem();
				return pCurrentItem->data(0, Qt::UserRole).value<CFolder*>();
			}

			//////////////////////////////////////////////////////////////////////////
			//								PACKAGE									//
			//////////////////////////////////////////////////////////////////////////
			// Add a package.
			void CMainWindow::AddPackage(const QDir &p_sPackage)
			{
				// Create a new Item.
				QTreeWidgetItem *pItem = CreateFolder(m_pTreePackages, p_sPackage);
			}

			//////////////////////////////////////////////////////////////////////////
			//								SLOTS								    //
			//////////////////////////////////////////////////////////////////////////
			void CMainWindow::ShowProjectsMenu(const QPoint &p_oPosition)
			{
				QTreeWidgetItem *pItem = ui->projectsTreeWidget->itemAt(p_oPosition);
				if(pItem)
				{
					// Find parent.
					bool bIsRoot = true;
					QTreeWidgetItem *pParent = pItem;
					while(pParent->parent())
					{
						bIsRoot = false;
						pParent = pParent->parent();
					}

					// Define type of menu
					CAssetsMenu::EType eType = CAssetsMenu::e_Type_Packages;
					if(pParent->text(0) == "Archetypes")
					{
						eType = CAssetsMenu::e_Type_Archetypes;
					}
					else if(pParent->text(0) == "Worlds")
					{
						eType = CAssetsMenu::e_Type_Worlds;
					}

					ui->projectsTreeWidget->setCurrentItem(pItem);
					
					// Show menu.
					QPoint oGlobalPosition = ui->projectsTreeWidget->mapToGlobal(p_oPosition);
					m_oAssetsMenu.Show(oGlobalPosition, eType, bIsRoot);
				}				
			}

			void CMainWindow::OnFolderSelected(QTreeWidgetItem *p_pItem, int)
			{
				//ui->folderViewer->SetFolder(p_pItem->data(0, Qt::UserRole).value<CFolder*>());
				CFolder *pFolder = p_pItem->data(0, Qt::UserRole).value<CFolder*>();
				QString sPath = pFolder->GetDir().absolutePath();
				QFileSystemModel *pModel = (QFileSystemModel *)ui->folderViewer->model();
				pModel->setRootPath(sPath);
				ui->folderViewer->setRootIndex(pModel->index(sPath));
			}

			void CMainWindow::OnZoomChanged(int p_nScale)
			{
				//ui->folderViewer->Scale(p_nScale);
			}

			//////////////////////////////////////////////////////////////////////////
			//																	    //
			//////////////////////////////////////////////////////////////////////////
			// Create a new folder in the specified item.
			QTreeWidgetItem *CMainWindow::CreateFolder(QTreeWidgetItem *p_pItem, const QDir &p_oPath)
			{
				// Retrieves parent folder.
				CFolder *pParentFolder = p_pItem->data(0, Qt::UserRole).value<CFolder*>();
				CFolder *pFolder = SAM_NEW CFolder(p_oPath, pParentFolder);
				pParentFolder->AddFolder(pFolder);

				QVariant oData = qVariantFromValue<CFolder*>(pFolder);

				QTreeWidgetItem *pItem = new QTreeWidgetItem();				
				pItem->setIcon(0, QIcon(QStringLiteral(":/data/32x32/directory.png")));
				pItem->setFlags(pItem->flags() | Qt::ItemIsEditable);
				pItem->setData(0, Qt::UserRole, oData);
				pItem->setText(0, p_oPath.dirName());
				p_pItem->addChild(pItem);
				ui->projectsTreeWidget->setCurrentItem(pItem);

				return pItem;
			}

			// Read the content of the folder.
			void CMainWindow::ParseFolder(QTreeWidgetItem *p_pParent, const QDir &p_sCurrentFolder)
			{
				QStringList oStringList = p_sCurrentFolder.entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
				for(int nIndex = 0; nIndex < oStringList.size(); ++nIndex)
				{
					QFileInfo oInfo(p_sCurrentFolder.absoluteFilePath(oStringList[nIndex]));
					QString sPath = oInfo.absoluteFilePath();

					if(oInfo.isDir())
					{
						// Create the folder.
						QTreeWidgetItem *pChild = CreateFolder(p_pParent, sPath);

						ParseFolder(pChild, sPath);
					}
					// check if it isn't meta.
					else if(sPath.endsWith(".meta") == false)
					{												
						g_pRequestManager->RequestLoad(sPath);					
					}
				}
			}
		}
	}
}
