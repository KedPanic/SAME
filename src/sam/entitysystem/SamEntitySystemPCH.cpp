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

#include "entitysystem/CComponentManager.h"
#include "components/CTransform.h"
#include "components/CCamera.h"
#include "components/CMesh.h"

//===================================//
// DLL Create/Destroy implementation //
//===================================//
#include <common/SamModuleInit.h>

namespace sam
{
	namespace scene
	{
		CComponentManager *g_pComponentManager = NULL;

		// Create entity system.
		CComponentManager *CreateEntitySystem(Env *p_pEnv)
		{
			SAM_ASSERT(g_pComponentManager == NULL, "Entity System was already created.");

			ModuleInit(p_pEnv);

			p_pEnv->m_pComponentManager = g_pComponentManager = SAM_NEW CComponentManager;
			
			// register main components.
			CTransform::Register(1000);
			CCamera::Register(1000);
			CMesh::Register(1000);

			return g_pComponentManager;
		}

		// Destroy entity system.
		void DestroyEntitySystem()
		{
			SAM_ASSERT(g_Env->m_pComponentManager != NULL, "Entity System was already freed");

			// TODO: supprimer le module.
		}
	}	
}
