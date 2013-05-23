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
#ifndef __CRENDER_WINDOW_PLF__
#define __CRENDER_WINDOW_PLF__

#ifndef __CRENDER_WINDOW__
#   error "Do not include it directly"
#endif

#include <renderer/SRenderStatePlf.h>

namespace sam
{
    /// @brief Implementation of CRenderWindow with the DirectX11 library.
    class SAM_RENDERER_API CRenderWindow : public IAllocated
    {
    public:
        /// @brief Constructor.
        CRenderWindow();

        /// @brief Destructor.
        ~CRenderWindow();

		/// @brief Create window form external handle.
		/// 
		/// @param p_hWinHandle Window handle.
		/// @param p_nWidth Width of the window.
		/// @param p_nHeight Height of the window.
		/// @param p_nColorBpp Color depth.
		/// @param p_nDepthBits Size of depth buffer in bits.
		/// @param p_nStencilBits Size of stencil buffer in bits.
		/// @param p_nAASample Level of anti-aliasing.
		/// 
		/// @return True if no error occurred.
		bool Create(SAM_HWND p_hWinHandle, int32 p_nWidth, int32 p_nHeight, uint32 p_nColorBpp, uint32 p_nDepthBits, uint32 p_nStencilBits, uint32 p_nAASample);

        /// @brief Create window.
        /// 
        /// @param _sTitle Title of the window.
        /// @param _iWidth Width of the window.
        /// @param _iHeight Height of the window.
        /// @param _iColorBpp Color depth.
        /// @param _iDepthBits Size of depth buffer in bits.
        /// @param _iStencilBits Size of stencil buffer in bits.
        /// @param _iAASample Level of anti-aliasing.
        /// @param _bFullscreen True to make window in fullscreen mode.
        /// 
        /// @return Window context handler.
        SAM_HWND Create(const char *_sTitle, int _iWidth, int _iHeight, uint32 _iColorBpp, uint32 _iDepthBits, uint32 _iStencilBits, uint32 _iAASample, bool _bFullscreen);

        /// @brief Retrieves window context handler.
        /// 
        /// @return Window context handler.
        SAM_HWND GetHWND(void);

        /// @brief Show/Hidde mouse pointer.
        /// 
        /// @param _bShow True to show mouse pointer.
        void ShowMouseCursor(bool _bShow);

        /// @brief Change resolution.
        /// 
        /// @param p_nWidth Width of the window.
        /// @param p_nHeight Height of the window.
        void SetResolution(int p_nWidth, int p_nHeight);

        /// @brief Retrieves width of the window.
        /// 
        /// @return Width of the window.
        int GetWidth(void) const;

        /// @brief Retrieves height of the window.
        /// 
        /// @return Width of the window.
        int GetHeight(void) const;

        /// @brief Sets viewport.
        /// 
        /// @param _iX Position on X-Axis.
        /// @param _iY Position on Y-Axis.
        /// @param _iWidth Width of the viewport.
        /// @param _iHeight Height of the viewport.
        void SetViewport(int _iX, int _iY, int _iWidth, int _iHeight);

        /// @brief Retrieves viewport size and position.
        /// 
        /// @param _iX Position on X-Axis.
        /// @param _iY Position on Y-Axis.
        /// @param _iWidth Width of the viewport.
        /// @param _iHeight Height of the viewport.
        void GetViewport(int *_iX, int *_iY, int *_iWidth, int *_iHeight);

        /// @brief Sets scissor for the viewport.
        /// 
        /// @param _X Position on X-Axis.
        /// @param _iY Position on Y-Axis.
        /// @param _iWidth Width of the scissor.
        /// @param _iHeight Height of the scissor.
        void SetScissor(int _iX, int _iY, int _iWidth, int _iHeight);

        /// @brief Sets the color to clear the color buffer.
        /// 
        /// @param _fRed Red channel.
        /// @param _fGreen Green channel.
        /// @param _fBlue Blue channel.
        /// @param _fAlpha Alpha channel.
        void SetClearColor(float _fRed, float _fGreen, float _fBlue, float _fAlpha);

        /// @brief Sets the value to clear the depth buffer.
        /// 
        /// @param _fClearDepth Value to clear.
        void SetClearDepth(float _fClearDepth);

        /// @brief Sets the value to clear the stencil buffer.
        /// 
        /// @param _nClearStencil Value to clear.
        void SetClearStencil(uint8 _nClearStencil);

        /// @brief Begin rendering scene.
        /// 
        /// @param _nFlags Clear mask flags.
        ///
        /// @return True if rendering begun successfully.
        bool BeginScene(uint32 _nFlags);

        /// @brief Clear buffer.
        /// 
        /// @param _nFlags Clear mash flags.
        /// 
        /// @return True if scene cleared successfully.
        bool ClearScene(uint32 _nFlags);

        /// @brief End rendering scene.
        /// 
        /// @return True if scene ended successfully.
        bool EndScene(void);

        /// @brief Draw line.
        /// 
        /// @param _vPointA First point of the line.
        /// @param _vPointB Second point of the line.
        /// @param _Color   Color of the line.
        void DrawLine(const Vector3 &_vPointA, const Vector3 &_vPointB, const Color &_Color);

        /// @brief Draw sphere.
        /// 
        /// @param _vCenter Position of the sphere.
        /// @param _fRadius Radius.
        /// @param _Color   Color of the sphere.
        void DrawSphere(const Vector3 &_vCenter, float _fRadius, const Color &_Color);

        /// @brief Draw polygon.
        /// 
        /// @param _pvVertices Array of vertex.
        /// @param _nNbVertex  Number of vertex.
        /// @param _pColor	   Vertex color.	
        void DrawVertices(const Vector3 *_pvVertices, uint32 _nNbVertex, const Color *_pColor);

        /// @brief Draw current vertex buffer.
        /// 
        /// @param _nNbIndex index number.
        /// @param _nStartVertexLocation.
        void Draw(uint32 _nNbIndex, uint32 _nStartVertexLocation = 0);

        //================================================//
        //                  RENDER STATE                  //
        //================================================//

        /// @brief Sets blending factor state.
        /// 
        /// @param _bEnabled True to enable blending operation.
        /// @param _eSrcColor Source color factor.
        /// @param _eDstColor Destination color factor.
        /// @param _eSrcAlpha Source alpha factor.
        /// @param _eDstAlpha Destination alpha factor.
        void SetBlendFactor(bool _bEnabled, EBlendFactor _eSrcColor, EBlendFactor _eDstColor, EBlendFactor _eSrcAlpha, EBlendFactor _eDstAlpha);

        /// @brief Sets blending color.
        /// 
        /// @param _fRed Red channel.
        /// @param _fGreen Green channel.
        /// @param _fBlue Blue channel.
        /// @param _fAlpha Alpha channel.
        void SetBlendColor(float _fRed, float _fGreen, float _fBlue, float _fAlpha);

        /// @brief Sets blending operation.
        /// 
        /// @param _eColor Color operation.
        /// @param _eAlpha Alpha operation.
        void SetBlendOp(EBlendOp _eColor, EBlendOp _eAlpha);


        //================================================//
        //                  SHADER MANAGEMENT             //
        //================================================//

		/// @brief Set constant buffer.
		void SetConstantBuffer()

        /// @brief Create vertex buffer.
        CVertexBuffer *CreateVertexBuffer(void);

        /// @brief Set current vertex buffer.
        /// 
        /// @param _nSlot Input slot.
        /// @param _pVertexBuffer Vertex buffer.
        void SetVertexBuffer(uint32 _nSlot, CVertexBuffer *_pVertexBuffer);   

        /// @brief Create vertex shader.
        /// 
        /// @param p_pStream Program file.
		/// @param p_nID Unique ID.
        /// @param p_sFuncName Function name.
        /// @param p_sProfile Profile name.
        /// 
        /// @return Pointer to the vertex shader or null.
        CVertexShader *CreateVertexShader(IStream *p_pStream, ID p_nID, const char *p_sFuncName, const char *p_sProfile);

        /// @brief Retrieves vertex shader by ID.
        /// 
        /// @param p_nID ID of the program file.
        /// 
        /// @return Pointer to the vertex shader or null.
        CVertexShader *GetVertexShader(ID p_nID);

        /// @brief Sets vertex shader.
        /// 
        /// @param p_pShader vertex Shader.
        void SetVertexShader(CVertexShader *p_pShader);

        /// @brief Create pixel shader.
        /// 
		/// @param p_pStream Program file.
		/// @param p_nID Unique ID.
        /// @param p_sFuncName Function name.
        /// @param p_sProfile Profile name.
        /// 
        /// @return Pointer to the pixel shader or null.
        CPixelShader *CreatePixelShader(IStream *p_pStream, ID p_nID, const char *p_sFuncName, const char *p_sProfile);

        /// @brief Retrieves pixel shader by ID.
        /// 
        /// @param p_nID ID of the program file.
        /// 
        /// @return Pointer to the pixel shader or null.
        CPixelShader *GetPixelShader(ID p_nID);

        /// @brief Sets pixel shader.
        /// 
        /// @param p_pShader Shader.
        void SetPixelShader(CPixelShader *p_pShader);

		/// @brief Delete all created shaders.
		void DeleteAllShaders();


        //================================================//
        //                  INTERNAL USE                  //
        //================================================//

        /// @brief Set window proc
        /// 
        /// @param p_pfWndProc Pointer to the function used to receive window events.
        void SetWndProc(WNDPROC p_pfWndProc) {m_pfWndProc = p_pfWndProc;}

        /// @brief Retrieves directx device.
        /// 
        /// @return DirectX device.
        ID3D11Device *GetD3DDevice(void) const {return m_pDevice;}

        /// @brief Retrieves directx context.
        /// 
        /// @return DirectX context.
        ID3D11DeviceContext *GetD3DContext(void) const {return m_pContext;}

        /// @brief Load DirectX error.
        /// 
        /// @param _hResult Id of the error.
        /// @param _pMsg Message to log.
        void LogError(HRESULT _hResult, const char *_pMsg = "");

    private:
        WNDPROC m_pfWndProc;

        uint32 m_nWidth;    ///< Size of the window
        uint32 m_nHeight;   ///< Size of the window

        HWND m_hWindowHandle;   ///< Handle of the window

        // DirectX11
        IDXGISwapChain      *m_pSwapChain; ///< Swap chain interface.
        ID3D11Device        *m_pDevice;    ///< Direct3D device interface.
        ID3D11DeviceContext *m_pContext;   ///< Direct3D device context.

        float m_fClearColor[4];     ///< Clear color.
        float m_fClearDepth;        ///< Clear depth value.
        uint8 m_nClearStencil;      ///< Clear stencil value.

        SRenderStateDX11 m_DefaultRenderState;

        CVertexShader *m_pFirstVertexShader;
        CVertexShader *m_pLastVertexShader;
        CPixelShader *m_pFirstPixelShader;
        CPixelShader *m_pLastPixelShader;

        /// @brief Initialize DirectX11 context.
        /// 
        /// @param _iAASample Level of anti-aliasing.
        /// @param _bFullscreen True to make window in fullscreen mode.
        /// 
        /// @return false if any error occurred.
        bool InitializeDevice(uint32 _iAASample, bool _bFullscreen);
    };
}

#endif // __CRENDER_WINDOW_PLF__
