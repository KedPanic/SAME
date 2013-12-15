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
#ifndef __FILEUTIL__
#define __FILEUTIL__

#ifndef MAX_PATH
#	define MAX_PATH 256
#endif

namespace sam
{
	/// @brief Retrieves home path.
	/// 
	/// @param _sPath Allocated string.
	/// 
	/// @return True if no error occurred.
	INLINE bool GetHomePath(char *_sPath)
	{
		return SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, _sPath) >= 0;    
	}

	/// @brief Retrieves application path.
	/// 
	/// @param _sPath Allocated string.
	/// 
	/// @return True if no error occurred.
	INLINE bool GetAppPath(char *_sPath)
	{
		return SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, _sPath) >= 0;    
	}


	/// @brief Creates recursively directories.
	/// 
	/// @param p_sPath Allocated string.
	/// 
	/// @return True if no error occurred.
	INLINE bool CreateDirectory(const char *p_sPath)
	{
		return SHCreateDirectoryExA(NULL, p_sPath, NULL) == ERROR_SUCCESS;
	}

	/// @brief Retrieves current working directory.
	/// 
	/// @param p_nBufferLength Size of the allocated string.
	/// @param p_sPath Allocated string.
	/// 
	/// @return True if no error occurred.
	INLINE bool GetCurrentWorkingDirectory(uint32 p_nBufferLength, char *p_sPath)
	{
		return GetCurrentDirectoryA(p_nBufferLength, p_sPath) != 0;
	}

	/// @brief Check if specified path is a file.
	/// 
	/// @param p_sPath File path.
	/// 
	/// @return True if specified path is a file.
	INLINE bool IsFile(const char *p_sPath)
	{
		DWORD attributes = GetFileAttributesA(p_sPath);

		return attributes != INVALID_FILE_ATTRIBUTES && attributes != FILE_ATTRIBUTE_DIRECTORY;
	}

	/// @brief Check if specified path is a directory.
	/// 
	/// @param p_sPath File path.
	/// 
	/// @return True if specified path is a directory.
	INLINE bool IsDirectory(const char *p_sPath)
	{
		return GetFileAttributesA(p_sPath) == FILE_ATTRIBUTE_DIRECTORY;
	}

    /// @brief Retrieves all directory in the specified directory.
    /// 
    /// @param _sDir Root directory to search subdirectory.
    /// @param _asSubDir Array of subdirectory.
    /// @param _bRecursive True to search recursively.
    ///
    /// @return True if no error occurred.
    INLINE bool GetSubDirectory(const String &_sDir, VString &_asSubDir, bool _bRecursive = false)
    {
        WIN32_FIND_DATAA findData;

        // Check if its a directory.
        HANDLE hFind = FindFirstFileA(_sDir.c_str(), &findData);
        if(INVALID_HANDLE_VALUE == hFind) 
        {
            SamLogWarning("Unable to find folder %s", _sDir.c_str());
            return false;
        } 

        if(!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            SamLogWarning("Specified path is not a directory %s", _sDir.c_str());
            return false;
        }

        // Get all directory from the specified directory.
        while(FindNextFileA(hFind, &findData))
        {
            if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                _asSubDir.push_back(findData.cFileName);

                if(_bRecursive)
                {
                    GetSubDirectory(findData.cFileName, _asSubDir, true);
                }
            }
        }

        return true;
    }

    /// @brief Copy file to destination.
    /// 
    /// @param p_sBaseFile File to copy.
    /// @param p_sDestFile Destination file.
    /// 
    /// @return True if no error occurred.
    INLINE bool CopyFile(const char *p_sBaseFile, const char *p_sDestFile)
    {
        return ::CopyFileA(p_sBaseFile, p_sDestFile, false) != 0;
    }


	/// @brief Retrieves the last modification time of the specified file.
	/// 
	/// @param p_sPath File path.
}

#endif // __WIN_FILEUTIL__
