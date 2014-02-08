//===========================================
// Copyright (C) 2013-2014 Stone Age Machine
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
#ifndef CProjectFrame_H
#define CProjectFrame_H

#include <QFrame>
#include <QListWidgetItem>
#include <QFileSystemWatcher>
#include <QTreeWidgetItem>

namespace Ui {
class CProjectFrame;
}

class CFileWatcher;
class IResource;
class CFolder;
class CFolderTreeItem;

class CProjectFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CProjectFrame(QWidget *parent = 0);
    ~CProjectFrame();

private slots:
    void on_treeWidgetPackages_itemClicked(QTreeWidgetItem *item, int column);

    void on_horizontalSliderZoom_valueChanged(int value);

    void on_lineEditSearch_textChanged(const QString &filter);

    void on_listWidgetAssets_itemDoubleClicked(QListWidgetItem *item);

    void on_fileCreated(const QString &p_sFilename);
    void on_fileRemoved(const QString &p_sFilename);
    void on_fileModified(const QString &p_sFilename);
    void on_fileRenamed(const QString &p_sOldFilename, const QString &p_sNewFilename);

    void on_listWidgetAssets_itemSelectionChanged();

signals:
    void on_resourceSelected(IResource *p_pResource);

private:
    Ui::CProjectFrame *ui;
    bool m_bIsFiltering;
    CFileWatcher *m_pFileWatcher;

    void PopulateAssetsView(CFolder *p_pFolder, bool p_bSubDir = false);
    IResource *FindItemByName(const QString &p_sFilename);
    void ClearAssetsView();

    void PopulatePackagesView(CFolderTreeItem *p_pFolder);
    CFolderTreeItem *FindFolderByPath(const QString &p_sPath);
};

#endif // CProjectFrame_H
