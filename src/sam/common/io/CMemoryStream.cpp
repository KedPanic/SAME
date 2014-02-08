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
#include "common/io/CMemoryStream.h"

namespace sam
{
	/// @brief Constructor.
	///
	/// @param _pBuffer Pointer to an allocated block of memory.
	/// @param _iSize Size of the buffer.
	/// @param _bFreeOnClose true if we must to delete the memory when the stream is destroyed.
	CMemoryStream::CMemoryStream(void *_pBuffer, uint32 _iSize, bool _bFreeOnClose /*= false*/)
		: sam::IStream(_bFreeOnClose), m_pBuffer((uint8*)_pBuffer), m_nPosition(0), m_iLength(_iSize)
	{
	}

	/// @brief Destructor.
	CMemoryStream::~CMemoryStream(void)
	{
		Close();
	}

	/// @brief Close the stream.
	void CMemoryStream::Close(void)
	{
		SAM_ASSERT(m_pBuffer != 0, "m_pBuffer is null");

		if(m_bFreeOnClose)
		{
			SAM_FREE(m_pBuffer);
		}
	}

	// Read a block of bytes and store it in the buffer.
	uint32 CMemoryStream::Read(void *p_pBuffer, uint32 p_nSize)
	{
		SAM_ASSERT(p_pBuffer != 0, "_pBuffer is null");
		SAM_ASSERT(m_pBuffer != 0, "m_pBuffer is null");

		uint32 nSeek = p_nSize <= m_iLength - m_nPosition?p_nSize:m_iLength - m_nPosition;
		memcpy(p_pBuffer, &m_pBuffer[m_nPosition], nSeek);

		m_nPosition += nSeek;
		return nSeek;
	}

	/// @brief Set the position in the stream.
	///
	/// @param _iOffset The new position.
	/// @param _eOrigin Seeking direction.
	/// @return the number of bytes sought.
	uint32 CMemoryStream::Seek(uint32 _iOffset, sam::ESeekDir _eOrigin)
	{
		SAM_ASSERT(m_pBuffer != 0, "m_pBuffer is null");

		int iSeek = 0;
		switch(_eOrigin)
		{
		case e_SD_Begin:
			if(_iOffset < m_iLength)
			{
				m_nPosition = _iOffset;
				iSeek = _iOffset;
			}
			else
			{                
				m_nPosition = m_iLength;
				iSeek = m_iLength;
			}
			break;

		case e_SD_Current:
			m_nPosition += _iOffset;
			if(m_nPosition >= m_iLength)
			{
				iSeek = m_iLength - m_nPosition;
				m_nPosition = m_iLength;                
			}
			else
				iSeek = _iOffset;
			break;

		case e_SD_End:
			if(_iOffset < m_iLength)
			{
				m_nPosition = m_iLength - _iOffset;
				iSeek = _iOffset;
			}
			else
			{
				m_nPosition = 0;
				iSeek = m_iLength;
			}
			break;
		}

		return iSeek;
	}

	/// @brief Get the current position in the stream.
	/// 
	/// @return the current position in the stream.
	uint32 CMemoryStream::Tell(void)
	{
		return m_nPosition;
	}

	/// @brief Get the size of the stream.
	/// 
	/// @return the size of the stream.
	uint32 CMemoryStream::Size(void)
	{
		return m_iLength;
	}

	/// @brief Get true if the end of the stream is reached.
	///
	/// @return true if the end of the stream is reached.
	bool CMemoryStream::Eof(void) const
	{
		return (m_nPosition == m_iLength);
	}

	/// @brief Get the data of the stream.
	///
	/// @return data of the stream.
	uint8 *CMemoryStream::Data(void)
	{
		return m_pBuffer;
	}
}
