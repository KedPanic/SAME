//===========================================
// Copyright (C) 2013-2014 Stone Age Machine
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
#include "SamBox.h"
#include "CPlatform.h"

// Default constructor.
CPlatform::CPlatform()
{	
	m_nId = sam::InvalidId;
}

CPlatform::~CPlatform()
{

}

// Read the configuration file.
void CPlatform::Initialize(const char *p_sFilename)
{
	sam::CJSONSerializer oSerializer(p_sFilename);
	oSerializer.BeginSerialization(true, "platform");
	oSerializer.BeginElem("platform");
	{
		m_sName = oSerializer.ReadValue("name");

		while(oSerializer.BeginElem("exporter"))
		{		
			uint32 nResourceType = oSerializer.ReadIntValue("type");
			SAM_ASSERT(nResourceType < e_ResourceType_Nb, "Bad resource type");
			m_pExportName[nResourceType] = oSerializer.ReadValue("name");
			oSerializer.EndElem();
		}
	}
	oSerializer.EndElem();
	oSerializer.EndSerialization();

	m_nId = sam::CreateID(m_sName.c_str(), m_sName.size());
}

// Manual creation.
void CPlatform::Initialize(const char *p_sName, const char *p_aExportName[e_ResourceType_Nb])
{
	m_sName = p_sName;

	for(uint32 nIndex = 0; nIndex < e_ResourceType_Nb; ++nIndex)
	{
		m_pExportName[nIndex] = p_aExportName[nIndex];
	}

	m_nId = sam::CreateID(m_sName.c_str(), m_sName.size());
}
