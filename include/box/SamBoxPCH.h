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
#ifndef __SAMBOX_PCH__
#define __SAMBOX_PCH__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <wx/aui/aui.h>
#include <wx/xrc/xmlres.h>
#include <wx/image.h>
#include <wx/splash.h>
#include <wx/stdpaths.h>
#include <wx/menu.h>
#include <wx/menuitem.h>
#include <wx/dir.h>
#include <wx/treectrl.h>
#include <wx/progdlg.h>
#include <wx/dcbuffer.h>
#include <wx/mimetype.h>

#include <FreeImage.h>

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <SamCommon.h>
#include <SamRenderer.h>
#include <SamInput.h>
#include <SamSound.h>
#include <SamEntitySystem.h>

class boxAuiNotebook;
class CProject;
class CSamBox;
class CSplashScreen;
class CPlatform;
class CTexturePropertiesPanel;

/// @enum Window identifiers
enum EWindowID
{
	e_WindowID_PackagePanel,
};

typedef std::vector<CPlatform*> Platforms;


//////////////////////////////////////////////////////////////////////////
// RESOURCES
//////////////////////////////////////////////////////////////////////////
class CFolder;
class CMeshResource;
class CPackage;
class CResourceManager;
class IResource;
class IResourceFactory;
class CTextureResource;

#include <resources/SMeshMetadata.h>
#include <resources/STextureMetadata.h>

/// @enum Type of resource.
enum EResourceType
{
	e_ResourceType_Font,
	e_ResourceType_Texture,
	e_ResourceType_Mesh,

	e_ResourceType_Unknown,
	e_ResourceType_Nb = e_ResourceType_Unknown,

	e_ResourceType_Folder // special resource.
};

//////////////////////////////////////////////////////////////////////////
// EXPORTERS
//////////////////////////////////////////////////////////////////////////
class CExporterManager;
class IExporter;
class IExporterListener;

typedef std::vector<sam::SParam> ExportParams;

// Global variable.
extern CSamBox *g_pSamBox;
extern CResourceManager *g_pResourceManager;
extern CExporterManager *g_pExporterManager; 

// Declare custom wxWidgets event.
#include <CustomSignal.h>
#include <widgets/CustomEvent.h>
#include <ImageList.h>
#include <LocalizationIDs.h>

#endif // __SAMBOX_PCH__
