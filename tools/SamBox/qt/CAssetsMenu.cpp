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
#include "qt/CAssetsMenu.h"
#include "CSamBox.h"

namespace sam
{
	namespace box
	{
		namespace qt
		{
			CAssetsMenu::CAssetsMenu()
				: m_eType(e_Type_Packages)
			{				
				/* Create common actions */
				m_pCreateFolder = new QAction(QApplication::translate("SamBox", "Folder", 0), nullptr);
				connect(m_pCreateFolder, SIGNAL(triggered()), this, SLOT(CreateFolder()));

				m_pDeleteFolder = new QAction(QApplication::translate("SamBox", "Delete", 0), nullptr);
				connect(m_pDeleteFolder, SIGNAL(triggered()), this, SLOT(DeleteFolder()));

				/* Menu Archetypes */
				QMenu *pMenuCreate = new QMenu("Create");
				pMenuCreate->addAction(QApplication::translate("SamBox", "Archetype", 0), this, SLOT(CreateArchetype()));
				pMenuCreate->addAction(m_pCreateFolder);
				m_aMenu[e_Type_Archetypes].addMenu(pMenuCreate);
				m_aMenu[e_Type_Archetypes].addAction(m_pDeleteFolder);

				/* Menu Packages */
				pMenuCreate = new QMenu("Create");
				pMenuCreate->addAction(QApplication::translate("SamBox", "Package", 0), this, SLOT(CreatePackage()));
				pMenuCreate->addAction(m_pCreateFolder);
				m_aMenu[e_Type_Packages].addMenu(pMenuCreate);
				m_aMenu[e_Type_Packages].addSeparator();

				m_pImportAsset = new QAction(QApplication::translate("SamBox", "Import Asset...", 0), nullptr);
				connect(m_pImportAsset, SIGNAL(triggered()), this, SLOT(ImportAsset()));
				m_aMenu[e_Type_Packages].addAction(m_pImportAsset);

				/* Menu Worlds */
				pMenuCreate = new QMenu("Create");
				pMenuCreate->addAction(QApplication::translate("SamBox", "World", 0), this, SLOT(CreateWorld()));
				pMenuCreate->addAction(m_pCreateFolder);
				m_aMenu[e_Type_Worlds].addMenu(pMenuCreate);
				m_aMenu[e_Type_Worlds].addAction(m_pDeleteFolder);
			}

			void CAssetsMenu::Show(const QPoint &p_oPosition, EType p_eType, bool p_bIsRoot)
			{
				m_eType = p_eType;

				// Set create menu.
				m_pDeleteFolder->setEnabled(!p_bIsRoot);
				m_pImportAsset->setEnabled(!p_bIsRoot);

				// Set create menu.
				m_aMenu[m_eType].exec(p_oPosition);
			}

			//////////////////////////////////////////////////////////////////////////
			//								SLOTS								    //
			//////////////////////////////////////////////////////////////////////////
			void CAssetsMenu::CreateFolder()
			{
				CSamBox::GetInstance()->CreateFolder();
			}

			void CAssetsMenu::DeleteFolder()
			{
				CSamBox::GetInstance()->DeleteFolder();
			}

			void CAssetsMenu::CreateArchetype()
			{
			}

			void CAssetsMenu::CreatePackage()
			{
				CSamBox::GetInstance()->CreatePackage();
			}

			void CAssetsMenu::CreateWorld()
			{
				CSamBox::GetInstance()->CreateWorld();
			}

			void CAssetsMenu::ImportAsset()
			{				
				CSamBox::GetInstance()->ImportAsset();
			}
		}
	}
}
