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
#ifndef __SAMBOXPCH__
#define __SAMBOXPCH__

#define NOMINMAX

#include <SamCommon.h>
#include <SamRenderer.h>
#include <SamInput.h>
#include <QtCore>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/qgraphicsproxywidget.h>
#include <QtWidgets/QFileDialog>

#include <FreeImage.h>

namespace sam
{
	namespace box
	{
		class CDatabase;
		class CFolder;
		class CPackage;
		class CProject;
		class CProjectManager;
		class CRequestManager;
		class CWorld;
		class IExporter;
		class IResource;
		class IResourceFactory;

		// Global variables.
		extern CRequestManager *g_pRequestManager;

		// QT
		namespace qt
		{
			class CMainWindow;
			class CProjectWizard;			
		}

		/// @brief Open a dialog box to choose a directory.
		extern QDir OpenDirDialog(QWidget *p_pParent = NULL, const QString &p_sTitle = QString(), const QString &p_sFolder = QString());
	}
}

#endif // __SAMBOXPCH__
