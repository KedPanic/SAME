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
#include "CInitializingThread.h"
#include "CPlatform.h"
#include "CSamBox.h"
#include "resources/CResourceManager.h"

#include "exporter/CExporterManager.h"
#include "exporter/CTextureExporterDXT.h"
#include "exporter/CMeshExporter.h"

#include <common/SamModuleInit.h>

#include <Qdir>
#include <QStandardPaths>

void CInitializingThread::run()
{
    emit ShowSplashScreen();

    InitializeEngine();

    InitializeEditor();
}

void CInitializingThread::InitializeEngine()
{
    emit ShowMessage("Sam Engine initializing...");

    sam::Env *pEnv = sam::InitCommon();
    sam::ModuleInit(pEnv);

    // create log file.
    pEnv->pLog->SetFilename("SamBox.log");

    // load sub-modules
    sam::CreateRenderManager(pEnv);
    sam::scene::CreateEntitySystem(pEnv);
}

void CInitializingThread::InitializeEditor()
{    
    emit ShowMessage("SamBox initializing...");

    // initializing sam box
    new CResourceManager;
    new CExporterManager;

    // initialize exporter.
    g_pExporterManager->RegisterExporter(new CTextureExporterDXT);
    g_pExporterManager->RegisterExporter(new CMeshExporter);

    // create application folder.
    QDir oDir;
    oDir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DataLocation));

    // create supported platform configurations.
    {
        // default platform
        CPlatform *pPlatform = SAM_NEW CPlatform;
        const char *aExporter[ e_ResourceType_Nb ] =
        {
            "TrueType",
            "DXT",
            "Mesh"
        };

        pPlatform->Initialize("PC", aExporter);
        g_pSamBox->AddPlatform(pPlatform);
    }
}
