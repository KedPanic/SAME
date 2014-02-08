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
#include "SamBox.h"
#include "CProjectLoadingThread.h"
#include "CPlatform.h"
#include "CSamBox.h"
#include "CProject.h"
#include "resources/CFolder.h"
#include "resources/CResourceManager.h"

#include <QDir>
#include <QStandardPaths>
#include <QListWidgetItem>

CProjectLoadingThread::CProjectLoadingThread(CProject *p_pProject) :
    m_pProject(p_pProject)
{

}

void CProjectLoadingThread::run()
{
    emit ShowSplashScreen();

    CreateResourceTree();
}

void CProjectLoadingThread::CreateResourceTree()
{
    emit ShowMessage("Loading resources...");

    ParseFolder(m_pProject->GetPackageFolder(), "");
}

void CProjectLoadingThread::ParseFolder(CFolder *p_pFolder, const sam::String &p_sPackageName)
{
    QDir oDir(p_pFolder->GetPath().c_str());
    QFileInfoList oInfoList = oDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    for(int nIndex = 0; nIndex < oInfoList.count(); ++nIndex)
    {
        const QFileInfo &oFileInfo = oInfoList.at(nIndex);

        if(oFileInfo.isDir())
        {
            CFolder *pFolder = NULL;
            if(p_pFolder->IsRoot())
            {
                pFolder = new CFolder(oFileInfo.fileName().toStdString(), oFileInfo.absoluteFilePath().toStdString(), oFileInfo.fileName().toStdString(), p_pFolder);
                ParseFolder(pFolder, pFolder->GetName());
            }
            else
            {
                pFolder = new CFolder(oFileInfo.fileName().toStdString(), oFileInfo.absoluteFilePath().toStdString(), p_sPackageName, p_pFolder);
                ParseFolder(pFolder, p_sPackageName);
            }

            p_pFolder->AddResource(pFolder);
        }
        // check if it is not a metadata.
        else if(oFileInfo.fileName().indexOf(".metadata") < 0)
        {            
            IResource *pResource = g_pResourceManager->Create(oFileInfo.fileName().toStdString(), oFileInfo.absoluteFilePath().toStdString(), p_sPackageName);
            if(pResource != NULL)
            {
                p_pFolder->AddResource(pResource);
            }
        }
    }
}
