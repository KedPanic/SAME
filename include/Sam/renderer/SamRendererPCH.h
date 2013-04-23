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
#ifndef __SAM_RENDERER_PCH__
#define __SAM_RENDERER_PCH__

/* sam engine */
#include "SamCommon.h"
#include "renderer/EShaderState.h"
#include "renderer/ETexture.h"
#include "renderer/Color.h"

#ifdef SAM_PLATFORM_WIN
#   include <D3D11.h>
#   include <D3DX11.h>
#   include <D3Dcompiler.h>
#else
#   error "unsupported platform"
#endif

// sam engine renderer subsystem macro export
#ifdef SAM_RENDERER_EXPORTS
#   define SAM_RENDERER_API LIBRARY_EXPORT
#else
#   define SAM_RENDERER_API LIBRARY_IMPORT
#endif

//#define ENABLE_FLASH

namespace sam
{
    class CFont;
    class CMaterial;
    class CMaterialManager;
    class CPixelShader;
    class CRenderWindow;
    class CTexture;
	class CTextureManager;
    class CVertexBuffer;
    class CVertexShader;

    typedef uint32 FontID;

    /// @brief Initialize renderer module.
    /// 
    /// @param _pEnv Global environment variable.
    /// 
    /// @return Created render window.
    extern SAM_RENDERER_API CRenderWindow *CreateRenderManager(Env *_pEnv);

    /// @brief Close renderer module.
    extern SAM_RENDERER_API void DestroyRenderManager();
}

#endif // __SAM_RENDERER_PCH__
