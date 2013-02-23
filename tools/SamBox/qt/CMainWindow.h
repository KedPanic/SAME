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
#ifndef __SAMBOX_CMAINWINDOW__
#define __SAMBOX_CMAINWINDOW__

#include "qt/CAssetsMenu.h"

namespace Ui {
class SamBox;
}

namespace sam
{
	namespace box
	{
		namespace qt
		{
			class CMainWindow : public QMainWindow
			{
				Q_OBJECT

			public:
				explicit CMainWindow(QWidget *parent = 0);
				~CMainWindow();

				void ApplyDefaultLayout();

				void closeEvent(QCloseEvent *p_pEvent);

				void SetProjectFolder(const QDir &p_oProjectDir);

				//////////////////////////////////////////////////////////////////////////
				//							FILE SYSTEM									//
				//////////////////////////////////////////////////////////////////////////
				/// @brief Create a new folder in the file tree (archetype, package, world).
				void CreateFolder();

				/// @brief Delete focused folder in the file tree (archetype, package, world).
				void DeleteFolder();

				/// @brief Retrieve current folder.
				/// 
				/// @return Current folder.
				CFolder *GetCurrentFolder();

				//////////////////////////////////////////////////////////////////////////
				//								PACKAGE									//
				//////////////////////////////////////////////////////////////////////////
				/// @brief Add a package.
				/// 
				/// @param p_sPackage Package path.
				void AddPackage(const QDir &p_sPackage);

			private:
				Ui::SamBox *ui;
				QTreeWidgetItem *m_pTreeArchetypes;
				QTreeWidgetItem *m_pTreePackages;
				QTreeWidgetItem *m_pTreeWorlds;

				CAssetsMenu m_oAssetsMenu;
				QFileSystemWatcher m_oFileSystemWatcher; ///< Used to check if file or directory have changed.

				/// @brief Create a new folder in the specified item.
				/// 
				/// @param p_pItem Parent.
				/// 
				/// @return Created item.
				QTreeWidgetItem *CreateFolder(QTreeWidgetItem *p_pItem, const QDir &p_oPath);

				/// @brief Read the content of the folder.
				/// 
				/// @param p_pParent Item parent.
				/// @param p_sCurrentFolder Current folder.
				void ParseFolder(QTreeWidgetItem *p_pParent, const QDir &p_sCurrentFolder);

			public slots:
				void ShowProjectsMenu(const QPoint &p_oPosition);
				void OnFolderSelected(QTreeWidgetItem *p_pItem, int);
				void OnZoomChanged(int p_nScale);

				void OnDirectoryChange(const QString &p_sDirectory);
				void OnFileChange(const QString &p_sFile);
			};
		}
	}
}


#endif // __SAMBOX_CMAINWINDOW__
