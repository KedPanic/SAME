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
#include "common/io/CPackageStorage.h"
#include "common/io/CMemoryStream.h"

namespace sam
{
	// Constructor.
	CPackageStorage::CPackageStorage(const char *p_sFullPath)
	{
		m_sFullPath = SAM_ALLOC_ARRAY(char, strlen(p_sFullPath));
		strcpy(m_sFullPath, p_sFullPath);

		m_oFile.Open(m_sFullPath);

		// Parse the header.
		Reload();
	}

	// Retrieves IStream from the storage.
	IStream *CPackageStorage::GetResource(const char *p_sName)
	{
		Assets::const_iterator it = m_aAssets.find(p_sName);
		if(it != m_aAssets.end())
		{
			// check if it is already loaded.
			if(it->second.m_pStream)
			{
				return it->second.m_pStream;
			}

			return CreateResource(it->second.m_nPosition);
		}

		return NULL;
	}

	// Retrieves path of the specified stream.
	const char *CPackageStorage::GetPath(const char *p_sName) const
	{
		return p_sName;
	}

	// Reload location.
	void CPackageStorage::Reload()
	{
		m_oFile.Seek(0, e_SD_Begin);

		// SAMPACK!
		char sSignature[8];
		m_oFile.Read(sSignature, 8);
		if(strcmp(sSignature, "SAMPACK!") == 0)
		{
			SamLogError("It is not a sam package %s", GetFullPath());
			return;
		}


		// Version number.
		uint32 nVersion = 0;
		m_oFile.Read(&nVersion, 32);
		if(nVersion != ms_nVersion)
		{
			SamLogError("Wrong version number %d, required: %d for the package", nVersion, ms_nVersion, GetFullPath());
			return;
		}

		// Retrieves the number of assets.
		uint32 nNbAssets = 0;
		m_oFile.Read(&nNbAssets, 32);

		// Read asset header.
		while(nNbAssets--)
		{
			SAsset oAsset;
			m_oFile.Read(&oAsset, sizeof(SAsset));

			m_aAssets.insert(Assets::value_type(oAsset.m_sName, oAsset));
		}
	}

	// Create resource from package file.
	IStream *CPackageStorage::CreateResource(uint32 p_nPosition)
	{
		uint32 nAssetSize = 0;

		m_oFile.Seek(p_nPosition, e_SD_Begin);
		m_oFile.Read(&nAssetSize, 32);

		uint8 *pBuffer = SAM_ALLOC_ARRAY(uint8, nAssetSize);
		m_oFile.Read(pBuffer, nAssetSize);

		return SAM_NEW CMemoryStream(pBuffer, nAssetSize, true);
	}
}
