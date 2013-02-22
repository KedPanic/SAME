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
#include <common/SamPCH.h>
#include <common/base/CLog.h>
#include <common/io/CResourceStorageManager.h>
#include <cJSON.h>
#include <common/SamModuleInit.h>

void *json_malloc(size_t p_nSize)
{
	return sam::CAllocator::Alloc(p_nSize, __FILE__, __LINE__);
}

void json_free(void *p_pPtr)
{
    sam::CAllocator::Free(p_pPtr);
}

namespace sam
{
	SSystem g_System;

    /// @brief Initialize common module.
    ///
	/// @return Global environment variable.
	///
    /// @remarks Have to initialized before all others modules.
    Env *InitCommon()
    {
        SAM_ASSERT(g_Env == NULL, "Common module was already initialized.");

		CoInitializeEx(0, COINIT_MULTITHREADED);

        // initialize cJSON.
        cJSON_Hooks hooks;
        hooks.malloc_fn = json_malloc;
        hooks.free_fn = json_free;
        cJSON_InitHooks(&hooks);

        // create memory tracker.
#ifdef SAM_PROFILING
        new CMemoryTracker(); // singleton.
#endif
        // create global env and share it with common sam engine system.
        g_Env = new Env;
        g_Env->pFramework = NULL;
        g_Env->pRenderWindow = NULL;
        g_Env->pInputManager = NULL;
        g_Env->pLocalizationManager = NULL;

		// Initialize system info.
		g_System.Initialize();

        // create sub system.
        g_Env->pLog = SAM_NEW CLog;
        g_Env->pResourceStorageManager = SAM_NEW CResourceStorageManager;

		return g_Env;
    }

    /// @brief Close common module.
    void ShutdownCommon()
    {
        SAM_ASSERT(g_Env != NULL, "Common module is not initialized");

        // Free sub system.
        SAM_DELETE g_Env->pResourceStorageManager;
        SAM_DELETE g_Env->pLog;

#ifdef SAM_DEBUG
        // Release debug memory tracker.
        CMemoryTracker::Release();
#endif        

        // Release global environment variable.
        delete g_Env;
        g_Env = NULL;

		CoUninitialize();
    }
}
