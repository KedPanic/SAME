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
#ifndef __SAM_ENGINE_CONFIG__
#define __SAM_ENGINE_CONFIG__

#include "common/SamPlatform.h"
#include "common/system/System.h"

// enumeration
#include "common/SamTypes.h"
#include "common/io/EStream.h"

// declaration
namespace sam
{
    struct cmp_str
    {
        bool operator()(const char *_pStrA, const char *_pStrB) const
        {
            return strcmp(_pStrA, _pStrB) < 0;
        }
    };
	
	class CInputManager;	
	class CJobArray;
	class CJobManager;
	class CLog;
    class CLocalizationManager;    
    class CMaterialManager;
	class CRenderWindow;
	class CResourceStorageManager;
	class CSignalManager;
    class CTextureManager;		

	class IResourceStorage;
    class IFramework;
    class IGame;
    class ISerializer;
    class ISerializable;

	namespace scene
	{
		class CComponentManager;
	}
    
    /// @brief Global environment variables.
    /// @remarks Will be created by CommonInit()
    struct Env
    {        
        CLocalizationManager *pLocalizationManager;
        CLog *pLog;
        CInputManager *pInputManager;
		CRenderWindow *pRenderWindow;
        CResourceStorageManager *pResourceStorageManager;
        IFramework *pFramework;
        CMaterialManager *pMaterialManager;
        CTextureManager *pTextureManager;
		scene::CComponentManager *m_pComponentManager;
		CJobManager *pJobManager;
		CSignalManager *pSignalManager;
/*
        ISoundManager *pSoundManager;
        IPhysicalWorld *pPhysicalWorld;
        IGame *pGame;
        IWorld *pWorld;
        IEntitySystem *pEntitySystem;
        IProfileManager *pProfileManager;
*/
    };    


    extern Env *g_Env;
    extern void ModuleInit(Env *_pEnv);    
}

#include <common/base/IAllocated.h>

#endif // __SAM_ENGINE_CONFIG__
