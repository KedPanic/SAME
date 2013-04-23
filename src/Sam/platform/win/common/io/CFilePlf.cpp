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
#include "common/io/CFile.h"

namespace sam
{
	// Open the stream.
	bool CFile::Open(const char *_sFilename, int _nOpenFlags /*= e_OM_Read | e_OM_Binary*/)
	{
		SAM_ASSERT(m_pFile == NULL, "a file is already open");
		if(m_pFile)
		{
			Close();
		}

		uint16 nIndex = 0;
		char sOpenMode[4] = {'\0'};

		// read mode.
		if(_nOpenFlags & e_OM_Read)
		{
			// create a file.
			if(_nOpenFlags & e_OM_Append)
			{
				sOpenMode[0] = 'a';
				sOpenMode[1] = '+';
				nIndex = 2;
			}
			// file must exist.
			else if(_nOpenFlags & e_OM_Write)
			{
				sOpenMode[0] = 'r';
				sOpenMode[1] = '+';
				nIndex = 2;
			}
			// file must exist.
			else
			{
				sOpenMode[0] = 'r';
				nIndex = 1;
			}
		}
		// write mode. (Create a file).
		else if(_nOpenFlags & e_OM_Write)
		{
			if(_nOpenFlags & e_OM_Append)
			{
				sOpenMode[0] = 'a';
				sOpenMode[1] = '+';
			}
			else
			{
				sOpenMode[0] = 'w';
				sOpenMode[1] = '+';
			}            

			nIndex = 2;
		}

		// binary mode.
		if(_nOpenFlags & e_OM_Binary)
		{
			sOpenMode[nIndex] = 'b';
		}

		if(!(m_pFile = fopen(_sFilename, sOpenMode)))
		{
			SamLogError("Unable to open specified file '%s'", _sFilename);
            return false;
		}

        return true;
	}

	// Close the stream.
	void CFile::Close(void)
	{
		SAM_ASSERT(m_pFile != NULL, "m_pFile is null");

		fclose(m_pFile);
	}

	// Read a block of bytes and store it in the buffer.
	uint32 CFile::Read(void* _pBuffer, uint32 _iSize)
	{
		SAM_ASSERT(m_pFile != NULL, "m_pFile is null");

		return fread(_pBuffer, 1, _iSize, m_pFile);
	}

	// Writes data in the file to the current position.
	uint32 CFile::Write(const void *_pData, uint32 _iSize)
	{
		SAM_ASSERT(m_pFile != NULL, "m_pFile is null");

		return fwrite(_pData, _iSize, 1, m_pFile);
	}

	// Set the position in the stream.
	uint32 CFile::Seek(uint32 _iOffset, ESeekDir _eOrigin)
	{
		SAM_ASSERT(m_pFile != NULL, "m_pFile is null");

		return fseek(m_pFile, _iOffset, _eOrigin);
	}

	// Get the current position in the stream.
	uint32 CFile::Tell()
	{
		SAM_ASSERT(m_pFile != NULL, "m_pFile is null");

		return ftell(m_pFile);
	}

	// Get the size of the stream.
	uint32 CFile::Size()
	{
		SAM_ASSERT(m_pFile != NULL, "m_pFile is null");

		// Retrieves current position.
		uint32 iCurrentPos = ftell(m_pFile);

		// Goto the end.
		fseek(m_pFile, 0L, e_SD_End);

		// Retrieves size.
		uint32 iSize = ftell(m_pFile);

		// Return to the original position.
		fseek(m_pFile, iCurrentPos, e_SD_Begin);

		return iSize;
	}

	// Get true if the end of the stream is reached.
	bool CFile::Eof() const
	{
		SAM_ASSERT(m_pFile != NULL, "m_pFile is null");

		return feof(m_pFile) != 0;
	}	

	// Flush current content.
	void CFile::Flush()
	{
		fflush(m_pFile);
	}
}


