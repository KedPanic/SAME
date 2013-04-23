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
#include "common/io/ISerializable.h"
#include "common/io/ISerializer.h"
#include "common/io/CXMLSerializer.h"
#include "common/io/CJSONSerializer.h"

namespace sam
{
	SerializableRegistry::SSerializables *SerializableRegistry::m_pSerializables = NULL;

    /// @brief Remove all serializable.
    void SerializableRegistry::RemoveAllSerializables(void)
    {
        SSerializables *pSerializable = m_pSerializables;
        while(pSerializable)
        {                                
            SSerializables *pNextSerializable = pSerializable->m_pNext;

            SAM_DELETE pSerializable;
            pSerializable = pNextSerializable;
        }

        m_pSerializables = NULL;
    }

    /// @brief Register serializable pointer function
    static void RegisterSerializable();
    void SerializableRegistry::RegisterSerializable(const char *p_sName, CreateInstance p_pfCreateInstanceFunc)
    {
        SAM_ASSERT(p_sName != NULL, "p_sName is NULL, unable to register it.");

        SamLog("Register serializable '%s'", p_sName);
        SSerializables *pNode = SAM_NEW SSerializables;
        pNode->m_sName = p_sName;
        pNode->m_pfCreateInstance = p_pfCreateInstanceFunc;
        pNode->m_pNext = m_pSerializables;  

        m_pSerializables = pNode;
    }

    /// @brief Called by the serializer to (de)serialize.
    void SerializableRegistry::Serialize(const char *_sName, ISerializer *_pContext)
    {
        SSerializables *pSerializable = m_pSerializables;
        while(pSerializable)
        {
            if(strcmp(pSerializable->m_sName, _sName) == 0)
            {
				if(_pContext->IsReading())
				{
				}
				else
				{
					_pContext->BeginElem(pSerializable->m_sName);
					pSerializable->m_pfCreateInstance()->Write(_pContext);
					_pContext->EndElem();
				}
                return;
            }

            pSerializable = pSerializable->m_pNext;
        }

        SamLogError("Unable to find serializable with name '%s'", _sName);
    }

    namespace helper
    {
        /// @brief Helper method to serialize/deserialize.
        bool Serialize(ESerializerType p_eSerialiazerType, ISerializable *p_pSerializable, const char *p_sFilename, bool p_bReading /*= false*/)
        {
            SAM_ASSERT(p_eSerialiazerType != e_Serializer_Custom, "Custom serializer is not supported.");

            switch(p_eSerialiazerType)
            {
            case e_Serializer_Binary:
                SAM_ASSERT(false, "Not supported yet");
                break;

            case e_Serializer_XML:
				{
					CXMLSerializer oSerializer(p_sFilename);
					oSerializer.BeginSerialization(p_bReading, p_pSerializable->GetSerializeName());
					if(p_bReading)
					{
						p_pSerializable->Read(&oSerializer);
					}
					else
					{
						p_pSerializable->Write(&oSerializer);
					}
					oSerializer.EndSerialization();
				}
                break;

			case e_Serializer_JSon:
				{
// 					CJSONSerializer oSerializer(p_sFilename);
// 					oSerializer.BeginSerialization(p_bReading, p_pSerializable->GetSerializeName());
// 					if(p_bReading)
// 					{
// 						p_pSerializable->Read(&oSerializer);
// 					}
// 					else
// 					{
// 						p_pSerializable->Write(&oSerializer);
// 					}
// 					oSerializer.EndSerialization();
				}
				break;

            }

            return true;
        }
    }
}
