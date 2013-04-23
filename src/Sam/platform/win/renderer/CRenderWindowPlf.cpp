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
#include "renderer/CRenderWindow.h"
#include "renderer/CVertexBuffer.h"
#include "renderer/CTextureManager.h"
#include "renderer/CMaterialManager.h"
#include "renderer/CPixelShader.h"
#include "renderer/CVertexShader.h"

#include <DxErr.h>

namespace sam
{
    bool CheckSupportedDisplayFormat(DXGI_SWAP_CHAIN_DESC *_pSwapChainDesc, int _nWidth, int _nHeight)
    {
        HRESULT result;

        IDXGIFactory* factory = NULL;
        IDXGIAdapter* adapter = NULL;
        IDXGIOutput* adapterOutput = NULL;
        unsigned int numModes, i, numerator, denominator;
        DXGI_MODE_DESC* displayModeList;
        DXGI_ADAPTER_DESC adapterDesc;

        // Create a DirectX graphics interface factory.
        result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
        if(FAILED(result))
        {
            return false;
        }

        // Use the factory to create an adapter for the primary graphics interface (video card).
        result = factory->EnumAdapters(0, &adapter);
        if(FAILED(result))
        {
            return false;
        }

        // Enumerate the primary adapter output (monitor).
        result = adapter->EnumOutputs(0, &adapterOutput);
        if(FAILED(result))
        {
            return false;
        }

        // Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
        result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
        if(FAILED(result))
        {
            return false;
        }

        // Create a list to hold all the possible display modes for this monitor/video card combination.
        displayModeList = new DXGI_MODE_DESC[numModes];
        if(!displayModeList)
        {
            return false;
        }

        // Now fill the display mode list structures.
        result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
        if(FAILED(result))
        {
            return false;
        }

        // Now go through all the display modes and find the one that matches the screen width and height.
        // When a match is found store the numerator and denominator of the refresh rate for that monitor.
        for(i=0; i < numModes; i++)
        {
             if(displayModeList[i].Width == (unsigned int)_nWidth)
             {
                 if(displayModeList[i].Height == (unsigned int)_nHeight)
                 {
                    numerator = displayModeList[i].RefreshRate.Numerator;
                    denominator = displayModeList[i].RefreshRate.Denominator;
                    break;
                }
            }
        }

        // Get the adapter (video card) description.
        result = adapter->GetDesc(&adapterDesc);
        if(FAILED(result))
        {
            return false;
        }

		if(i == numModes)
		{
			_pSwapChainDesc->BufferDesc.Width = _nWidth;
			_pSwapChainDesc->BufferDesc.Height = _nHeight;
 			_pSwapChainDesc->BufferDesc.RefreshRate.Denominator = 60;
			_pSwapChainDesc->BufferDesc.RefreshRate.Numerator = 1;
 			_pSwapChainDesc->BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
			_pSwapChainDesc->BufferDesc.Scaling =DXGI_MODE_SCALING_UNSPECIFIED;
		}
		else
		{
			memcpy(&_pSwapChainDesc->BufferDesc, &displayModeList[i], sizeof(DXGI_MODE_DESC));
		}

        // Release the display mode list.
        delete [] displayModeList;
        displayModeList = 0;

        // Release the adapter output.
        adapterOutput->Release();
        adapterOutput = 0;

        // Release the adapter.
        adapter->Release();
        adapter = 0;

        // Release the factory.
        factory->Release();
        factory = 0;

        return true;
    }

    CTextureManager *g_pTextureManager = NULL;
    /// @brief Constructor.
    CRenderWindow::CRenderWindow()
        : m_nWidth(0), m_nHeight(0), m_hWindowHandle(NULL), m_fClearDepth(0.0f), m_nClearStencil(0),
          m_pFirstVertexShader(NULL), m_pLastVertexShader(NULL), m_pFirstPixelShader(NULL), m_pLastPixelShader(NULL)
    {
        g_pTextureManager = SAM_NEW CTextureManager;

        memset(&m_fClearColor, 0, sizeof(m_fClearColor));
    }

    /// @brief Destructor.
    CRenderWindow::~CRenderWindow()
    {
        SAM_DELETE g_pTextureManager;
        g_pTextureManager = 0;
    }

    // Initialize DirectX11 context.
    bool CRenderWindow::InitializeDevice(uint32 _iAASample, bool _bFullscreen)
    {        
        SAM_ASSERT(_iAASample > 0, "AA Sample level should be higher than 0");

        // Create the swap chain.
        DXGI_SWAP_CHAIN_DESC swapChainDesc;
        ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
     

        swapChainDesc.BufferCount = 1;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow = m_hWindowHandle;        
        swapChainDesc.Windowed = !_bFullscreen;        
        swapChainDesc.SampleDesc.Count = _iAASample <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT?_iAASample:D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;
        swapChainDesc.SampleDesc.Quality = 0;

        CheckSupportedDisplayFormat(&swapChainDesc, m_nWidth, m_nHeight);

        D3D_FEATURE_LEVEL featureLevelsSupported;
        const D3D_FEATURE_LEVEL featuresLevels[] =
        {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
        };

        UINT createDeviceFlags = 0;
#ifdef _DEBUG
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        // try to load with DX11 feature.
        HRESULT hResult = D3D11CreateDeviceAndSwapChain(
            NULL, 
            D3D_DRIVER_TYPE_HARDWARE, 
            NULL, 
            createDeviceFlags, 
            featuresLevels, 
            3, 
            D3D11_SDK_VERSION, 
            &swapChainDesc, 
            &m_pSwapChain,
            &m_pDevice,
            &featureLevelsSupported,
            &m_pContext);
        if(hResult != S_OK)
        {
            LogError(hResult, "Unable to create 3D device.");
            return false;
        }

        // Initialize default render state.
        m_DefaultRenderState.Initialize(m_pSwapChain, m_pDevice, m_pContext);

        return true;
    }

	// Create window form external handle.
	bool CRenderWindow::Create(SAM_HWND p_hWinHandle, int32 p_nWidth, int32 p_nHeight, uint32 p_nColorBpp, uint32 p_nDepthBits, uint32 p_nStencilBits, uint32 p_nAASample)
	{
		m_hWindowHandle = p_hWinHandle;
		m_nWidth = p_nWidth;
		m_nHeight = p_nHeight;

		// Initialize 3D device.
		if(!InitializeDevice(p_nAASample, false))
		{
			return false;
		}

		// Set viewport.
		SetViewport(0, 0, m_nWidth, m_nHeight);

		return true;
	}

    // Create window.
    SAM_HWND CRenderWindow::Create(const char *_sTitle, int _iWidth, int _iHeight, uint32 _iColorBpp, uint32 _iDepthBits, uint32 _iStencilBits, uint32 _iAASample, bool _bFullscreen)
    {               
        HINSTANCE hInstance = GetModuleHandle(0);

        // Create Win32 Window
        WNDCLASSEX wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = m_pfWndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = NULL;//LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
        wcex.hCursor = NULL;//LoadCursor( NULL, IDC_ARROW);
        wcex.hbrBackground = ( HBRUSH )(COLOR_WINDOW + 1);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = "SamEngine";
        wcex.hIconSm = NULL;//LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
        if(!RegisterClassEx( &wcex ))
        {
            SamLogError("Unable to create window.");
            return NULL;
        }

        // Set style.
        int nX, nY;
        DWORD dwStyle = WS_VISIBLE | WS_OVERLAPPED;
        if(_bFullscreen)
        {
            nX = 0;
            nY = 0;
            dwStyle |= WS_POPUP;
        }
        else
        {
            dwStyle |= /*WS_CLIPCHILDREN | WS_CLIPSIBLINGS | */WS_CAPTION;

            RECT rect = {0, 0, _iWidth, _iHeight};
            AdjustWindowRect(&rect, dwStyle, false);

            nX = (GetSystemMetrics(SM_CXSCREEN) - _iWidth) / 2;
            nY = (GetSystemMetrics(SM_CYSCREEN) - _iHeight) / 2;
        }

        // Create window.
        m_hWindowHandle = CreateWindow("SamEngine", _sTitle, dwStyle, nX, nY, _iWidth, _iHeight, NULL, NULL, hInstance, this);
        if(!m_hWindowHandle)
        {
            SamLogError("Unable to create window.");
            return NULL;
        }
        ShowMouseCursor(false);        

        m_nWidth = _iWidth;
        m_nHeight = _iHeight;

        // Initialize 3D device.
        if(!InitializeDevice(_iAASample, _bFullscreen))
            return NULL;

        // Set viewport.
        SetViewport(0, 0, _iWidth, _iHeight);

        return m_hWindowHandle;
    }

    /// @brief Retrieves window context handler.
    /// 
    /// @return Window context handler.
    SAM_HWND CRenderWindow::GetHWND(void)
    {
        return m_hWindowHandle;
    }

    /// @brief Show/Hidde mouse pointer.
    /// 
    /// @param _bShow True to show mouse pointer.
    void CRenderWindow::ShowMouseCursor(bool _bShow)
    {
        ShowCursor(_bShow);
    }

    // Change resolution.
    void CRenderWindow::SetResolution(int p_nWidth, int p_nHeight)
    {
		m_nWidth = p_nWidth;
        m_nHeight = p_nHeight;

		m_DefaultRenderState.Resize(m_pSwapChain, m_pDevice, m_pContext);
    }

    /// @brief Retrieves width of the window.
    /// 
    /// @return Width of the window.
    int CRenderWindow::GetWidth(void) const
    {
        return m_nWidth;
    }

    /// @brief Retrieves height of the window.
    /// 
    /// @return Width of the window.
    int CRenderWindow::GetHeight(void) const
    {
        return m_nHeight;
    }

    /// @brief Sets viewport.
    /// 
    /// @param _iX Position on X-Axis.
    /// @param _iY Position on Y-Axis.
    /// @param _iWidth Width of the viewport.
    /// @param _iHeight Height of the viewport.
    void CRenderWindow::SetViewport(int _iX, int _iY, int _iWidth, int _iHeight)
    {        
        D3D11_VIEWPORT viewport = {(FLOAT)_iX, (FLOAT)_iY, (FLOAT)_iWidth, (FLOAT)_iHeight, 0.0f, 1.0f};
        
        m_pContext->RSSetViewports(1, &viewport);
    }

    /// @brief Retrieves viewport size and position.
    /// 
    /// @param _iX Position on X-Axis.
    /// @param _iY Position on Y-Axis.
    /// @param _iWidth Width of the viewport.
    /// @param _iHeight Height of the viewport.
    void CRenderWindow::GetViewport(int *_iX, int *_iY, int *_iWidth, int *_iHeight)
    {   
        D3D11_VIEWPORT viewport;
        UINT nNbViewports = 1;
        m_pContext->RSGetViewports(&nNbViewports, &viewport);

        *_iX = (int)viewport.TopLeftX;
        *_iY = (int)viewport.TopLeftY;
        *_iWidth  = (int)viewport.Width;
        *_iHeight = (int)viewport.Height;
    }

    /// @brief Sets scissor for the viewport.
    /// 
    /// @param _X Position on X-Axis.
    /// @param _iY Position on Y-Axis.
    /// @param _iWidth Width of the scissor.
    /// @param _iHeight Height of the scissor.
    void CRenderWindow::SetScissor(int _iX, int _iY, int _iWidth, int _iHeight)
    {
        D3D11_RECT rect = {_iX, _iY, _iWidth, _iHeight};
        m_pContext->RSSetScissorRects(1, &rect);
    }

    /// @brief Sets the color to clear the color buffer.
    /// 
    /// @param _fRed Red channel.
    /// @param _fGreen Green channel.
    /// @param _fBlue Blue channel.
    /// @param _fAlpha Alpha channel.
    void  CRenderWindow::SetClearColor(float _fRed, float _fGreen, float _fBlue, float _fAlpha)
    {
        m_fClearColor[0] = _fRed;
        m_fClearColor[1] = _fGreen;
        m_fClearColor[2] = _fBlue;
        m_fClearColor[3] = _fAlpha;
    }

    /// @brief Sets the value to clear the depth buffer.
    /// 
    /// @param _fClearDepth Value to clear.
    void CRenderWindow::SetClearDepth(float _fClearDepth)
    {
        m_fClearDepth = _fClearDepth;
    }

    /// @brief Sets the value to clear the stencil buffer.
    /// 
    /// @param _nClearStencil Value to clear.
    void CRenderWindow::SetClearStencil(uint8 _nClearStencil)
    {
        m_nClearStencil = _nClearStencil;
    }

    /// @brief Begin rendering scene.
    /// 
    /// @param _nFlags Clear mask flags.
    ///
    /// @return True if rendering begun successfully.
    bool CRenderWindow::BeginScene(uint32 _nFlags)
    {
        // retrieve current view.
//         sf::View &view = m_RenderWindow.GetDefaultView();
// 
//         // compute new position.
//         Vector3 vPos = _Camera.GetPosition();
//         float fHalfX = m_RenderWindow.GetWidth() >> 1;
//         float fHalfY = m_RenderWindow.GetHeight() >> 1;
//         view.SetCenter(vPos.x + fHalfX, vPos.y + fHalfY);
//         view.SetHalfSize(fHalfX, fHalfY);
//         view.Zoom(vPos.z);

        //m_pRenderWindow->Clear();
        ClearScene(_nFlags);

        return true;
    }

    /// @brief Clear buffer.
    /// 
    /// @param _nFlags Clear mash flags.
    /// 
    /// @return True if scene cleared successfully.
    bool CRenderWindow::ClearScene(uint32 _nFlags)
    {
        if(_nFlags & EClearType_Depth || _nFlags & EClearType_Stencil)
        {
            UINT flag = 0;
            if(_nFlags & EClearType_Stencil)
                flag |= D3D11_CLEAR_STENCIL;
            if(_nFlags & EClearType_Depth)
                flag |= D3D11_CLEAR_DEPTH;

            m_pContext->ClearDepthStencilView(m_DefaultRenderState.m_pDepthStencilView, flag, m_fClearDepth, m_nClearStencil);
        }

        if(_nFlags & EClearType_Color)
        {
            m_pContext->ClearRenderTargetView(m_DefaultRenderState.m_pRenderTargetView, m_fClearColor);
        }

        return true;
    }

    /// @brief End rendering scene.
    /// 
    /// @return True if scene ended successfully.
    bool CRenderWindow::EndScene(void)
    {
        m_pSwapChain->Present(0, 0);

        return true;
    }    

    /// @brief Draw line.
    /// 
    /// @param _vPointA First point of the line.
    /// @param _vPointB Second point of the line.
    void CRenderWindow::DrawLine(const Vector3 &_vPointA, const Vector3 &_vPointB, const Color &_Color)
    {
       // sf::Color color(_Color.r * 255, _Color.g * 255, _Color.b * 255, _Color.a * 255);
        //m_RenderWindow.Draw(sf::Shape::Line(_vPointA.x, _vPointA.y, _vPointB.x, _vPointB.y, 1.f, color));
    }

    /// @brief Draw sphere.
    /// 
    /// @param _vCenter Position of the sphere.
    /// @param _fRadius Radius.
    /// @param _Color   Color of the sphere.
    void CRenderWindow::DrawSphere(const Vector3 &_vCenter, float _fRadius, const Color &_Color)
    {
        //sf::Color color(_Color.r * 255, _Color.g * 255, _Color.b * 255, _Color.a * 255);
        //m_RenderWindow.Draw(sf::Shape::Circle(_vCenter.x, _vCenter.y, _fRadius, color));
    }

    /// @brief Draw polygon.
    /// 
    /// @param _pvVertices Array of vertex.
    /// @param _nNbVertex  Number of vertex.
    /// @param _pColor	   Vertex color.	
    void CRenderWindow::DrawVertices(const Vector3 *_pvVertices, uint32 _nNbVertex, const Color *_pColor)
    {
//         sf::Shape polygon;
//         for(int i = 0; i < _nNbVertex; ++i)
//         {
//             sf::Color color(_pColor[i].r * 255, _pColor[i].g * 255, _pColor[i].b * 255, _pColor[i].a * 255);
//             polygon.AddPoint(_pvVertices[i].x, _pvVertices[i].y, color);
//         }

        //m_RenderWindow.Draw(polygon);
    }

    /// @brief Draw current vertex buffer.
    /// 
    /// @param _nNbIndex index number.
    /// @param _nStartVertexLocation.
    void CRenderWindow::Draw(uint32 _nNbIndex, uint32 _nStartVertexLocation /*= 0*/)
    {
        m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        m_pContext->Draw(_nNbIndex, _nStartVertexLocation);
    }

     //================================================//
    //                  RENDER STATE                  //
    //================================================//
    static D3D11_BLEND gs_BlendFactor[] =
    {
        D3D11_BLEND_ZERO,
        D3D11_BLEND_ONE,
        D3D11_BLEND_SRC_COLOR,
        D3D11_BLEND_INV_SRC_COLOR,
        D3D11_BLEND_DEST_COLOR,
        D3D11_BLEND_INV_DEST_COLOR,
        D3D11_BLEND_SRC_COLOR,
        D3D11_BLEND_INV_SRC_COLOR,
        D3D11_BLEND_SRC_ALPHA,
        D3D11_BLEND_INV_SRC_ALPHA,
        D3D11_BLEND_DEST_ALPHA,
        D3D11_BLEND_INV_DEST_ALPHA,
        D3D11_BLEND_SRC_ALPHA,
        D3D11_BLEND_INV_SRC_ALPHA,
        D3D11_BLEND_SRC_ALPHA_SAT,
    };

    static D3D11_BLEND_OP gs_BlendOp[] =
    {
        D3D11_BLEND_OP_ADD,
        D3D11_BLEND_OP_SUBTRACT,
        D3D11_BLEND_OP_REV_SUBTRACT,
        D3D11_BLEND_OP_MIN,
        D3D11_BLEND_OP_MAX,
    };

    /// @brief Sets blending factor state.
    /// 
    /// @param _bEnabled True to enable blending operation.
    /// @param _eSrcColor Source color factor.
    /// @param _eDstColor Destination color factor.
    /// @param _eSrcAlpha Source alpha factor.
    /// @param _eDstAlpha Destination alpha factor.
    void CRenderWindow::SetBlendFactor(bool _bEnabled, EBlendFactor _eSrcColor, EBlendFactor _eDstColor, EBlendFactor _eSrcAlpha, EBlendFactor _eDstAlpha)
    {
        m_DefaultRenderState.m_BlendStateDesc.RenderTarget[0].BlendEnable = _bEnabled;
        m_DefaultRenderState.m_BlendStateDesc.RenderTarget[0].SrcBlend = gs_BlendFactor[_eSrcColor];
        m_DefaultRenderState.m_BlendStateDesc.RenderTarget[0].DestBlend = gs_BlendFactor[_eDstColor];
        m_DefaultRenderState.m_BlendStateDesc.RenderTarget[0].SrcBlendAlpha = gs_BlendFactor[_eSrcAlpha];
        m_DefaultRenderState.m_BlendStateDesc.RenderTarget[0].DestBlendAlpha = gs_BlendFactor[_eDstAlpha];
    }

    /// @brief Sets blending color.
    /// 
    /// @param _fRed Red channel.
    /// @param _fGreen Green channel.
    /// @param _fBlue Blue channel.
    /// @param _fAlpha Alpha channel.
    void CRenderWindow::SetBlendColor(float _fRed, float _fGreen, float _fBlue, float _fAlpha)
    {

    }

    /// @brief Sets blending operation.
    /// 
    /// @param _eColor Color operation.
    /// @param _eAlpha Alpha operation.
    void CRenderWindow::SetBlendOp(EBlendOp _eColor, EBlendOp _eAlpha)
    {
        m_DefaultRenderState.m_BlendStateDesc.RenderTarget[0].BlendOp = gs_BlendOp[_eColor];
        m_DefaultRenderState.m_BlendStateDesc.RenderTarget[0].BlendOpAlpha = gs_BlendOp[_eAlpha];
    }

    //================================================//
    //                  SHADER MANAGEMENT             //
    //================================================//

    /// @brief Create vertex buffer.
    CVertexBuffer *CRenderWindow::CreateVertexBuffer(void)
    {
        return SAM_NEW CVertexBuffer;
    }

    /// @brief Set current vertex buffer.
    /// 
    /// @param _nSlot Input slot.
    /// @param _pVertexBuffer Vertex buffer.
    void CRenderWindow::SetVertexBuffer(uint32 _nSlot, CVertexBuffer *_pVertexBuffer)
    {
        SAM_ASSERT(_pVertexBuffer != NULL, "Vertex buffer is null");

        CVertexBuffer *pVertexBuffer = _pVertexBuffer;
        if(m_DefaultRenderState.m_pVertexBuffer != _pVertexBuffer)
        {
            m_DefaultRenderState.m_pVertexBuffer = _pVertexBuffer;
            m_DefaultRenderState.m_pVertexShader->CreateInputLayout(pVertexBuffer);

            uint32 nOffset = 0;
            uint32 nStride = _pVertexBuffer->GetStride();
            ID3D11Buffer *pBuffer = pVertexBuffer->GetD3DBuffer();

            m_pContext->IASetVertexBuffers(_nSlot, 1, &pBuffer, &nStride, &nOffset);            
        }
    }

    // Create vertex shader.
    CVertexShader *CRenderWindow::CreateVertexShader(IStream *p_pStream, ID p_nID, const char *p_sFuncName, const char *p_sProfile)
    {
        CVertexShader *pVertexShader = NULL;
#ifdef SAM_DEBUG
        if(pVertexShader = GetVertexShader(p_nID))
        {
            SAM_ASSERT(false, "Vertex shader already exist");
            return pVertexShader;
        }
#endif

        pVertexShader = SAM_NEW CVertexShader(p_nID);
        if(!pVertexShader->CreateShader(p_pStream, p_sFuncName, p_sProfile))
        {
            SAM_DELETE pVertexShader;
            return NULL;
        }

        // update chained list.
        if(m_pLastVertexShader)
		{
            m_pLastVertexShader->SetNext(pVertexShader);
		}
        else
		{
			m_pFirstVertexShader = pVertexShader;
		}
		
		m_pLastVertexShader = pVertexShader;
        return pVertexShader;
    }

    // Retrieves vertex shader by ID.
    CVertexShader *CRenderWindow::GetVertexShader(ID p_nID)
    {
        CVertexShader *pVertexShader = m_pFirstVertexShader;
        while(pVertexShader)
        {
            if(pVertexShader->GetID() == p_nID)
			{
                return pVertexShader;
			}

            pVertexShader = pVertexShader->GetNext();
        }

        return NULL;
    }

    // Sets vertex shader.
    void CRenderWindow::SetVertexShader(CVertexShader *p_pShader)
    {
        m_DefaultRenderState.m_pVertexShader = (CVertexShader*)p_pShader;
        m_pContext->VSSetShader(m_DefaultRenderState.m_pVertexShader->GetD3DVertexShader(), NULL, 0);
        m_pContext->IASetInputLayout(m_DefaultRenderState.m_pVertexShader->GetD3DInputLayout());
    }

    // Create pixel shader.
    CPixelShader *CRenderWindow::CreatePixelShader(IStream *p_pStream, ID p_nID, const char *p_sFuncName, const char *p_sProfile)
    {
        CPixelShader *pPixelShader = NULL;
#ifdef SAM_DEBUG
        if(pPixelShader = GetPixelShader(p_nID))
        {
            SAM_ASSERT(false, "Pixel shader already exist");
            return pPixelShader;
        }
#endif

        // retrieves file path.
        pPixelShader = SAM_NEW CPixelShader(p_nID);
        if(!pPixelShader->CreateShader(p_pStream, p_sFuncName, p_sProfile))
        {
            SAM_DELETE pPixelShader;
            return NULL;
        }

        // update chained list.
        if(m_pLastPixelShader)
		{
            m_pLastPixelShader->SetNext(pPixelShader);
		}
        else
		{
            m_pFirstPixelShader = pPixelShader;
		}

        m_pLastPixelShader = pPixelShader;

        return pPixelShader;
    }

    // Retrieves pixel shader by name.
    CPixelShader *CRenderWindow::GetPixelShader(ID p_nID)
    {
        CPixelShader *pPixelShader = m_pFirstPixelShader;
        while(pPixelShader)
        {
            if(pPixelShader->GetID() == p_nID)
			{
                return pPixelShader;
			}

            pPixelShader = pPixelShader->GetNext();
        }

        return NULL;
    }

    // Sets pixel shader.
    void CRenderWindow::SetPixelShader(CPixelShader *p_pShader)
    {
        m_DefaultRenderState.m_pPixelShader = (CPixelShader*)p_pShader;
        m_pContext->PSSetShader(m_DefaultRenderState.m_pPixelShader->GetD3DPixelShader(), NULL, 0);
    }


    //================================================//
    //                  INTERNAL USE                  //
    //================================================//

    // Load DirectX error.
    void CRenderWindow::LogError(HRESULT _hResult, const char *_pMsg /*= ""*/)
    {
        switch(_hResult)
        {
        case D3D11_ERROR_FILE_NOT_FOUND:
            SamLogError("The file was not found. %s\n", _pMsg);
            break;

        case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS:
            SamLogError("There are too many unique instances of a particular type of state object. %s\n", _pMsg);
            break;

        case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS:
            SamLogError("There are too many unique instances of a particular type of view object. %s\n", _pMsg);
            break;

        case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD:
            SamLogError("The first call to ID3D11DeviceContext::Map after either ID3D11Device::CreateDeferredContext or ID3D11DeviceContext::FinishCommandList per Resource was not D3D11_MAP_WRITE_DISCARD. %s\n", _pMsg);
            break;

        case D3DERR_INVALIDCALL:
            SamLogError("%s %s\n", DXGetErrorDescription(_hResult), _pMsg);
            break;

        case D3DERR_WASSTILLDRAWING:
            SamLogError("The previous blit operation that is transferring information to or from this surface is incomplete. %s\n", _pMsg);
            break;

        case E_FAIL:
            SamLogError("Attempted to create a device with the debug layer enabled and the layer is not installed. %s\n", _pMsg);
            break;

        case E_INVALIDARG:
            SamLogError("%s %s\n", DXGetErrorDescription(_hResult), _pMsg);
            break;

        case E_OUTOFMEMORY:
            SamLogError("Direct3D could not allocate sufficient memory to complete the call. %s\n", _pMsg);
            break;

        case S_FALSE:
            SamLogError("Alternate success value, indicating a successful but nonstandard completion (the precise meaning depends on context). %s\n", _pMsg);
            break;
        }
    }
}
