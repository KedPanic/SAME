#ifndef __SAMBOX__
#define __SAMBOX__

// SAM ENGINE
#include <SamCommon.h>
#include <SamRenderer.h>
#include <SamEntitySystem.h>

// EXTERNAL LIBRARIES
#include <FreeImage.h>

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <QMessageBox>

//////////////////////////////////////////////////////////////////////////
/// CORE
//////////////////////////////////////////////////////////////////////////
class CPlatform;
class CProject;
class CSamBox;
class CFileWatcher;

typedef std::vector<CPlatform*> Platforms;

//////////////////////////////////////////////////////////////////////////
/// RESOURCES
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
/// EXPORTERS
//////////////////////////////////////////////////////////////////////////
class CExporterManager;
class IExporter;
class IExporterListener;


// Global variables.
extern CSamBox *g_pSamBox;
extern CResourceManager *g_pResourceManager;
extern CExporterManager *g_pExporterManager;

enum EMode
{
    e_Mode_2D, ///< Set the editor in 2D mode.
    e_Mode_3D, ///< Set the editor in 3D mode.
};

#endif // __SAMBOX__
