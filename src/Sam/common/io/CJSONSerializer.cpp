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
#include "common/io/cJSON.h"
#include "common/io/CJSONSerializer.h"
#include "common/io/ISerializable.h"
#include "common/base/StringUtil.h"
#include "common/io/CFile.h"

namespace sam
{
	/// @brief Constructor
	/// 
	/// @param _sFilename Name of the file.
	CJSONSerializer::CJSONSerializer(const char *_sFilename)
		: m_sFilename(_sFilename), m_bRead(false), m_pRoot(NULL), m_pCurrentElement(NULL)
	{
	}

	// Called at starting (de)serialization
	bool CJSONSerializer::BeginSerialization(bool _bRead, const char *_sName)
	{
		m_bRead = _bRead;
		// read
		if(m_bRead)
		{
            CFile file;
            if(file.Open(m_sFilename, e_OM_Read))
            {
                return BeginSerialization(file.Data(), file.Size(), _sName);
            }            
		}
        else
        {
            m_pCurrentElement = m_pRoot = cJSON_CreateObject();
			return true;
        }

		return false;
	}

	// Called at starting (de)serialization
	bool CJSONSerializer::BeginSerialization(uint8 *p_pBuffer, uint32 p_nSize, const char *p_sName)
	{
		m_pRoot = cJSON_Parse((char*)p_pBuffer);
		if(m_pRoot == NULL)
		{
			return false;
		}

		// check if the file is not empty.
		if(m_pRoot->child)
		{
			m_pCurrentElement = m_pRoot->child;
		}
		else
		{
			m_pCurrentElement = m_pRoot;
		}				

		return true;
	}

	/// @brief Called at ending serialization
	void CJSONSerializer::EndSerialization()
	{
		// need to save the file ?
		if(!m_bRead)
		{      
            char *pData = cJSON_Print(m_pRoot);

            // write the file.
            CFile file;
            if(file.Open(m_sFilename, e_OM_Write))
            {
                file.Write(pData, strlen(pData));
                file.Close();
            }

            SAM_FREE(pData);
		}

        cJSON_Delete(m_pRoot);
        m_pRoot = NULL;
	}

	/// @brief Start serializable
	/// 
	/// @param _pPtr Pointer to the serializable.
	void CJSONSerializer::Begin(ISerializable *_pPtr)
	{
		SAM_ASSERT(_pPtr != NULL, "_pPtr is NULL");

        if(!m_bRead)
        {
             cJSON *pElement = cJSON_CreateObject();
             if(m_pCurrentElement)
             {
                 cJSON_AddItemToObject(m_pCurrentElement, _pPtr->GetSerializeName(), pElement);
             }
             
             m_pCurrentElement = pElement;
        }
		else
		{
			SAM_ASSERT(m_pCurrentElement != NULL, "m_pCurrentElement is NULL");

            // check if it is the next element.
            if(strcmp(m_pCurrentElement->next->string, _pPtr->GetSerializeName()) == 0)
            {
                m_pCurrentElement = m_pCurrentElement->next;
            }
            // check if it is the first child.
            else if(strcmp(m_pCurrentElement->child->string, _pPtr->GetSerializeName()) == 0)
            {
                m_pCurrentElement = m_pCurrentElement->child;
            }
		}
	}

	/// @brief End of serializable
	void CJSONSerializer::End()
	{
        if(m_pCurrentElement->prev)
        {
            m_pCurrentElement = m_pCurrentElement->prev;
        }
	}

	// Start element
	bool CJSONSerializer::BeginElem(const char *_sElement)
	{
		/*
		The element are an array with json to simplify the file.
		this is a representation of an object:
		{
			"MyObject" : [{
				"variable_1": "value",
				"variable_2": "value"
				}, {
				"variable_1": "value",
				"variable_2": "value"
				}]
		}
		As you can see there are two declarations of "MyObject".
		*/

        if(m_bRead)
        {           
			// check if we are at the end of the file.
			if(!m_pCurrentElement)
			{
				return false;
			}

			// check if it is the current node.
			if(m_pCurrentElement->string && strcmp(m_pCurrentElement->string, _sElement) == 0)
			{
				m_pCurrentElement = m_pCurrentElement->child;
				return true;
			}

			// check if it is a child node.
			if(m_pCurrentElement->child && m_pCurrentElement->child->string && strcmp(m_pCurrentElement->child->string, _sElement) == 0)
			{
				m_pCurrentElement =  m_pCurrentElement->child->child;
				return true;
			}

			// check if we are already in the array.
			if(m_pCurrentElement->parent)
			{
				if(m_pCurrentElement->parent->type == cJSON_Array)
				{
					if(m_pCurrentElement->parent->string && strcmp(m_pCurrentElement->parent->string, _sElement) == 0)
					{
						return true;
					}
				}
			}

			// check if it is the next node.
			if(!m_pCurrentElement->string || strcmp(m_pCurrentElement->string, _sElement) != 0)
			{
				// check if it is the next element.
				if(m_pCurrentElement->next && strcmp(m_pCurrentElement->next->string, _sElement) == 0)
				{
					m_pCurrentElement = m_pCurrentElement->next;
				}
			}			

			return false; // No elements inside the array.
        }

		SAM_ASSERT(m_pCurrentElement != NULL, "m_pCurrentElement is NULL");

		// check if it is not the current node.
		if(!m_pCurrentElement->string || strcmp(m_pCurrentElement->string, _sElement) != 0)
		{
			cJSON *pArray = cJSON_CreateArray();
			cJSON_AddItemToObject(m_pCurrentElement, _sElement, pArray);

			cJSON *pElement = cJSON_CreateObject();
			cJSON_AddItemToObject(pArray, "", pElement);

			m_pCurrentElement = pElement;
		}
		else
		{
			cJSON *pElement = cJSON_CreateObject();
			cJSON_AddItemToObject(m_pCurrentElement, _sElement, pElement);

			m_pCurrentElement = pElement;
		}

		return true;
	}

	/// @brief Ending current element
	void CJSONSerializer::EndElem()
	{
		if(m_bRead)
		{
			// check if we are at the end of the array.
			if(!m_pCurrentElement)
			{
				// nothing to do
			}

			// find next element
			cJSON *pElement = m_pCurrentElement;
			while(pElement)
			{
				if(pElement->parent && pElement->parent->next)
				{
					pElement = pElement->parent->next;
					break;
				}

				pElement = pElement->parent;
			}

			m_pCurrentElement = pElement;
		}
		else
		{
			m_pCurrentElement = m_pCurrentElement->parent->parent;
		}
	}

	// Read value with specified name.
	char *CJSONSerializer::ReadValue(const char *p_sName)
	{
		// Go to next element.
		NextNode(p_sName);

		SAM_ASSERT(m_pCurrentElement->type == cJSON_String, "Malformated json file '%s', value '%s' is not a string", m_sFilename, p_sName);

		char *sResult = SAM_ALLOC_ARRAY(char, strlen(m_pCurrentElement->valuestring) + 1);
		strcpy(sResult, m_pCurrentElement->valuestring);

		return sResult;
	}

	// Read integer value with specified name.
	int CJSONSerializer::ReadIntValue(const char *p_sName)
	{
		// Go to next element.
		NextNode(p_sName);

		SAM_ASSERT(m_pCurrentElement->type == cJSON_Number, "Malformated json file '%s', value '%s' is not a number", m_sFilename, p_sName);	
		return m_pCurrentElement->valueint;
	}

	// Read value with specified name.
	void CJSONSerializer::ReadValue(const char *p_sName, bool  &p_bValue)
	{
		// Go to next element.
		NextNode(p_sName);

		if(m_pCurrentElement->type == cJSON_False)
		{
			p_bValue = false;
		}
		else if(m_pCurrentElement->type == cJSON_True)
		{
			p_bValue = true;
		}
		else
		{
			SamLogError("Malformated json file '%s', value '%s' is not a boolean", m_sFilename, p_sName);
		}
	}

	void CJSONSerializer::ReadValue(const char *p_sName, int   &p_nValue)
	{
		// Go to next element.
		NextNode(p_sName);

		SAM_ASSERT(m_pCurrentElement->type == cJSON_Number, "Malformated json file '%s', value '%s' is not a number", m_sFilename, p_sName);	
		p_nValue = m_pCurrentElement->valueint;
	}

	void CJSONSerializer::ReadValue(const char *p_sName, uint32 &p_nValue)
	{
		// Go to next element.
		NextNode(p_sName);

		SAM_ASSERT(m_pCurrentElement->type == cJSON_Number, "Malformated json file '%s', value '%s' is not a number", m_sFilename, p_sName);	
		p_nValue = m_pCurrentElement->valueint;
	}

	void CJSONSerializer::ReadValue(const char *p_sName, Vector3 &p_vValue)
	{
		// Go to next element.
		NextNode(p_sName);

		SAM_ASSERT(m_pCurrentElement->type == cJSON_String, "Malformated json file '%s', value '%s' is not a string", m_sFilename, p_sName);

		std::vector<char *> vValue;
		split(m_pCurrentElement->valuestring, ",", vValue);
		if(vValue.size() != 3)
		{
			SamLogError("Malformated json file '%s', value '%s' is not a vector3", m_sFilename, p_sName);
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

	void CJSONSerializer::ReadValue(const char *p_sName, float &p_fValue)
	{
		// Go to next element.
		NextNode(p_sName);

		SAM_ASSERT(m_pCurrentElement->type == cJSON_Number, "Malformated json file '%s', value '%s' is not a real", m_sFilename, p_sName);
		p_fValue = (float)m_pCurrentElement->valuedouble;
	}

	void CJSONSerializer::ReadValue(const char *p_sName, float p_afValue[4])
	{
		// Go to next element.
		NextNode(p_sName);

		SAM_ASSERT(m_pCurrentElement->type == cJSON_String, "Malformated json file '%s', value '%s' is not a string", m_sFilename, p_sName);

		std::vector<char *> vValue;
		split(m_pCurrentElement->valuestring, ",", vValue);
		if(vValue.size() != 4)
		{
			SamLogError("Malformated json file '%s', value '%s' is not a vector4", m_sFilename, p_sName);
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

	// Write value with specified name.
	void CJSONSerializer::WriteValue(const char *p_sName, const bool  &p_bValue)
	{
		if(p_bValue)
		{
			cJSON_AddItemToObject(m_pCurrentElement, p_sName, cJSON_CreateTrue());
		}
		else
		{
			cJSON_AddItemToObject(m_pCurrentElement, p_sName, cJSON_CreateFalse());
		}
	}

	void CJSONSerializer::WriteValue(const char *p_sName, const int   &p_nValue)
	{
		cJSON_AddItemToObject(m_pCurrentElement, p_sName, cJSON_CreateNumber(p_nValue));
	}

	void CJSONSerializer::WriteValue(const char *p_sName, const uint32  &p_nValue)
	{
		cJSON_AddItemToObject(m_pCurrentElement, p_sName, cJSON_CreateNumber(p_nValue));
	}

	void CJSONSerializer::WriteValue(const char *p_sName, const char *p_sValue)
	{
		cJSON_AddItemToObject(m_pCurrentElement, p_sName, cJSON_CreateString(p_sValue));
	}

	void CJSONSerializer::WriteValue(const char *p_sName, const Vector3 &p_vValue)
	{
		char pBuffer[256] = {'\0'};
		sprintf(pBuffer, "%f,%f,%f", toStringT<float>(p_vValue.x), toStringT<float>(p_vValue.y), toStringT<float>(p_vValue.z));         
		cJSON_AddItemToObject(m_pCurrentElement, p_sName, cJSON_CreateString(pBuffer));
	}

	void CJSONSerializer::WriteValue(const char *p_sName, const float &p_fValue)
	{
		cJSON_AddItemToObject(m_pCurrentElement, p_sName, cJSON_CreateNumber(p_fValue));
	}

	void CJSONSerializer::WriteValue(const char *p_sName, const float p_afValue[4])
	{
		char pBuffer[256] = {'\0'};
		sprintf(pBuffer, "%f,%f,%f,%f", toStringT<float>(p_afValue[0]), toStringT<float>(p_afValue[1]), toStringT<float>(p_afValue[2]), toStringT<float>(p_afValue[3]));
		cJSON_AddItemToObject(m_pCurrentElement, p_sName, cJSON_CreateString(pBuffer));
	}

    /// @brief Goto the next node.
    void CJSONSerializer::NextNode(const char *p_sName)
    {
        SAM_ASSERT(m_pCurrentElement != NULL, "Current element is null");

		// go to the first element of the current array.
        if(m_pCurrentElement->child)
        {
			m_pCurrentElement = m_pCurrentElement->child;
        }
        else
        {
            m_pCurrentElement = m_pCurrentElement->next;
        }

        SAM_ASSERT(m_pCurrentElement != NULL, "There is no more element in the json file, malformated file !");
		SAM_ASSERT(strcmp(m_pCurrentElement->string, p_sName) == 0, "There is no element with name '%s' in the json file, malformated file !", p_sName);
    }
}
