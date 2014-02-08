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
#include "SamEntitySystemPCH.h"
#include "components/CMesh.h"

#include "CComponentManager.h"
#include "components/CTransform.h"
#include "CGameObject.h"

namespace sam
{
	namespace scene
	{
		IMPLEMENT_COMPONENT(CMesh);

		//////////////////////////////////////////////////////////////////////////
		//					TRANSFORM SYSTEM IMPLEMENTATION						//
		//////////////////////////////////////////////////////////////////////////
		void CMesh::Update(f32 p_fDelta)
		{
			for(uint32 nIndex = 0; nIndex < s_oObjectPool.GetCount(); ++nIndex)
			{
				CMesh *pCamera = s_oObjectPool[nIndex];

				// update position and orientation from transform.

			}
		}
		//////////////////////////////////////////////////////////////////////////

		// Default constructor.
		CMesh::CMesh()
			: m_pMesh(NULL)
		{

		}

		//  Load mesh from memory buffer.
		bool CMesh::LoadMesh(uint8 *p_pBuffer, uint32 p_nSize)
		{
			m_pMesh = SAM_NEW sam::CMesh;
			return m_pMesh->CreateMesh(p_pBuffer, p_nSize);
		}
	}	
}
