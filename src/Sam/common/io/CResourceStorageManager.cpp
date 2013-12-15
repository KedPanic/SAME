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
#include "SamCommonPCH.h"
#include "common/io/CResourceStorageManager.h"
#include "common/io/CFolderStorage.h"
#include "common/io/CPackageStorage.h"

namespace sam
{
    // Constructor.
    CResourceStorageManager::CResourceStorageManager()
    {

    }

    /// @brief Destructor.
    CResourceStorageManager::~CResourceStorageManager()
    {
        RemoveAllResourceStorages();
    }

    // Create a resource storage.
    IResourceStorage *CResourceStorageManager::CreateResourceStorage(const char *p_sName, const char *p_sPath)
    {     
        if(IResourceStorage *pResourceStorage = GetResourceStorage(p_sName))
        {
            SamLogWarning("resource storage with name '%s' already exist", p_sName);
            return pResourceStorage;             
        }

// have to be absolute.
// todo: create resource storage creation in IFramework
#if 0
        // Try to find stream location in the mod folder.
        if(g_Env->pSystem->IsMod())
        {            
            char sPath[256] = {'\0'};
            strcat(sPath, g_Env->pSystem->GetModDataFolder());
            strcat(sPath, "\\");
            strcat(sPath, _sPath);
            if(IStreamLocation *pStreamLocation = CreateStreamLocation(_sName, sPath, true))
                return pStreamLocation;
        }

        // Create default location.
        char sPath[256] = {'\0'};
        strcat(sPath, g_Env->pSystem->GetDataFolder());
        strcat(sPath, "\\");
        strcat(sPath, _sPath);
#endif
        return CreateResourceStorage(p_sName, p_sPath, false);
    }

    // Create a resource storage.
    IResourceStorage *CResourceStorageManager::CreateResourceStorage(const char *p_sName, const char *p_sPath, bool p_bMod)
    {
		sam::IResourceStorage *pResourceStorage = 0;
        if(IsFile(p_sPath))
        {
			const char *sExt = &p_sPath[strlen(p_sPath) - 4];

			// Package file ?
			if(strcmp(sExt, ".pck") == 0)
			{
				pResourceStorage = SAM_NEW CPackageStorage(p_sPath);
			}
            // Zip file ?
            else if(strcmp(sExt, ".zip") == 0)
            {
                // TODO create zip archive.
                SamLog("TODO Zip resource storage have to be implemented");
            }			
           
            else
			{
                SAM_ASSERT(false, "Bad resource storage");
			}
        }
		// Directory.
		else if(IsDirectory(p_sPath))
		{
			pResourceStorage = SAM_NEW CFolderStorage(p_sPath);
		}

		// Add new resource storage.
		if(pResourceStorage)
		{
			char *sName = SAM_ALLOC_ARRAY(char, strlen(p_sName));
			strcpy(sName, p_sName);
			m_aResourceStorages.insert(ResourceStorages::value_type(sName, pResourceStorage));
			return pResourceStorage;
		}

        SamLogWarning("Unable to find resource storage '%s' with path '%s'", p_sName, p_sPath);
        return 0;
    }

    // Retrieves resource storage by name.
    IResourceStorage *CResourceStorageManager::GetResourceStorage(const char *p_sName) const
    {
        ResourceStorages::const_iterator it = m_aResourceStorages.find(p_sName);
        if(it != m_aResourceStorages.end())
            return it->second;

        return 0;
    }

    // Removes resource storage by name.
    void CResourceStorageManager::RemoveResourceStorage(const char *p_sName)
    {
        ResourceStorages::iterator it = m_aResourceStorages.find(p_sName);
        if(it != m_aResourceStorages.end())
        {
            SAM_DELETE_ARRAY it->first;
            SAM_DELETE it->second;
            m_aResourceStorages.erase(it);
        }
    }

    // Removes all resource storages.
    void CResourceStorageManager::RemoveAllResourceStorages()
    {
        ResourceStorages::iterator it = m_aResourceStorages.begin(), it_end = m_aResourceStorages.end();
        while(it != it_end)
        {
            SAM_DELETE it->second;
            it = m_aResourceStorages.erase(it);
        }
    }

    // Retrieves resource by name.
    IStream *CResourceStorageManager::GetResource(const char *p_sName, const char *p_sStorageName)
    {
        ResourceStorages::const_iterator it = m_aResourceStorages.find(p_sStorageName);
        if(it != m_aResourceStorages.end())
        {
            return it->second->GetResource(p_sName);
        }

        SamLogError("Unable to find specified asset '%s' in the resource storage '%s'", p_sName, p_sStorageName);
        return 0;
    }

    // Retrieves path of the specified resource.
    const char *CResourceStorageManager::GetPath(const char *p_sName, const char *p_sStorageName) const
    {
        ResourceStorages::const_iterator it = m_aResourceStorages.find(p_sStorageName);
        if(it != m_aResourceStorages.end())
        {
            return it->second->GetPath(p_sName);
        }

        SamLogError("Unable to find specified asset '%s' in the resource storage '%s'", p_sName, p_sStorageName);
        return 0;
    }
}
