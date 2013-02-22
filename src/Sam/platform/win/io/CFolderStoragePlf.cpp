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
#include "common/SamPCH.h"
#include "common/io/CFile.h"
#include "common/io/CFolderStorage.h"

namespace sam
{
    // Constructor.
    CFolderStorage::CFolderStorage(const char *p_sFullPath)
        : m_sFullPath(NULL) 
    {
        m_sFullPath = SAM_ALLOC_ARRAY(char, strlen(p_sFullPath));
        strcpy(m_sFullPath, p_sFullPath);

        char sPath[256] = {'\0'};
        strcpy(sPath, m_sFullPath);
        ParseFolder(sPath);
    }

    // Destructor.
    CFolderStorage::~CFolderStorage()
    {
        SAM_FREE(m_sFullPath);

        Assets::iterator it_begin = m_aAssets.begin(), it_end = m_aAssets.end();
        for(; it_begin != it_end; ++it_begin)
        {
            SAM_FREE(it_begin->second);
        }
    }

    // Retrieves IStream from the storage.
    IStream *CFolderStorage::GetResource(const char *p_sName)
    {
        Assets::const_iterator test_it = m_aAssets.begin();
        const char *test = test_it->first;
        if(strcmp(test, p_sName) == 0)
        {
        }

        Assets::const_iterator it = m_aAssets.find(p_sName);
        if(it != m_aAssets.end())
            return SAM_NEW CFile(it->second);

        return 0;
    }

    // Retrieves path of the specified stream.
    const char *CFolderStorage::GetPath(const char *p_sName) const
    {
        Assets::const_iterator it = m_aAssets.find(p_sName);
        if(it != m_aAssets.end())
            return it->second;

        return NULL;
    }

    // Reload location.
    void CFolderStorage::Reload()
    {
        m_aAssets.clear();
        ParseFolder(m_sFullPath);
    }

    // Retrieves all file in the folder.
    void CFolderStorage::ParseFolder(char *p_sPath)
    {
        WIN32_FIND_DATA fd;
        strcat(p_sPath, "/*");
        HANDLE hFile = FindFirstFile(p_sPath, &fd);
        p_sPath[strlen(p_sPath) - 2] = '\0';
        if(hFile != INVALID_HANDLE_VALUE) 
        {
            do 
            {
                // Directory.
                if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
                {                
                    // Do not include parent and local directory.
                    if(strcmp(fd.cFileName, ".") != 0 && strcmp(fd.cFileName, "..") != 0)
                    {
                        strcat(p_sPath, "/");
                        strcat(p_sPath, fd.cFileName);
                        ParseFolder(p_sPath); 
                    }
                }
                else
                {
                    uint32 nFilenameLength = strlen(fd.cFileName);
                    uint32 nSize = strlen(p_sPath) + nFilenameLength;

                    char *sStreamPath = SAM_ALLOC_ARRAY(char, nSize);
                    strcpy(sStreamPath, p_sPath);
                    strcat(sStreamPath, "/");
                    strcat(sStreamPath, fd.cFileName);

                    m_aAssets.insert(Assets::value_type(&sStreamPath[nSize - nFilenameLength + 1], sStreamPath));
                }
            } while(FindNextFile(hFile, &fd));

            FindClose(hFile);
        }
    }
}
