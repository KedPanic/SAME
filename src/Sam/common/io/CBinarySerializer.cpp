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
#include "common/io/CBinarySerializer.h"

namespace sam
{
	// Constructor.
	CBinarySerializer::CBinarySerializer(const char *p_sFilename)
		: m_sFilename(p_sFilename)
	{
	}

	// Called at starting (de)serialization
	bool CBinarySerializer::BeginSerialization(bool p_bRead, const char *p_sName)
	{
		m_bRead = p_bRead;
		int32 nFlags = e_OM_Binary;
		if(m_bRead)
		{
			nFlags |= e_OM_Read;
		}
		else
		{
			nFlags |= e_OM_Write;
		}

		return m_oFile.Open(m_sFilename, nFlags);
	}

	// Called at ending serialization
	void CBinarySerializer::EndSerialization()
	{
	}

	// Start serializable
	void CBinarySerializer::Begin(ISerializable *p_pSerializable)
	{
	}

	// End of serializable
	void CBinarySerializer::End()
	{
	}

	// Start element
	bool CBinarySerializer::BeginElem(const char *p_sElement)
	{
		uint32 nSize = strlen(p_sElement);

		SAM_ASSERT(nSize <= s_nBufferSize, "Buffer is too small !");
		
		if(m_bRead)
		{
			uint32 nCurrentPosition = m_oFile.Tell();

			m_oFile.Read(&m_sBuffer, nSize);
			if(strncmp(p_sElement, m_sBuffer, nSize) == 0)
			{
				return true;
			}

			// no more element.
			m_oFile.Seek(nCurrentPosition, e_SD_Begin);
			return false;
		}

		m_oFile.Write(p_sElement, nSize);
		return true;
	}

	// Ending current element
	void CBinarySerializer::EndElem()
	{
	}

	// Read value with specified name.
	char *CBinarySerializer::ReadValue(const char *p_sName)
	{
		uint32 nCurrentPosition = m_oFile.Tell();

		// Compute size.	
		bool bDone = false;
		uint32 nSize = 1;
		while(!bDone)
		{
			uint32 nRead = m_oFile.Read(m_sBuffer, s_nBufferSize);
			bDone = nRead == 0;

			for(uint8 nIndex = 0; nIndex < nRead; ++nIndex)
			{
				if(m_sBuffer[nIndex] == '\0')
				{
					bDone = true;
					break;
				}

				++nSize;
			}			
		}

		// Reset position.
		m_oFile.Seek(nCurrentPosition, e_SD_Begin);

		// Copy.
		char *sValue = SAM_ALLOC_ARRAY(char, nSize);
		m_oFile.Read(sValue, nSize);

		return sValue;
	}

	// Read value with specified name.
	void CBinarySerializer::ReadValue(const char *p_sName, bool  &p_bValue)
	{
		m_oFile.Read(&p_bValue, sizeof(bool));
	}

	void CBinarySerializer::ReadValue(const char *p_sName, int   &p_nValue)
	{
		m_oFile.Read(&p_nValue, sizeof(int));
	}

	void CBinarySerializer::ReadValue(const char *p_sName, uint32  &p_nValue)
	{
		m_oFile.Read(&p_nValue, sizeof(uint32));
	}

	void CBinarySerializer::ReadValue(const char *p_sName, Vector3 &p_vValue)
	{
		m_oFile.Read(&p_vValue, sizeof(Vector3));
	}

	void CBinarySerializer::ReadValue(const char *p_sName, float &p_fValue)
	{
		m_oFile.Read(&p_fValue, sizeof(float));
	}

	void CBinarySerializer::ReadValue(const char *p_sName, float p_afValue[4])
	{
		m_oFile.Read(p_afValue, sizeof(float) * 4);
	}

	// Write value with specified name.
	void CBinarySerializer::WriteValue(const char *p_sName, const bool  &p_bValue)
	{
		m_oFile.Write(&p_bValue, sizeof(bool));
	}

	void CBinarySerializer::WriteValue(const char *p_sName, const int   &p_nValue)
	{
		m_oFile.Write(&p_nValue, sizeof(int));
	}

	void CBinarySerializer::WriteValue(const char *p_sName, const uint32  &p_nValue)
	{
		m_oFile.Write(&p_nValue, sizeof(uint32));
	}

	void CBinarySerializer::WriteValue(const char *p_sName, const char *p_sValue)
	{
		m_oFile.Write(p_sValue, strlen(p_sValue) + 1);
	}

	void CBinarySerializer::WriteValue(const char *p_sName, const Vector3 &p_vValue)
	{
		m_oFile.Write(&p_vValue, sizeof(Vector3));
	}

	void CBinarySerializer::WriteValue(const char *p_sName, const float &p_fValue)
	{
		m_oFile.Write(&p_fValue, sizeof(float));
	}

	void CBinarySerializer::WriteValue(const char *p_sName, const float p_afValue[4])
	{
		m_oFile.Write(p_afValue, sizeof(float) * 4);
	}
}
