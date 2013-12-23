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
	/// @param p_sPath Allocated string.
	///
	/// @return True if no error occurred.
	INLINE bool GetHomePath(char *p_sPath)
	{
        passwd *pPasswd = getpwuid(getuid());
        p_sPath = pPasswd->pw_dir;

		return true;
	}

	/// @brief Retrieves application path.
	///
	/// @param p_sPath Allocated string.
	///
	/// @return True if no error occurred.
	INLINE bool GetAppPath(char *p_sPath)
	{
        readlink("/proc/self/exe", p_sPath, MAX_PATH);
		return true;
	}


	/// @brief Creates recursively directories.
	///
	/// @param p_sPath Allocated string.
	///
	/// @return True if no error occurred.
	INLINE bool CreateDirectory(const char *p_sPath)
	{
		return mkdir(p_sPath, 0777);
	}

	/// @brief Retrieves current working directory.
	///
	/// @param p_nBufferLength Size of the allocated string.
	/// @param p_sPath Allocated string.
	///
	/// @return True if no error occurred.
	INLINE bool GetCurrentWorkingDirectory(uint32 p_nBufferLength, char *p_sPath)
	{
        return getcwd(p_sPath, p_nBufferLength);
	}

	/// @brief Check if specified path is a file.
	///
	/// @param p_sPath File path.
	///
	/// @return True if specified path is a file.
	INLINE bool IsFile(const char *p_sPath)
	{
        struct stat oStat;
        return stat(p_sPath, &oStat) == 0 && S_ISREG(oStat.st_mode);
	}

	/// @brief Check if specified path is a directory.
	///
	/// @param p_sPath File path.
	///
	/// @return True if specified path is a directory.
	INLINE bool IsDirectory(const char *p_sPath)
	{
		struct stat oStat;
        return stat(p_sPath, &oStat) == 0 && S_ISDIR(oStat.st_mode);
	}

    /// @brief Retrieves all directory in the specified directory.
    ///
    /// @param p_sDir Root directory to search subdirectory.
    /// @param p_asSubDir Array of subdirectory.
    /// @param p_bRecursive True to search recursively.
    ///
    /// @return True if no error occurred.
    INLINE bool GetSubDirectory(const char *p_sDir, VString &p_asSubDir, bool p_bRecursive = false)
    {
        // Check if its a directory.
        if(IsDirectory(p_sDir))
        {
            SamLogWarning("Unable to find folder %s", p_sDir);
            return false;
        }

        // Get all directory from the specified directory.
        DIR *pDir = opendir(p_sDir);
        dirent *pEntry = NULL;
        char sFullPath[MAX_PATH];

        while((pEntry = readdir(pDir)) != NULL)
        {
            if(pEntry->d_name[0] != '.')
            {
                strcpy(sFullPath, p_sDir);
                strcat(sFullPath, "/");
                strcat(sFullPath, pEntry->d_name);

                if(IsDirectory(sFullPath))
                {
                    p_asSubDir.push_back(sFullPath);

                    if(p_bRecursive)
                    {
                        GetSubDirectory(sFullPath, p_asSubDir, true);
                    }
                }
            }
        }

        return true;
    }

    /// @brief Copy file to destination.
    ///
    /// @param p_sSourceFile File to copy.
    /// @param p_sDestFile Destination file.
    ///
    /// @return True if no error occurred.
    INLINE bool CopyFile(const char *p_sSourceFile, const char *p_sDestFile)
    {
        int nSourceFile = open(p_sSourceFile,  O_RDONLY);
        if(nSourceFile == 0)
        {
            return false;
        }

        int nDestFile = open(p_sDestFile,  O_WRONLY | O_CREAT);
        if(nDestFile == 0)
        {
            return false;
        }

        const uint32 nBufferSize = 8 * 1024;
        char sBuffer[nBufferSize];
        uint32 nRead = 0;
        while((nRead = read(nSourceFile, sBuffer, nBufferSize)) != 0)
        {
            write(nDestFile, sBuffer, nRead);
        }

        close(nSourceFile);
        close(nDestFile);

        return true;
    }
}

#endif // __WIN_FILEUTIL__
