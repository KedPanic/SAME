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
#ifndef __IRESOURCE_STORAGE_H__
#define __IRESOURCE_STORAGE_H__

namespace sam
{
    /// @enum Define the type of resource storage.
    enum EResourceStorageType
    {
        e_ResourceStorage_Unknown,
        e_ResourceStorage_Folder,		///< Folder.
        e_ResourceStorage_Zip,		///< Zip.
		e_ResourceStorage_Package,	///< Binary package.
    };

    /// @brief Interface of resource storage.
    class IResourceStorage : public IAllocated
    {
    public:
        /// @brief Retrieves type of resource storage.
        /// 
        /// @return Type of resource storage.
        virtual EResourceStorageType GetType() const = 0;

        /// @brief Retrieves full path of the location.
        /// 
        /// @return Full location path.
        virtual const char *GetFullPath() const = 0;

        /// @brief Retrieves IStream from the storage.
        /// 
        /// @param p_sName Name of the resource.
		///
        /// @return Pointer to the IStream or null if an error occurred.
        virtual IStream *GetResource(const char *p_sName) = 0;

        /// @brief Retrieves path of the specified resource.
        /// 
        /// @param p_sName Name of the resource.
		///
        /// @return Path or null string.
        virtual const char *GetPath(const char *p_sName) const = 0;       

        /// @brief Reload location.
        virtual void Reload() = 0;
    };
}

#endif // __IRESOURCE_STORAGE_H__
