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
#include "common/io/CXMLSerializer.h"
#include "common/io/ISerializable.h"
#include "common/base/StringUtil.h"

#include <tinyxml.h>

namespace sam
{
	// Helper method to deserialize
	/*void Deserialize(TiXmlElement *pElement)
	{
		// 
		if(!pElement)
			return;

		while(pElement)
		{
			SerializableRegistry::Deserialize(pElement->Value(), this);

			Deserialize(pElement->FirstChildElement());

			pElement = pElement->NextSiblingElement();
		}	
	}*/

	/// @brief Constructor
	/// 
	/// @param _sFilename Name of the file.
	CXMLSerializer::CXMLSerializer(const char *_sFilename)
		: m_sFilename(_sFilename), m_bRead(false), m_pXmlHandler(NULL), m_pCurrentElement(NULL)
	{
	}

	// Called at starting (de)serialization
	bool CXMLSerializer::BeginSerialization(bool _bRead, const char *_sName)
	{
		m_pXmlHandler = SAM_ALLOC(TiXmlDocument);

		m_bRead = _bRead;
		// read
		if(_bRead)
		{
			if(m_pXmlHandler->LoadFile(m_sFilename))
			{  
                m_pCurrentElement = m_pXmlHandler->RootElement();
                SAM_ASSERT(strcmp(_sName, m_pCurrentElement->Value()) == 0, "Bad serialize name");
// 				if( (m_pCurrentElement = m_pXmlHandler->FirstChildElement()) != NULL)
// 				{
//                     SAM_ASSERT(strcmp(_sName, m_pCurrentElement->Value()) == 0, "Bad serialize name");
// 				}				
// 				else 
// 					SamLogError("Unable to get first child element in the XML file '%s'", m_sFilename);
 			}
 			else
			{
				SamLogError("Unable to load XML file '%s'", m_sFilename);
				return false;
			}

			return true;
		}

        m_pCurrentElement = new TiXmlElement(_sName);
		return true;
	}

	/// @brief Called at ending serialization
	void CXMLSerializer::EndSerialization()
	{
		// need to save the file ?
		if(!m_bRead)
		{      
            m_pXmlHandler->LinkEndChild(m_pCurrentElement);
			m_pXmlHandler->SaveFile(m_sFilename);
		}

		SAM_FREE(m_pXmlHandler);
		m_pXmlHandler = NULL;
	}

	/// @brief Start serializable
	/// 
	/// @param _pPtr Pointer to the serializable.
	void CXMLSerializer::Begin(ISerializable *_pPtr)
	{
		SAM_ASSERT(_pPtr != NULL, "_pPtr is NULL");

        if(!m_bRead)
        {
             TiXmlElement *pElement = new TiXmlElement(_pPtr->GetSerializeName());
             if(m_pCurrentElement)
                 m_pCurrentElement->LinkEndChild(pElement);
             else
                 m_pCurrentElement = pElement;
        }
		else
		{
			SAM_ASSERT(m_pCurrentElement != NULL, "m_pCurrentElement is NULL");

			m_pCurrentElement = m_pCurrentElement->FirstChildElement(_pPtr->GetSerializeName());
		}
	}

	/// @brief End of serializable
	void CXMLSerializer::End()
	{
        if(m_pCurrentElement->Parent())
            m_pCurrentElement = (TiXmlElement*)m_pCurrentElement->Parent();
	}

	/// @brief Start element
	/// 
	/// @param _sElement Name of the element.
	/// 
	/// @return false if the element doesn't exist.
	bool CXMLSerializer::BeginElem(const char *_sElement)
	{
		SAM_ASSERT(m_pCurrentElement != NULL, "m_pCurrentElement is NULL");

        TiXmlElement *pChildElement = NULL;
        if(m_bRead)
        {
		    pChildElement = m_pCurrentElement->NextSiblingElement(_sElement);
            if(pChildElement == NULL) // no more next element !
			{
				// try to find child element !
				pChildElement = m_pCurrentElement->FirstChildElement(_sElement);
				if(pChildElement == NULL) // unable to find child element !
				{
					return false;
				}
			}
        }
        else
        {
            pChildElement = (TiXmlElement*)m_pCurrentElement->LinkEndChild(new TiXmlElement(_sElement));
        }

        m_pCurrentElement = pChildElement;
		return true;
	}

	// Ending current element
	void CXMLSerializer::EndElem()
	{
        //m_pCurrentElement = (TiXmlElement*)m_pCurrentElement->Parent();
	}

	// Read value with specified name.
	char *CXMLSerializer::ReadValue(const char *p_sName)
	{
		const char *sValue = NULL;
		if( (sValue = m_pCurrentElement->Attribute(p_sName)) == NULL)
		{
			SamLogError("Unable to get value of the attribute '%s' in the current element in the XML file '%s'", p_sName, m_sFilename);
			return NULL;
		}

		char *sResult = SAM_ALLOC_ARRAY(char, strlen(sValue) + 1);
		strcpy(sResult, sValue);

		return sResult;
	}

	// Read value with specified name.
	void CXMLSerializer::ReadValue(const char *p_sName, bool  &p_bValue)
	{
#ifdef TIXML_USE_STL
		if(m_pCurrentElement->QueryValueAttribute<bool>(p_sName, &p_bValue) == TIXML_WRONG_TYPE)
		{
			SamLogError("Unable to get value of the attribute '%s' in the current element in the XML file '%s'", p_sName, m_sFilename);
		}
#else
		int iValue;
		if(m_pCurrentElement->QueryIntAttribute(p_sName, &iValue) == TIXML_WRONG_TYPE)
		{
			SamLogError("Unable to get value of the attribute '%s' in the current element in the XML file '%s'", p_sName, m_sFilename);
		}

		p_bValue = iValue != 0;
#endif
	}

	void CXMLSerializer::ReadValue(const char *p_sName, int   &p_nValue)
	{
		if(m_pCurrentElement->Attribute(p_sName, &p_nValue) != "i")
		{
			SamLogError("Unable to get value of the attribute '%s' in the current element in the XML file '%s'", p_sName, m_sFilename);
		}
	}

	void CXMLSerializer::ReadValue(const char *p_sName, uint32 &p_nValue)
	{
		int nValue = 0;
		ReadValue(p_sName, nValue);

		p_nValue = nValue;
	}

	void CXMLSerializer::ReadValue(const char *p_sName, Vector3 &p_vValue)
	{
		const char *pAttr = NULL;
		if( (pAttr = const_cast<char*>(m_pCurrentElement->Attribute(p_sName))) == NULL)
		{
			SamLogError("Unable to get value of the attribute '%s' in the current element in the XML file '%s'", p_sName, m_sFilename);
		}
		else
		{
			VString vValue = split(pAttr, ",");
			if(vValue.size() < 3)
			{
				SamLogError("Unable to get value of the attribute '%s' in the current element in the XML file '%s'", p_sName, m_sFilename);
			}
			else
			{
				while(vValue.empty())
				{
					p_vValue[vValue.size() - 1] = parseValue<float>(vValue.back());
					vValue.pop_back();
				}
			}
		}
	}

	void CXMLSerializer::ReadValue(const char *p_sName, float &p_fValue)
	{
		if(m_pCurrentElement->QueryFloatAttribute(p_sName, &p_fValue) == TIXML_WRONG_TYPE)
		{
			SamLogError("Unable to get value of the attribute '%s' in the current element in the XML file '%s'", p_sName, m_sFilename);
		}
	}

	void CXMLSerializer::ReadValue(const char *p_sName, float p_afValue[4])
	{
		const char *pAttr = NULL;
		if( (pAttr = const_cast<char*>(m_pCurrentElement->Attribute(p_sName))) == NULL)
		{
			SamLogError("Unable to get value of the attribute '%s' in the current element in the XML file '%s'", p_sName, m_sFilename);
		}
		else
		{
			VString vValue = split(pAttr, ",");
			if(vValue.size() < 4)
			{
				SamLogError("Unable to get value of the attribute '%s' in the current element in the XML file '%s'", p_sName, m_sFilename);
			}
			else
			{
				while(vValue.empty())
				{                        
					p_afValue[vValue.size() - 1] = parseValue<float>(vValue.back());
					vValue.pop_back();
				}
			}
		}
	}

	/// @brief Write value with specified name.
	/// 
	/// @param p_sName Name of the value
	/// @param p_*Value Value.
	void CXMLSerializer::WriteValue(const char *p_sName, const bool  &p_bValue)
	{
		m_pCurrentElement->SetAttribute(p_sName, p_bValue);
	}

	void CXMLSerializer::WriteValue(const char *p_sName, const int   &p_nValue)
	{
		m_pCurrentElement->SetAttribute(p_sName, p_nValue);
	}

	void CXMLSerializer::WriteValue(const char *p_sName, const char *p_sValue)
	{
		m_pCurrentElement->SetAttribute(p_sName, p_sValue);
	}

	void CXMLSerializer::WriteValue(const char *p_sName, const Vector3 &p_vValue)
	{
		char sBuffer[256] = {'\0'};
		sprintf(sBuffer, "%f,%f,%f", toStringT<float>(p_vValue.x), toStringT<float>(p_vValue.y), toStringT<float>(p_vValue.z));
		m_pCurrentElement->SetAttribute(p_sName, sBuffer);
	}

	void CXMLSerializer::WriteValue(const char *p_sName, const float &p_fValue)
	{
		m_pCurrentElement->SetDoubleAttribute(p_sName, p_fValue);
	}

	void CXMLSerializer::WriteValue(const char *p_sName, const float p_afValue[4])
	{
		char pBuffer[16] = {'\0'};
		sprintf(pBuffer, "%f,%f,%f", toStringT<float>(p_afValue[0]), toStringT<float>(p_afValue[1]), toStringT<float>(p_afValue[2]), toStringT<float>(p_afValue[3]));
		m_pCurrentElement->SetAttribute(p_sName, pBuffer);
	}
}

