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
#include "renderer/SamPCH.h"
#include "renderer/ShaderUtilsPlf.h"
#include "renderer/CRenderWindow.h"

namespace sam
{
    bool CompileShader(void *p_pData, uint32 p_nSize, const char *p_sFuncName, const char *p_sProfile, ID3DBlob **p_ppBlob)
    {
        ID3DBlob *pErrorBlob = NULL;
        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef SAM_DEBUG
        dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		HRESULT hResult = D3DCompile(p_pData, p_nSize, NULL, NULL, NULL, p_sFuncName, p_sProfile, dwShaderFlags, 0, p_ppBlob, &pErrorBlob);
        if(hResult != S_OK)
        {            
            if(pErrorBlob != NULL)
            {
                g_Env->pRenderWindow->LogError(hResult, (char*)pErrorBlob->GetBufferPointer());
                pErrorBlob->Release();
            }
            else
			{
                g_Env->pRenderWindow->LogError(hResult, "Unable to compile shader");
			}

            return false;
        }

        return true;
    }
}
