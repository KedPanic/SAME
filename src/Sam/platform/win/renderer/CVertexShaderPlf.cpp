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
#include "renderer/CVertexShader.h"
#include "renderer/CVertexBuffer.h"
#include "renderer/CRenderWindow.h"
#include "renderer/ShaderUtilsPlf.h"

namespace sam
{
    static char *gs_SemanticName[] =
    {
        "POSITION",         // VS_Position,
        "BLEND_WEIGHTS",    // VS_Blend_Weights,
        "BLEND_INDICES",    // VS_Blend_Indices,
        "NORMAL",           // VS_Normal,
        "DIFFUSE",          // VS_Diffuse,
        "SPECULAR",         // VS_Specular,
        "BINORMAL",         // VS_Binormal,
        "TANGENT",          // VS_Tangent,
        "TEXCOORD0"         // VS_Texture_Coord0,
    };

    static DXGI_FORMAT gs_eFormat[8][4] =
    {
        // Int
        {DXGI_FORMAT_R32_SINT, DXGI_FORMAT_R32G32_SINT, DXGI_FORMAT_R32G32B32_SINT, DXGI_FORMAT_R32G32B32A32_SINT},

        // Short        
        {DXGI_FORMAT_R16_SINT, DXGI_FORMAT_R16G16_SINT, DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_R16G16B16A16_SINT},

        // Char
        {DXGI_FORMAT_R8_SINT, DXGI_FORMAT_R8G8_SINT, DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_R8G8B8A8_SINT},

        // UInt
        {DXGI_FORMAT_R32_UINT, DXGI_FORMAT_R32G32_UINT, DXGI_FORMAT_R32G32B32_UINT, DXGI_FORMAT_R32G32B32A32_UINT},

        // UShort
        {DXGI_FORMAT_R16_UINT, DXGI_FORMAT_R16G16_UINT, DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_R16G16B16A16_UINT},

        // UChar
        {DXGI_FORMAT_R8_UINT, DXGI_FORMAT_R8G8_UINT, DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_R8G8B8A8_UINT},

        // Float
        {DXGI_FORMAT_R32_FLOAT, DXGI_FORMAT_R32G32_FLOAT, DXGI_FORMAT_R32G32B32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT},

        // Half
        {DXGI_FORMAT_R16_FLOAT, DXGI_FORMAT_R16G16_FLOAT, DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_R16G16B16A16_FLOAT},
    };

    // Constructor.
    CVertexShader::CVertexShader(ID p_nID)
        : m_nID(p_nID), m_pVertexShader(NULL), m_pInputLayout(NULL), m_pBlob(NULL), m_pNext(NULL)
    {

    }

    // Destructor.
    CVertexShader::~CVertexShader(void)
    {
    }

    // Create vertex shader.
    bool CVertexShader::CreateShader(IStream *p_pStream, const char *_sFuncName, const char *_sProfile)
    {
        // compile vertex shader.
        if(CompileShader(p_pStream->Data(), p_pStream->Size(), _sFuncName, _sProfile, &m_pBlob))
        {
            // create vertex shader.
            HRESULT hResult = g_Env->pRenderWindow->GetD3DDevice()->CreateVertexShader(
                m_pBlob->GetBufferPointer(), 
                m_pBlob->GetBufferSize(),
                NULL,
                &m_pVertexShader);
            if(hResult != S_OK)
            {
                m_pBlob->Release();
                return false;
            }

            return true;
        }

        return false;
    }

    bool CVertexShader::CreateInputLayout(CVertexBuffer *p_pVertexBuffer)
    {
        if(m_pInputLayout)
        {
            m_pInputLayout->Release();
            m_pInputLayout = NULL;
        }

        D3D11_INPUT_ELEMENT_DESC *layout = SAM_ALLOC_ARRAY(D3D11_INPUT_ELEMENT_DESC, p_pVertexBuffer->GetNbElements());
        uint32 nOffset = 0;
        for(uint32 i = 0; i < p_pVertexBuffer->GetNbElements(); ++i)
        {
            layout[i].SemanticName = gs_SemanticName[p_pVertexBuffer->GetSemantic(i)];
            layout[i].SemanticIndex = 0;
            layout[i].Format = gs_eFormat[p_pVertexBuffer->GetTypeID(i)][p_pVertexBuffer->GetNbComponent(i) - 1];
            layout[i].InputSlot = 0;
            layout[i].AlignedByteOffset = nOffset;
            layout[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            layout[i].InstanceDataStepRate = 0;

            nOffset += p_pVertexBuffer->GetOffset(i);
        }

        HRESULT hResult = g_Env->pRenderWindow->GetD3DDevice()->CreateInputLayout(layout, p_pVertexBuffer->GetNbElements(), m_pBlob->GetBufferPointer(), m_pBlob->GetBufferSize(), &m_pInputLayout);
        SAM_FREE_ARRAY(layout);
        if(hResult != S_OK)
        {
            return false;
        }

        return true;
    }
}
