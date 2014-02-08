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
#ifndef __SRENDER_STATE_DX11__
#define __SRENDER_STATE_DX11__

namespace sam
{
    class CVertexBuffer;
    class CVertexShader;
    class CPixelShader;

    /// @brief Render state.
    struct SRenderState : public IAllocated
    {
        ID3D11RenderTargetView  *m_pRenderTargetView;    ///< Render target.
        ID3D11Texture2D         *m_pDepthStencilBuffer;  ///< Depth stencil buffer.
        ID3D11DepthStencilView  *m_pDepthStencilView;    ///< Depth stencil.
        ID3D11DepthStencilState *m_pDepthStencilState;   ///< Depth stencil state.
        ID3D11RasterizerState   *m_pRasterizerState;     ///< Rasterizer state.
        D3D11_BLEND_DESC         m_BlendStateDesc;       ///< Blend state description.
        ID3D11BlendState        *m_pBlendState;          ///< Blend state.

        CVertexBuffer           *m_pVertexBuffer;
		CIndexBuffer            *m_pIndexBuffer;
		CConstantBuffer         *m_pConstantBuffer;
        CVertexShader           *m_pVertexShader;
        CPixelShader            *m_pPixelShader;

        /// @brief Default constructor
        SRenderState(void);

        /// @brief Initialize.
        /// 
        /// @return True if it initialized successfully.
        bool Initialize(IDXGISwapChain *_pSwapChain, ID3D11Device *_pDevice, ID3D11DeviceContext *_pContext);

		/// @brief Resize the back buffer.
		/// 
		/// @param p_pSwapChain
		/// @param p_pDevice
		/// @param p_pContext
		/// @param p_nWidth
		/// @param p_nheight
		/// 
		/// @return True if no error occurred.
		bool Resize(IDXGISwapChain *p_pSwapChain, ID3D11Device *p_pDevice, ID3D11DeviceContext *p_pContext);
    };
}

#endif // __CRENDER_STATE_DX11__
