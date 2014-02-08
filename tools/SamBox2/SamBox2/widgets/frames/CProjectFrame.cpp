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
#include "CProjectFrame.h"
#include "ui_cprojectframe.h"

#include "CSamBox.h"
#include "CProject.h"
#include "CFileWatcher.h"
#include "resources/CFolder.h"
#include "resources/CResourceManager.h"
#include "project/CFolderTreeItem.h"

#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QFileIconProvider>
#include <QDir>

CProjectFrame::CProjectFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CProjectFrame),
    m_bIsFiltering(false),
    m_pFileWatcher(NULL)
{
    ui->setupUi(this);    

    // create assets view.
    QString sAssetRootPath = (g_pSamBox->GetCurrentProject()->GetProjectPath() + "/packages/").c_str();
    PopulateAssetsView(g_pSamBox->GetCurrentProject()->GetPackageFolder());

    // create file watcher
    m_pFileWatcher = new CFileWatcher(this);
    m_pFileWatcher->setPath(sAssetRootPath);

    connect(m_pFileWatcher, SIGNAL(fileCreated(const QString&)), this, SLOT(on_fileCreated(const QString&)));
    connect(m_pFileWatcher, SIGNAL(fileRemoved(QString)), this, SLOT(on_fileRemoved(QString)));
    connect(m_pFileWatcher, SIGNAL(fileModified(const QString&)), this, SLOT(on_fileModified(const QString&)));
    connect(m_pFileWatcher, SIGNAL(fileRenamed(QString,QString)), this, SLOT(on_fileRenamed(QString,QString)));

    // create packages view.
    CFolderTreeItem *pRoot = new CFolderTreeItem(ui->treeWidgetPackages);
    pRoot->SetFolder(g_pSamBox->GetCurrentProject()->GetPackageFolder());
    pRoot->setText(0, "packages");
    PopulatePackagesView(pRoot);
    // hide specific column to keep the name column only.
    ui->treeWidgetPackages->hideColumn(1);
    ui->treeWidgetPackages->hideColumn(2);
    ui->treeWidgetPackages->hideColumn(3);

    ui->splitterProject->setStretchFactor(0, 0);
    ui->splitterProject->setStretchFactor(1, 1);
}

CProjectFrame::~CProjectFrame()
{
    delete ui;
}

void CProjectFrame::PopulateAssetsView(CFolder *p_pFolder, bool p_bSubDir /*= false*/)
{
    const CFolder::Resources &aResources = p_pFolder->GetResources();
    for(uint32 nIndex = 0; nIndex < aResources.size(); ++nIndex)
    {
        IResource *pResource = aResources[nIndex];
        if(p_bSubDir && pResource->GetResourceType() == e_ResourceType_Folder)
        {
            PopulateAssetsView((CFolder*)pResource);
        }

        ui->listWidgetAssets->addItem(aResources[nIndex]);
    }
}

IResource *CProjectFrame::FindItemByName(const QString &p_sFilename)
{
    QList<QListWidgetItem*> oList = ui->listWidgetAssets->findItems(p_sFilename, Qt::MatchExactly);

    if(m_bIsFiltering)
    {
        // check by path.
        CFolderTreeItem *pItem = (CFolderTreeItem*)ui->treeWidgetPackages->currentItem();
        for(int nIndex = 0; nIndex < oList.size(); ++nIndex)
        {
            IResource *pResource = (IResource*)oList.at(nIndex);
            if(pResource->GetPath() == pItem->GetFolder()->GetPath())
            {
                return pResource;
            }
        }

        return NULL;
    }

    if(oList.size())
    {
        return (IResource*)oList.at(0);
    }

    SAM_ASSERT(false, "should never happen !");
    return NULL;
}

void CProjectFrame::ClearAssetsView()
{
    // clear the list.
    while(ui->listWidgetAssets->count() > 0)
    {
        ui->listWidgetAssets->takeItem(0);
    }
}

void CProjectFrame::PopulatePackagesView(CFolderTreeItem *p_pFolderParent)
{
    const CFolder::Resources &aResources = p_pFolderParent->GetFolder()->GetResources();
    for(uint32 nIndex = 0; nIndex < aResources.size(); ++nIndex)
    {
        IResource *pResource = aResources[nIndex];
        if(pResource->GetResourceType() == e_ResourceType_Folder)
        {
            CFolderTreeItem *pFolderItem = new CFolderTreeItem(p_pFolderParent);
            pFolderItem->setText(0, pResource->GetName().c_str());
            pFolderItem->SetFolder((CFolder*)pResource);
            pFolderItem->setIcon(0, pResource->icon());

            PopulatePackagesView(pFolderItem);
        }
    }
}

CFolderTreeItem *CProjectFrame::FindFolderByPath(const QString &p_sPath)
{
    QDir oDir(p_sPath);
    QString sName = oDir.dirName();
    QList<QTreeWidgetItem*> oList = ui->treeWidgetPackages->findItems(oDir.dirName(), Qt::MatchExactly | Qt::MatchRecursive);
    for(int nIndex = 0; nIndex < oList.count(); ++nIndex)
    {
        CFolderTreeItem *pFolder = (CFolderTreeItem*)oList.at(nIndex);
        if(pFolder->GetFolder()->GetPath() == p_sPath.toStdString())
        {
            return pFolder;
        }
    }

    return NULL;
}

/////////////////////////////////////////////////////////////////
/// SLOTS
/////////////////////////////////////////////////////////////////
void CProjectFrame::on_treeWidgetPackages_itemClicked(QTreeWidgetItem *item, int column)
{
    if(m_bIsFiltering == false)
    {
        CFolderTreeItem *pFolderItem = (CFolderTreeItem*)item;

        ClearAssetsView();
        PopulateAssetsView(pFolderItem->GetFolder());
    }
    else
    {
        m_bIsFiltering = false;
        ui->lineEditSearch->textChanged(ui->lineEditSearch->text());
    }
}

void CProjectFrame::on_horizontalSliderZoom_valueChanged(int value)
{
    if(value == ui->horizontalSliderZoom->minimum())
    {
        ui->listWidgetAssets->setViewMode(QListView::ListMode);

        ui->listWidgetAssets->setIconSize(QSize(value, value));
        ui->listWidgetAssets->setGridSize(QSize(value, value + 5));
    }
    else
    {
        if(ui->listWidgetAssets->viewMode() != QListView::IconMode)
        {
            ui->listWidgetAssets->setViewMode(QListView::IconMode);
        }

        ui->listWidgetAssets->setIconSize(QSize(value, value));
        ui->listWidgetAssets->setGridSize(QSize(value + 10, value + 25));
    }
}

void CProjectFrame::on_lineEditSearch_textChanged(const QString &filter)
{
    if(filter.isEmpty())
    {
        m_bIsFiltering = false;

        CFolderTreeItem *pItem = (CFolderTreeItem*)ui->treeWidgetPackages->currentItem();

        ClearAssetsView();
        PopulateAssetsView(pItem->GetFolder(), false);
    }
    else
    {
        if(m_bIsFiltering == false)
        {
            CFolderTreeItem *pItem = (CFolderTreeItem*)ui->treeWidgetPackages->currentItem();

            // add all file and folder.
            ClearAssetsView();
            PopulateAssetsView(pItem->GetFolder(), true);

            m_bIsFiltering = true;
        }

        // remove all non matching files and folder.
        for(int nCount = 0; nCount < ui->listWidgetAssets->count(); ++nCount)
        {
            QListWidgetItem *pItem = ui->listWidgetAssets->item(nCount);
            QString sName = pItem->text();
            pItem->setHidden(sName.indexOf(filter, 0, Qt::CaseInsensitive) < 0);
        }
    }       
}

void CProjectFrame::on_listWidgetAssets_itemDoubleClicked(QListWidgetItem *item)
{
    IResource *pItem = (IResource*)(item);
    if(pItem->GetResourceType() == e_ResourceType_Folder)
    {
        CFolderTreeItem *pFolderItem = FindFolderByPath(pItem->GetPath().c_str());
        ui->treeWidgetPackages->setCurrentItem(pFolderItem);

        // clear the list.
        ClearAssetsView();
        PopulateAssetsView((CFolder*)pItem);
    }
}

void CProjectFrame::on_fileCreated(const QString &p_sFilename)
{
    if(p_sFilename.indexOf(".metadata") < 0)
    {
        CFolderTreeItem *pItem = (CFolderTreeItem*)ui->treeWidgetPackages->currentItem();
        QDir oDir(pItem->GetFolder()->GetPath().c_str());

        // create the resource.
        // TODO

        // add the file in the asset viewer.
        QFileInfo oFileInfo(oDir, p_sFilename);
        IResource *pResource = NULL;
        if(oFileInfo.isDir())
        {
            // create folder resource.
            pResource = SAM_NEW CFolder(p_sFilename.toStdString(), oFileInfo.absoluteFilePath().toStdString(), pItem->GetFolder()->GetPackage());

            CFolderTreeItem *pFolderItem = new CFolderTreeItem(pItem);
            pFolderItem->SetFolder((CFolder*)pResource);
            pFolderItem->setText(0, p_sFilename);
        }
        else
        {
            pResource = g_pResourceManager->Create(p_sFilename.toStdString(), oFileInfo.absoluteFilePath().toStdString(), pItem->GetFolder()->GetPackage());
        }

        ui->listWidgetAssets->addItem(pResource);
        if(m_bIsFiltering)
        {
            pResource->setHidden(p_sFilename.indexOf(ui->lineEditSearch->text(), 0, Qt::CaseInsensitive) < 0);
        }
    }
}

void CProjectFrame::on_fileRemoved(const QString &p_sFilename)
{
    IResource *pItem = FindItemByName(p_sFilename);
    if(pItem != NULL)
    {
        SAM_DELETE pItem;
    }
}

void CProjectFrame::on_fileModified(const QString &p_sFilename)
{
    IResource *pItem = FindItemByName(p_sFilename);
    if(pItem != NULL)
    {
        // TODO: refresh the resource.
    }
}

void CProjectFrame::on_fileRenamed(const QString &p_sOldFilename, const QString &p_sNewFilename)
{
    IResource *pItem = FindItemByName(p_sOldFilename);
    if(pItem != NULL)
    {
        CFolderTreeItem *pFolder = (CFolderTreeItem*)ui->treeWidgetPackages->currentItem();
        QDir oDir(pFolder->GetFolder()->GetPath().c_str());

        pItem->SetName(p_sNewFilename.toStdString());
        pItem->SetPath(oDir.filePath(p_sNewFilename).toStdString());
        pItem->setText(p_sNewFilename);

        if(m_bIsFiltering)
        {
            pItem->setHidden(p_sNewFilename.indexOf(ui->lineEditSearch->text(), 0, Qt::CaseInsensitive) < 0);
        }
    }
}

void CProjectFrame::on_listWidgetAssets_itemSelectionChanged()
{
    emit on_resourceSelected((IResource*)ui->listWidgetAssets->currentItem());
}
