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
#include <input/SamPCH.h>
#include <input/CInputManagerPlf.h>

//===================================//
// DLL Create/Destroy implementation //
//===================================//
#include <common/SamModuleInit.h>

namespace sam
{
	// Create input manager.
	CInputManager *CreateInputManager(Env *_pEnv, SAM_HWND _pWinHandle)
	{
        SAM_ASSERT(_pEnv->pInputManager == NULL, "Input manager already created!");

		ModuleInit(_pEnv);

		_pEnv->pInputManager = SAM_NEW CInputManager;
		_pEnv->pInputManager->Initialize(_pWinHandle);

		return _pEnv->pInputManager;
	}

	// Destroy input manager.
	void DestroyInputManager()
	{
		SAM_ASSERT(g_Env->pInputManager != NULL, "Input manager already freed");
	    
        g_Env->pInputManager->Shutdown();
		SAM_DELETE g_Env->pInputManager;
		g_Env->pInputManager = NULL;
	}
}
