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
#include <common/SamPCH.h>
#include "common/base/GUIDUtil.h"

#include <Rpc.h>

namespace sam
{
	/// @brief GUID is used to save and load game objects.
	namespace guid
	{
		// Helper method : convert windows api GUID to terre adelie GUID
		GUID convert(const ::GUID &_GUID)
		{
			GUID rGUID;

			rGUID.Data1 = _GUID.Data1;
			rGUID.Data2 = _GUID.Data2;
			rGUID.Data3 = _GUID.Data3;

			for(int i = 0; i < 8; i++)
				rGUID.Data4[i] = _GUID.Data4[i];

			return rGUID;
		}

		::GUID convert(const GUID &_GUID)
		{
			::GUID rGUID;

			rGUID.Data1 = _GUID.Data1;
			rGUID.Data2 = _GUID.Data2;
			rGUID.Data3 = _GUID.Data3;

			for(int i = 0; i < 8; i++)
				rGUID.Data4[i] = _GUID.Data4[i];

			return rGUID;
		}

		/// @brief Generate a GUID.
		/// 
		/// @return a new GUID.
		GUID Generate()
		{
			/* generate guid */
			::GUID rGUID;
			if(CoCreateGuid(&rGUID) != S_OK)
			{				
				// TODO : LOG ERROR
			}

			return convert(rGUID);
		}

		/// @brief Generate a GUID from string.
		/// 
		/// @param _sGUID GUID string
		GUID FromString(const String &_sGUID)
		{			
			GUID tGUID;

			sscanf_s(_sGUID.c_str(), "{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}", 
				&tGUID.Data1,
				&tGUID.Data2,
				&tGUID.Data3,
				&tGUID.Data4[0],
				&tGUID.Data4[1],
				&tGUID.Data4[2],
				&tGUID.Data4[3],
				&tGUID.Data4[4],
				&tGUID.Data4[5],
				&tGUID.Data4[6],
				&tGUID.Data4[7]);

			return tGUID;
		}

		/// @brief Generate a GUID from uint64.
		/// 
		/// @param _iGUID GUID uint64
		String ToString(const GUID &_GUID)
		{
			/* convert to string */
			wchar_t szWGuid[64];
			StringFromGUID2(convert(_GUID), szWGuid, sizeof(szWGuid));

			/* Convert wide char string to ansi string */
			char szGUID[64];
			int nRet = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, szWGuid, sizeof(szWGuid), szGUID, sizeof(szGUID), NULL, NULL);

			return szGUID;
		}
	}
}
