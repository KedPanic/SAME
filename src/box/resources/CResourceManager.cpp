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
#include "resources/CResourceManager.h"

#include "resources/IResource.h"
#include "resources/IResourceFactory.h"
#include "resources/CTextureResource.h"
#include "resources/CMeshResource.h"
#include "resources/CFileResource.h"

CResourceManager *g_pResourceManager = NULL;

// Default constructor.
CResourceManager::CResourceManager()
{
	SAM_TRAP(g_pResourceManager == NULL);
	g_pResourceManager = this;

	FreeImage_Initialise();
}

CResourceManager::~CResourceManager()
{
	FreeImage_DeInitialise();
}

// Add a resource factory.
void CResourceManager::AddResourceFactory(IResourceFactory *p_pResourceFactory)
{

}

// Create the resource.
IResource *CResourceManager::Create(const sam::String &p_sName, const sam::String &p_sPath, EResourceType p_eResourceType /*= e_ResourceType_Unknown*/)
{
	// if the resource type is unknown try to find it from the name.
	if(p_eResourceType == e_ResourceType_Unknown)
	{
		p_eResourceType = FindResourceType(p_sPath);
	}

	// create the resource.
	IResource *pResource = NULL;
	switch(p_eResourceType)
	{
	case e_ResourceType_Texture:
		pResource = SAM_NEW CTextureResource(p_sName, p_sPath);
		break;

	case e_ResourceType_Mesh:
		pResource = SAM_NEW CMeshResource(p_sName, p_sPath);
		break;

	default:
		// special resource, can't be exported.
		return SAM_NEW CFileResource(p_sName, p_sPath);
	}

	// check if there is the metadata.
	sam::String sMetadataPath = p_sPath + ".metadata";
	if(sam::IsFile(sMetadataPath.c_str()))
	{
		sam::CJSONSerializer oSerializer(sMetadataPath.c_str());
		oSerializer.BeginSerialization(true, sMetadataPath.c_str());
		pResource->Read(&oSerializer);
		oSerializer.EndSerialization();
	}
	else
	{
		// write default metadata.
		sam::CJSONSerializer oSerializer(sMetadataPath.c_str());
		oSerializer.BeginSerialization(false, sMetadataPath.c_str());
		pResource->Write(&oSerializer);
		oSerializer.EndSerialization();
	}
	
	return pResource;
}

// Retrieve the type of the resource from the name.
EResourceType CResourceManager::FindResourceType(const sam::String &p_sName)
{
	uint32 nPosition = p_sName.find_last_of(".");
	
	if(nPosition == p_sName.npos)
	{
		// there is no extension so return unknown !
		return e_ResourceType_Unknown;
	}

	sam::String sExtension = p_sName.substr(nPosition, p_sName.size());	

	// check if it is an image.
	FREE_IMAGE_FORMAT eImageFormat = FreeImage_GetFIFFromFilename(sExtension.c_str());
	if(eImageFormat != FIF_UNKNOWN && FreeImage_FIFSupportsReading(eImageFormat))
	{
		return e_ResourceType_Texture;
	}

	// check if it is a mesh.
	{
		Assimp::Importer oImporter;
		if(oImporter.IsExtensionSupported(sExtension.c_str()))
		{
			return e_ResourceType_Mesh;
		}
	}	

	return e_ResourceType_Unknown;
}
