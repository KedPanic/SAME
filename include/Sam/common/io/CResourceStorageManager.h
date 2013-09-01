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
#ifndef __CRESOURCE_STORAGE_MANAGER_H__
#define __CRESOURCE_STORAGE_MANAGER_H__

namespace sam
{
    /// @brief Manage assets.
    class SAM_COMMON_API CResourceStorageManager : public IAllocated
    {
    public:
        /// @brief Constructor.
        CResourceStorageManager();

        /// @brief Destructor.
        ~CResourceStorageManager();

        /// @brief Create a resource storage.
        /// 
        /// @param p_sName Name of the resource storage.
        /// @param p_sPath Absolute path of the resource storage.
		///
        /// @return resource storage or null if an error occurred.
        IResourceStorage *CreateResourceStorage(const char *p_sName, const char *p_sPath);

        /// @brief Retrieves resource storage by name.
        /// 
        /// @param p_sName Name of the resource storage.
		///
        /// @return resource storage or null if not found.
        IResourceStorage *GetResourceStorage(const char *p_sName) const;

        /// @brief Removes resource storage by name.
        /// 
        /// @param p_sName name of the resource storage.
        void RemoveResourceStorage(const char *p_sName);

        /// @brief Removes all resource storages.
        void RemoveAllResourceStorages();

        /// @brief Retrieves resource by name.
        /// 
        /// @param p_sName Name of the resource.
        /// @param p_sStorageName name of the resource storage.
		///
        /// @return Asset or null if not found.
        IStream *GetResource(const char *p_sName, const char *p_sStorageName);

        /// @brief Retrieves path of the specified resource.
        /// 
        /// @param p_sName Name of the resource.
        /// @param p_sStorageName name of the resource storage.
		///
        /// @return Path or null string.
        const char *GetPath(const char *p_sName, const char *p_sStorageName) const;

    private:
        typedef std::map<const char *, IResourceStorage*, cmp_str> ResourceStorages;
        ResourceStorages m_aResourceStorages;     ///< Array of resource storages.

        /// @brief Create a resource storage.
        /// 
        /// @param p_sName Name of the resource storage.
        /// @param p_sPath Absolute path of the resource storage.
        /// @param p_bMod True if its a path for the mod.
		///
        /// @return resource storage or null if an error occurred.
        IResourceStorage *CreateResourceStorage(const char *p_sName, const char *p_sPath, bool p_bMod);
    };
}

#endif // __CRESOURCE_STORAGE_MANAGER_H__
