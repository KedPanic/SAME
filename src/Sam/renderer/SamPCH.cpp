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
#include <renderer/SamPCH.h>
#include <renderer/CTexture.h>
#include <renderer/CMaterialManager.h>
#include <renderer/CRenderWindow.h>
#include <renderer/CTextureManager.h>

//===================================//
// DLL Create/Destroy implementation //
//===================================//
#include <common/SamModuleInit.h>

namespace sam
{
    CRenderWindow *CreateRenderManager(Env *_pEnv)
    {
        SAM_ASSERT(_pEnv->pRenderWindow == NULL, "Renderer was already created");
        ModuleInit(_pEnv);

        _pEnv->pRenderWindow = SAM_NEW CRenderWindow;
        _pEnv->pMaterialManager = SAM_NEW CMaterialManager;           
        _pEnv->pTextureManager = SAM_NEW CTextureManager;

        return _pEnv->pRenderWindow;
    }

    // Destroy render window.
    void DestroyRenderManager(void)
    {
        SAM_ASSERT(g_Env->pRenderWindow != NULL, "Renderer was already freed");
        
        SAM_DELETE g_Env->pTextureManager;
        g_Env->pTextureManager = NULL;

        SAM_DELETE g_Env->pMaterialManager;
        g_Env->pMaterialManager = NULL;

        SAM_DELETE g_Env->pRenderWindow;
        g_Env->pRenderWindow = NULL;
    }
}
