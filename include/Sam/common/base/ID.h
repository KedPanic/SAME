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
#ifndef __SAM_ID_H__
#define __SAM_ID_H__

namespace sam
{	
#if defined(SAM_DEBUG)
	class SAM_COMMON_API ID
	{
	public:
		// Default constructor.
		ID();		
		ID(uint32 p_nID);
		ID(const ID &p_nID);

		ID& operator =(const ID &p_oID)
		{
			if(&p_oID != this)
			{
				m_nID = p_oID.m_nID;
				m_sID = p_oID.m_sID;
			}

			return *this;
		}

		bool operator ==(const ID &p_oID) const
		{
			return m_nID == p_oID.m_nID;
		}

		uint32 GetID()
		{
			return m_nID;
		}

		void SetReadableID(const char *p_sID);
		const char *GetReadableID() const;

	private:
		uint32 m_nID;	///< Integer ID generated from String.
		String m_sID;	///< Readable ID for debug only.
	};
#else
	typedef uint32 ID;
#endif

	/// @brief Create unique ID from string.
	/// 
	/// @param p_nStringID String to generate an integer ID.
	/// @param p_nSize String size.
	/// 
	/// @return Generated ID.
	extern SAM_COMMON_API ID CreateID(const char *p_nStringID, uint32 p_nSize);
}
#endif // __CSTRING_ID_H__
