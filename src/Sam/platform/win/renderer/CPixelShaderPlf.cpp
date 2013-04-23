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
#include "SamRendererPCH.h"
#include "renderer/CPixelShader.h"
#include "renderer/CVertexBuffer.h"
#include "renderer/CRenderWindow.h"
#include "renderer/ShaderUtilsPlf.h"

namespace sam
{       
    // Constructor.
    CPixelShader::CPixelShader(ID p_nID)
        : m_nID(p_nID), m_pPixelShader(NULL), m_pNext(NULL)
    {
    }

    // Destructor.
    CPixelShader::~CPixelShader(void)
    {
    }

    // Create pixel shader.
    bool CPixelShader::CreateShader(IStream *p_pStream, const char *p_sFuncName, const char *p_sProfile)
    {
        ID3DBlob *pBlob = NULL;
        // compile pixel shader.
        if(CompileShader(p_pStream->Data(), p_pStream->Size(), p_sFuncName, p_sProfile, &pBlob))
        {
            // create pixel shader.
            HRESULT hResult = g_Env->pRenderWindow->GetD3DDevice()->CreatePixelShader(
                pBlob->GetBufferPointer(), 
                pBlob->GetBufferSize(),
                NULL,
                &m_pPixelShader);
            if(hResult != S_OK)
            {
                pBlob->Release();
                return false;
            }

            return true;
        }

        return false;
    }
}
