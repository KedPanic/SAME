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
#include "CScene.h"
#include "CGameObject.h"

#include "components/CCamera.h"
#include "components/CMesh.h"
#include "components/CTransform.h"

namespace sam
{
	namespace scene
	{
		typedef void (*InitializeFunc)();
		typedef void (*ShutdownFunc)();
		typedef void (*AddGameObjectFunc)(CGameObject *);
		typedef void (*RemoveGameObjectFunc)(CGameObject *);
		typedef void (*UpdateFunc)(CCamera *);

		struct CScene::SceneManager
		{
			InitializeFunc m_pfInit;
			ShutdownFunc m_pfShutdown;
			AddGameObjectFunc m_pfAddGameObject;
			RemoveGameObjectFunc m_pfRemoveGameObject;
			UpdateFunc m_pfUpdate;
		};
		
		// Default constructor.
		CScene::CScene()
			: m_pSceneManagerLibrary(NULL), m_pSceneManager(NULL)
		{
			m_pSceneManager = SAM_ALLOC(SceneManager);
		}

		CScene::~CScene()
		{

		}

		// Initialize the scene with a specific scene manager.
		void CScene::Initialize(const char *p_sSceneManagerName /*= "GenericSceneManager"*/, uint32 p_nMaxGameObject /*= 10000*/)
		{
			SAM_ASSERT(m_pSceneManagerLibrary == NULL, "Scene already initialized");

			// allocate game object buffer.
			m_aGameObjects.Init(p_nMaxGameObject);

			// load shared libraries.
			char sAppPath[MAX_PATH];
			if(GetCurrentWorkingDirectory(MAX_PATH, sAppPath))
			{
				strcat(sAppPath, "/plugins/");
				strcat(sAppPath, p_sSceneManagerName);
				strcat(sAppPath, SHARED_LIBRARY_EXT);

				m_pSceneManagerLibrary =  SamLoadLibrary(sAppPath);
				if(m_pSceneManagerLibrary)
				{
					// retrieves required function.
					m_pSceneManager->m_pfInit = (InitializeFunc)SamGetSymbol(m_pSceneManagerLibrary, "Initialize");
					m_pSceneManager->m_pfShutdown = (ShutdownFunc)SamGetSymbol(m_pSceneManagerLibrary, "Shutdown");
					m_pSceneManager->m_pfAddGameObject = (AddGameObjectFunc)SamGetSymbol(m_pSceneManagerLibrary, "AddGameObject");
					m_pSceneManager->m_pfRemoveGameObject = (RemoveGameObjectFunc)SamGetSymbol(m_pSceneManagerLibrary, "RemoveGameObject");
					m_pSceneManager->m_pfUpdate = (UpdateFunc)SamGetSymbol(m_pSceneManagerLibrary, "Update");
				}
			}			
		}

		// Create an empty game object.
		CGameObject *CScene::CreateGameObject()
		{
			CGameObject *pGameObject = m_aGameObjects.Alloc();
			pGameObject->m_pTransform = pGameObject->AddComponent<CTransform>();

			m_pSceneManager->m_pfAddGameObject(pGameObject);
			return pGameObject;
		}

		// Create a game object with a camera component.
		CGameObject *CScene::CreateCamera()
		{
			CGameObject *pGameObject = m_aGameObjects.Alloc();
			pGameObject->m_pTransform = pGameObject->AddComponent<CTransform>();
			pGameObject->AddComponent<CCamera>();

			m_pSceneManager->m_pfAddGameObject(pGameObject);
			return pGameObject;
		}

		// Create a game object with a mesh component.
		CGameObject *CScene::CreateMesh()
		{
			CGameObject *pGameObject = m_aGameObjects.Alloc();
			pGameObject->m_pTransform = pGameObject->AddComponent<CTransform>();
			pGameObject->AddComponent<CMesh>();

			m_pSceneManager->m_pfAddGameObject(pGameObject);
			return pGameObject;
		}

		// Render the scene from the current camera.
		void CScene::Render(CCamera *p_pCamera)
		{
			m_pSceneManager->m_pfUpdate(p_pCamera);
		}
	}
}
