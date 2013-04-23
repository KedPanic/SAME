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
#include "common/base/ID.h"
#include "common/base/StringUtil.h"

namespace sam
{
	// Create unique ID from string.
	// see http://en.wikipedia.org/wiki/Jenkins_hash_function
	ID CreateID(const char *p_nStringID, uint32 p_nSize)
	{
		uint32 nHash = 0;
		for(uint32 i = 0; i < p_nSize; ++i)
		{
			nHash += p_nStringID[i];
			nHash += (nHash << 10);
			nHash ^= (nHash >> 6);
		}

		nHash += (nHash << 3);
		nHash ^= (nHash >> 11);
		nHash += (nHash << 15);

#if defined(SAM_DEBUG)
		ID oID(nHash);
		oID.SetReadableID(p_nStringID);

		return oID;
#else
		return nHash;
#endif
	}

	// Default constructor.
	ID::ID()
		: m_nID(-1)
	{
	}

	ID::ID(uint32 p_nID)
		: m_nID(p_nID)
	{
	}

	void ID::SetReadableID(const char *p_sID)
	{
		SAM_ASSERT(p_sID != NULL, "ID String is null");

		m_sID = p_sID;
	}

	const char *ID::GetReadableID()
	{
		if(m_sID.empty())
		{
			m_sID = toStringT(m_nID);
		}

		return m_sID.c_str();
	}
}
