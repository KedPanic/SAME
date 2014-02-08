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
#include "renderer/SRenderStatePlf.h"
#include "renderer/CRenderWindow.h"

namespace sam
{
    /// @brief Default constructor
    SRenderState::SRenderState(void)
        : m_pRenderTargetView(NULL), 
		m_pDepthStencilBuffer(NULL), 
		m_pDepthStencilView(NULL), 
		m_pDepthStencilState(NULL), 
		m_pRasterizerState(NULL),
        m_pBlendState(NULL), 
		m_pVertexBuffer(NULL),
		m_pIndexBuffer(NULL),
		m_pConstantBuffer(NULL),
		m_pVertexShader(NULL), 
		m_pPixelShader(NULL)
    {
    }

    /// @brief Initialize.
    /// 
    /// @return True if initialized successfully.
    bool SRenderState::Initialize(IDXGISwapChain *_pSwapChain, ID3D11Device *_pDevice, ID3D11DeviceContext *_pContext)
    {
        HRESULT hResult = S_OK;

        //==========================================
        // retrieves the pointer to the back buffer.
        ID3D11Texture2D *pBackBuffer = NULL;
        hResult = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
        if(hResult != S_OK)
        {
            g_Env->pRenderWindow->LogError(hResult);
            return false;
        }

        //=========================
        // create the render target.
        hResult = _pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
        pBackBuffer->Release();
        if(hResult != S_OK)
        {
            g_Env->pRenderWindow->LogError(hResult);
            return false;
        }        

        //============================
        // create depth stencil buffer.
        SamLog("Could be created from texture manager!");
        D3D11_TEXTURE2D_DESC depthBufferDesc;
        ZeroMemory(&depthBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
        depthBufferDesc.Width = g_Env->pRenderWindow->GetWidth();
        depthBufferDesc.Height = g_Env->pRenderWindow->GetHeight();
        depthBufferDesc.MipLevels = 1;
        depthBufferDesc.ArraySize = 1;
        depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthBufferDesc.SampleDesc.Count = 1;
        depthBufferDesc.SampleDesc.Quality = 0;
        depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depthBufferDesc.CPUAccessFlags = 0;
        depthBufferDesc.MiscFlags = 0;

        hResult = _pDevice->CreateTexture2D(&depthBufferDesc, NULL, &m_pDepthStencilBuffer);
        if(hResult != S_OK)
        {
            g_Env->pRenderWindow->LogError(hResult);
            return false;
        }

        //============================
        // create depth stencil state.
        D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
        ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
        depthStencilDesc.DepthEnable = true;
        depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        depthStencilDesc.DepthFunc = D3D11_COMPARISON_GREATER;

        depthStencilDesc.StencilEnable = true;
        depthStencilDesc.StencilReadMask = 0xFF;
        depthStencilDesc.StencilWriteMask = 0xFF;

        /* front face */
        depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
        depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

        /* back face */
        depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
        depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

        hResult = _pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilState);
        if(hResult != S_OK)
        {
            g_Env->pRenderWindow->LogError(hResult);
            return false;
        }

        _pContext->OMSetDepthStencilState(m_pDepthStencilState, 1);

        //===========================
        // create depth stencil view.
        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
        ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
        depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        depthStencilViewDesc.Texture2D.MipSlice = 0;

        hResult = _pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView);
        if(hResult != S_OK)
        {
            g_Env->pRenderWindow->LogError(hResult);
            return false;
        }

        _pContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

        //===================
        // create rasterizer.
        D3D11_RASTERIZER_DESC rasterizerDesc;
        ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
        rasterizerDesc.AntialiasedLineEnable = false;
        rasterizerDesc.CullMode = D3D11_CULL_BACK;
        rasterizerDesc.DepthBias = 0;
        rasterizerDesc.DepthBiasClamp = 0.0f;
        rasterizerDesc.DepthClipEnable = true;
        rasterizerDesc.FillMode = D3D11_FILL_SOLID;
        rasterizerDesc.FrontCounterClockwise = false;
        rasterizerDesc.MultisampleEnable = false;
        rasterizerDesc.ScissorEnable = false;
        rasterizerDesc.SlopeScaledDepthBias = 0.0f;

        hResult = _pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerState);
        if(hResult != S_OK)
        {
            g_Env->pRenderWindow->LogError(hResult);
            return false;
        }

        _pContext->RSSetState(m_pRasterizerState);

        //=======================
        // create blending state.        
        ZeroMemory(&m_BlendStateDesc, sizeof(D3D11_BLEND_DESC));
        m_BlendStateDesc.AlphaToCoverageEnable = false;
        m_BlendStateDesc.IndependentBlendEnable = false;
        m_BlendStateDesc.RenderTarget[0].BlendEnable = false;
        m_BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
        m_BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
        m_BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        m_BlendStateDesc.RenderTarget[0].SrcBlendAlpha =  D3D11_BLEND_ONE;
        m_BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
        m_BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        m_BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        hResult = _pDevice->CreateBlendState(&m_BlendStateDesc, &m_pBlendState);
        if(hResult != S_OK)
        {
            g_Env->pRenderWindow->LogError(hResult);
            return false;
        }

        const float fBlendFactor[4] = {0.0f};
        _pContext->OMSetBlendState(m_pBlendState, fBlendFactor, 0xFFFFFFFF);

        return true;
    }

	// Resize the back buffer.
	bool SRenderState::Resize(IDXGISwapChain *p_pSwapChain, ID3D11Device *p_pDevice, ID3D11DeviceContext *p_pContext)
	{
		// Release current render target.
        p_pContext->OMSetRenderTargets(0, NULL, NULL);
        m_pRenderTargetView->Release();
        m_pDepthStencilView->Release();

        return Initialize(p_pSwapChain, p_pDevice, p_pContext);


		// Resize the back buffer
		HRESULT hResult = p_pSwapChain->ResizeBuffers(0, g_Env->pRenderWindow->GetWidth(), g_Env->pRenderWindow->GetHeight(), DXGI_FORMAT_UNKNOWN, 0);
		if(hResult != S_OK)
		{
			g_Env->pRenderWindow->LogError(hResult);
			return false;
		}

		// Retrieve the back buffer
		ID3D11Texture2D *pBackBuffer = NULL;
		hResult = p_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		if(hResult != S_OK)
		{
			g_Env->pRenderWindow->LogError(hResult);
			return false;
		}

		// Create the render target.
        hResult = p_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
		pBackBuffer->Release();
		if(hResult != S_OK)
		{
			g_Env->pRenderWindow->LogError(hResult);
			return false;
		}

        p_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

		return true;
	}
}
