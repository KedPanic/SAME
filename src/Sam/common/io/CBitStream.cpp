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
#include "common/io/CBitStream.h"

namespace sam
{
	CBitStream::CBitStream()
		: m_nSize(0), m_pWriteBuffer(NULL), m_nWritePos(0), m_nWritePosBit(0), m_pReadBuffer(NULL), m_nReadPos(0), m_nReadPosBit(0)
	{

	}

	CBitStream::~CBitStream()
	{

	}

	// Initialize the bit stream for write.
	void CBitStream::Init(uint8 *p_pBuffer, uint32 p_nSize)
	{
		m_pWriteBuffer = p_pBuffer;
		m_pReadBuffer = p_pBuffer;
		m_nSize = p_nSize;
		m_nReadPos = 0;
		m_nReadPosBit = 0;
		m_nWritePos = 0;
		m_nWritePosBit = 0;
	}

	// Initialize the bit stream for read only.
	void CBitStream::Init(const uint8 *p_pBuffer, uint32 p_nSize)
	{
		m_pWriteBuffer = NULL;
		m_pReadBuffer = p_pBuffer;
		m_nSize = p_nSize;
		m_nReadPos = 0;
		m_nReadPosBit = 0;
	}

	//////////////////////////////////////////////////////////////////////////
	//								WRITE OPERATION							//
	//////////////////////////////////////////////////////////////////////////
	void CBitStream::WriteBits(int32 p_nValue, uint32 p_nNbBits)
	{
		SAM_ASSERT(m_pWriteBuffer != NULL, "Uninitialized bit stream");
		SAM_ASSERT(p_nNbBits > 0 && p_nNbBits <= 32, "Unsupported size value %d", p_nNbBits);		
		SAM_ASSERT(m_nWritePosBit + p_nNbBits < m_nSize, "Overflow");

		if(p_nNbBits != 32)
		{
			SAM_ASSERT(p_nValue <= (1 << p_nNbBits) - 1, "Value overflow %d %d", p_nValue, p_nNbBits);
		}
		

		uint32 nNbBitsToWrite = 0;
		while(p_nNbBits)
		{
			if(m_nWritePosBit == 0)
			{
				m_pWriteBuffer[m_nWritePos] = 0;
				m_nWritePos++;				
			}

			nNbBitsToWrite = p_nNbBits;
			if(nNbBitsToWrite > 8 - m_nWritePosBit)
			{
				nNbBitsToWrite = 8 - m_nWritePosBit;
			}

			m_pWriteBuffer[m_nWritePos - 1] |= (p_nValue >> (p_nNbBits - nNbBitsToWrite)) << (8 - m_nWritePosBit - nNbBitsToWrite);

			p_nNbBits -= nNbBitsToWrite;
			m_nWritePosBit = (m_nWritePosBit + nNbBitsToWrite) & 7;			
		}
	}

	void CBitStream::WriteString(const char *p_sBuffer, uint32 p_nSize)
	{
		SAM_ASSERT(m_pWriteBuffer != NULL, "Unitialized bit stream");		

		// string are still aligned.
		if(m_nWritePosBit != 0)
		{
			m_nWritePosBit = 0;
			m_nWritePos++;
		}

		SAM_ASSERT(m_nWritePos + p_nSize < m_nSize, "Overflow");

		uint32 nStringSize = strlen(p_sBuffer) + 1;
		memcpy(&m_pWriteBuffer[m_nWritePos], p_sBuffer, nStringSize);
		m_nWritePos += nStringSize;
	}

	void CBitStream::WriteData(const uint8 *p_sBuffer, uint32 p_nSize)
	{
		SAM_ASSERT(m_pWriteBuffer != NULL, "Unitialized bit stream");		

		// data are still aligned.
		if(m_nWritePosBit != 0)
		{
			m_nWritePosBit = 0;
			m_nWritePos++;
		}

		SAM_ASSERT(m_nWritePos + p_nSize < m_nSize, "Overflow");
		memcpy(&m_pWriteBuffer, p_sBuffer, p_nSize);
		m_nWritePos += p_nSize;
	}

	//////////////////////////////////////////////////////////////////////////
	//								READ OPERATION							//
	//////////////////////////////////////////////////////////////////////////
	int32 CBitStream::ReadBits(uint32 p_nNbBits)
	{
		SAM_ASSERT(m_pReadBuffer != NULL, "Uninitialized bit stream");
		SAM_ASSERT(p_nNbBits > 0 && p_nNbBits <= 32, "Unsupported size value %d", p_nNbBits);

		int32 nValue = 0;
		uint32 nNbBitsRead = 0;
		while(p_nNbBits)
		{
			if(m_nReadPosBit == 0)
			{
				m_nReadPos++;
			}

			nNbBitsRead = p_nNbBits;
			if(nNbBitsRead > 8 - m_nReadPosBit)
			{
				nNbBitsRead = 8 - m_nReadPosBit;
			}

			nValue |= ((m_pReadBuffer[m_nReadPos - 1] >> (8 - m_nReadPosBit - nNbBitsRead)) & ((1 << nNbBitsRead) - 1)) << (p_nNbBits - nNbBitsRead);

			p_nNbBits -= nNbBitsRead;
			m_nReadPosBit = (m_nReadPosBit + nNbBitsRead) & 7;			
		}

		return nValue;
	}

	uint32 CBitStream::ReadString(char *p_sBuffer, uint32 p_nBufferSize)
	{
		SAM_ASSERT(m_pReadBuffer != NULL, "Unitialized bit stream");		

		// string are still aligned.
		if(m_nReadPosBit != 0)
		{
			m_nReadPosBit = 0;
			m_nReadPos++;
		}

		SAM_ASSERT(m_nReadPos + p_nBufferSize < m_nSize, "Overflow");
		uint32 nNbBytesRead = 0;
		while(true)
		{
			char c = ReadByte();			

			p_sBuffer[nNbBytesRead] = c;
			nNbBytesRead++;

			SAM_TRAP(nNbBytesRead < m_nSize);
			if(c == '\0')
			{
				break;
			}
		}

		return nNbBytesRead;
	}

	uint32 CBitStream::ReadData(uint8 *p_sBuffer, uint32 p_nBufferSize)
	{
		SAM_ASSERT(m_pReadBuffer != NULL, "Unitialized bit stream");		

		// string are still aligned.
		if(m_nReadPosBit != 0)
		{
			m_nReadPosBit = 0;
			m_nReadPos++;
		}

		uint32 nNbBytesRead = p_nBufferSize;
		if(m_nReadPos + p_nBufferSize >= m_nSize)
		{
			nNbBytesRead = m_nSize - m_nReadPos;
		}
		memcpy(p_sBuffer, &m_pReadBuffer[m_nReadPos], nNbBytesRead);
		m_nReadPos += nNbBytesRead;

		return nNbBytesRead;
	}
}
