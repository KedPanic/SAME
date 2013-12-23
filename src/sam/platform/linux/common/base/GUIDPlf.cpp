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
#include "common/base/GUIDUtil.h"

namespace sam
{
	/// @brief GUID is used to save and load game objects.
	namespace guid
	{
		// Generate a GUID.
		GUID Generate()
		{
			GUID oGUID;
            SAM_UNIMPLEMENTED;

			return oGUID;
		}

		// Generate a GUID from string.
		GUID FromString(const String &_sGUID)
		{
			GUID tGUID;

			sscanf(_sGUID.c_str(), "{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
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

		// Generate a GUID from uint64.
		String ToString(const GUID &_GUID)
		{
			SAM_UNIMPLEMENTED;

			return "";
		}
	}
}