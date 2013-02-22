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

namespace sam
{
	// Constructor.
	CFile::CFile(bool p_bFreeOnClose /*= true*/)
		: IStream(p_bFreeOnClose), m_pFile(NULL), m_pCache(NULL)
	{

	}

	// Constructor.
	CFile::CFile(const char *_sFile, bool p_bFreeOnClose /*= true*/)
		: IStream(p_bFreeOnClose), m_pFile(NULL), m_pCache(NULL)
	{
		Open(_sFile);	
	}

	// Destructor.
	CFile::~CFile(void)
	{
		if(m_pFile)
		{
			Close();
		}

		if(m_pCache && FreeOnClose())
		{
			SAM_FREE_ARRAY(m_pCache);
		}
	}

	// Get the data of the stream.
	uint8 *CFile::Data(void)
	{
		SAM_ASSERT(m_pFile != NULL, "m_pFile is null");

		if(m_pCache == NULL)
		{
			// Retrieves size.
			uint32 iSize = Size();

			// seek to begin
			Seek(0, e_SD_Begin);

			// Create buffer and copy file.
			m_pCache = SAM_ALLOC_ARRAY(uint8, iSize);
			memset(m_pCache, '\0', iSize);

			Read(m_pCache, iSize);
		}

		return m_pCache;
	}
}
