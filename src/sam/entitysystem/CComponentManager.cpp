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
#include "CComponentManager.h"
#include "IComponent.h"
#include "CGameObject.h"

namespace sam
{
	namespace scene
	{		
		/// @brief Default constructor.
		CComponentManager::CComponentManager()
		{			
			m_aComponents.SetSize(10);
		}

		CComponentManager::~CComponentManager()
		{

		}

		// Create a game object.
		CGameObject *CComponentManager::CreateGameObject()
		{
			CGameObject *pGameObject = SAM_NEW CGameObject;
			m_aGameObjects.push_back(pGameObject);

			return pGameObject;
		}

		// Register a new component.
		uint16 CComponentManager::RegisterComponent(SComponentRegistry *p_pRegister)
		{
			SComponentRegistry &oRegister = m_aComponents.Alloc();
			oRegister.m_pfCreate = p_pRegister->m_pfCreate;
			oRegister.m_pfUpdate = p_pRegister->m_pfUpdate;

			return m_aComponents.GetNbElements() - 1;
		}

		// Create component specified by index.
		IComponent *CComponentManager::CreateComponent(uint16 p_nType)
		{
			SComponentRegistry &oRegister = m_aComponents[p_nType];
			return oRegister.m_pfCreate();
		}


		struct SComponentUpdateJobData
		{
			IComponent *m_pComponent;
		};

		void CComponentManager::Update(f32 p_fDelta)
		{
			for(uint32 nIndex = 0; nIndex < m_aComponents.GetNbElements(); ++nIndex)
			{
				SComponentRegistry &oRegister = m_aComponents[nIndex];

				/* TODO: 
					le gestionnaire de scene devrait modifier les flags de mise a jour des components par game object.

					creer un job array et le remplir de job.

					SComponentUpdateJobData
					sam::SJob oJob =  {&MeshExportCallback, pMeshJobData};
					g_Env->pJobManager.Submit()
				*/

				// TEMP: update en brutforce.
				oRegister.m_pfUpdate(p_fDelta);
			}			
		}
	}	
}
