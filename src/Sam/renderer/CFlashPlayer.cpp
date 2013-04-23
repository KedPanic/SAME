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
#include "FlashSerialization.h"
#include "CRenderWindow.h"

#if defined(ENABLE_FLASH)
#import "PROGID:ShockwaveFlash.ShockwaveFlash" named_guids
#include "CFlashPlayer.h"
#include "CFlashEvent.h"
#include "CFlashControlSite.h"

typedef HRESULT (__stdcall *GetClassObject)(REFCLSID rclsid, REFIID riid, LPVOID * ppv); 

//#define TEST_THREAD
#ifdef TEST_THREAD
// Copy thread.
class CCopyBuffer : public sam::IAllocated, public sf::Thread
{
public:
    sf::Image *m_Main;
    struct DirtyRect
    {
        int left;
        int top;
        int right;
        int bottom;
    }m_DirtyRect;

    ShockwaveFlashObjects::IShockwaveFlash* m_pFlashObject; ///< COM-interface to the embedded flash object
    sf::Uint8 *m_pBuffer;

    bool *m_bDirty;

    CCopyBuffer(sf::Image *_Image, bool *_bDirty)
        : m_Main(_Image), m_pFlashObject(0), m_pBuffer(0), m_bDirty(_bDirty)
    {

    }

private:
    void Run()
    {
        // Compute size of the dirty zone.
        int iDirtyWidth  = m_DirtyRect.right - m_DirtyRect.left;
        int iDirtyHeight = m_DirtyRect.bottom - m_DirtyRect.top;

        // Compute dirty rectangle to draw.
        RECT local;
        local.left   = -m_DirtyRect.left;
        local.top    = -m_DirtyRect.top;
        local.right  = local.left + m_DirtyRect.right;
        local.bottom = local.top + m_DirtyRect.bottom; 

        // Retrieves view
        IViewObject* pCurView = 0;
        m_pFlashObject->QueryInterface(IID_IViewObject, (void**)&pCurView);

        // Create buffer.
        HDC hdc = GetDC(0);
        BITMAPINFOHEADER bih = {0};
        bih.biSize = sizeof(BITMAPINFOHEADER);
        bih.biBitCount = 32;
        bih.biCompression = BI_RGB;
        bih.biPlanes = 1;
        bih.biWidth = iDirtyWidth;
        bih.biHeight = -iDirtyHeight;
        HDC mainContext = CreateCompatibleDC(hdc);
        HBITMAP mainBitmap = CreateDIBSection(hdc, (BITMAPINFO*)&bih, DIB_RGB_COLORS, (void**)&m_pBuffer, 0, 0);
        SelectObject(mainContext, mainBitmap);
        ReleaseDC(0, hdc);

        // Draw.            
        int iDirtyBufSize = iDirtyWidth * iDirtyHeight * 4;
        memset(m_pBuffer, 0, iDirtyBufSize);
        HRESULT hr = OleDraw(pCurView, DVASPECT_TRANSPARENT, mainContext, &local);

        sf::Image tmp;
        tmp.LoadFromPixels(iDirtyWidth, iDirtyHeight, m_pBuffer);
        m_Main->Copy(tmp, m_DirtyRect.left, m_DirtyRect.top);

        // Release memory.
        DeleteDC(mainContext);
        DeleteObject(mainBitmap);

        *m_bDirty = false;

        SAM_DELETE this;
    }
};
#endif // TEST_THREAD

namespace sam
{    
    /// @brief Default constructor.
    /// 
    /// @param _iWidth Width of the flash player.
    /// @param _iHeight Height of the flash player.
    CFlashPlayer::CFlashPlayer(int _iWidth, int _iHeight, sf::RenderTarget *_pRenderTarget)
        : m_pFlashEvent(0), m_pFlashControlSite(0), m_pFlashObject(0), m_pWindowlessObj(0), m_pOleObject(0), m_bVisible(true), m_iWidth(_iWidth), m_iHeight(_iHeight), m_pFSCommandListener(0), m_pExternalInterfaceListener(0), m_pRenderTarget(_pRenderTarget)
    {
    }

    /// @brief Destructor.
    CFlashPlayer::~CFlashPlayer()
    {
        if(m_pOleObject)
        {
            m_pOleObject->Close(OLECLOSE_NOSAVE);
            m_pOleObject->Release();
        }

        if(m_pWindowlessObj)
        {
            m_pWindowlessObj->Release();
            m_pWindowlessObj = 0;
        }

        if(m_pFlashObject)
        {
            m_pFlashObject->Release();
            m_pFlashObject = 0;
        }

        if(m_pFlashControlSite)
        {
            m_pFlashControlSite->Release();
            SAM_DELETE m_pFlashControlSite;
            m_pFlashControlSite = 0;            
        }

        if(m_pFlashEvent)
        {
            //m_pFlashEvent->Shutdown();
            m_pFlashEvent->Release();
            SAM_DELETE m_pFlashEvent;
            m_pFlashEvent = 0;
        }
    }

    /// @brief Create controller.
    /// 
    /// @param _FlashLib Flash library.
    void CFlashPlayer::CreateController(HMODULE _FlashLib)
    {
        // Try to load from user-supplied Flash OCX first
        if(_FlashLib)
        {
            IClassFactory* pFactory = 0;

            // Retrieves function to create factory.
            GetClassObject getClassFunc = (GetClassObject)GetProcAddress(_FlashLib, "DllGetClassObject");

            // Retrieves factory.
            HRESULT result = getClassFunc(ShockwaveFlashObjects::CLSID_ShockwaveFlash, IID_IClassFactory, (void**)&pFactory);
            if(SUCCEEDED(result))
            {
                pFactory->CreateInstance(NULL, IID_IOleObject, (void**)&m_pOleObject);
                pFactory->Release();	
            }
        }

        // If we still don't have the object, try loading from registry
        if(!m_pOleObject)
        {
            HRESULT result = CoCreateInstance(ShockwaveFlashObjects::CLSID_ShockwaveFlash, 0, CLSCTX_INPROC_SERVER, IID_IOleObject, (void**)&m_pOleObject);
            if(FAILED(result))
            {
                SamLogError("Unable to create flash object from registry");
                return;
            }
        }

        // Create controller site.
        m_pFlashControlSite = SAM_NEW CFlashControlSite(this);

        IOleClientSite* pClientSite = 0;
        m_pFlashControlSite->QueryInterface(__uuidof(IOleClientSite), (void**)&pClientSite);
        m_pOleObject->SetClientSite(pClientSite);
        pClientSite->Release();

        //adjust size
        IOleInPlaceObject* pInPlaceObject = 0;	
        m_pOleObject->QueryInterface(__uuidof(IOleInPlaceObject), (void**)&pInPlaceObject);	        

        // Initialize dirty rect
        m_DirtyRect.left = m_DirtyRect.top = 0;
        m_DirtyRect.right = m_iWidth;
        m_DirtyRect.bottom = m_iHeight;

        if(pInPlaceObject)
        {            
            RECT rect;
            rect.top = 0;
            rect.left = 0;
            rect.right = m_iWidth;
            rect.bottom = m_iHeight;
            pInPlaceObject->SetObjectRects(&rect, &rect);
            pInPlaceObject->Release();
        }

        // Retrieves flash object.        
        m_pOleObject->QueryInterface(__uuidof(ShockwaveFlashObjects::IShockwaveFlash), (void**)&m_pFlashObject);
        m_pOleObject->Release(); 

        if(!m_pFlashObject)
        {
            SamLogError("Unable to create flash object");
            return;
        }        

        // Set transparent and active external communication.
        m_pFlashObject->WMode = L"transparent";
        m_pFlashObject->DisableLocalSecurity();

        m_pOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, 0, m_pFlashControlSite, 0, 0, 0);
        m_pOleObject->QueryInterface(&m_pWindowlessObj);

        // Create event listener.
        m_pFlashEvent = SAM_NEW CFlashEvent(this);
        m_pFlashEvent->Initialize();

        // Create image buffer.
        m_Image.Create(m_iWidth, m_iHeight);
        m_Sprite.SetImage(m_Image);
    }

    /// @brief Set position on X-Axis.
    /// 
    /// @param _iXPos Position on X-Axis.
    void CFlashPlayer::SetXPos(int _iXPos)
    {
        m_Sprite.SetPosition(_iXPos, m_Sprite.GetPosition().y);
    }

    /// @brief Set position on Y-Axis.
    /// 
    /// @param _iYPos Position on Y-Axis.
    void CFlashPlayer::SetYPos(int _iYPos)
    {        
        m_Sprite.SetPosition(m_Sprite.GetPosition().x, _iYPos);
    }

    /// @brief Load movie clip.
    /// 
    /// @param _sFile File to load.
    void CFlashPlayer::Load(const String &_sFile)
    {        
        m_pFlashObject->Movie = sam::toWString(sam::g_Env->pStreamManager->GetPath(_sFile, "ui")).c_str();    
    }

    /*****************************************/
    /*                 PLAYER                */
    /*****************************************/
    /// @brief Play.
    void CFlashPlayer::Play()
    {
        m_pFlashObject->Play();
    }

    /// @brief Pause.
    void CFlashPlayer::Pause()
    {
        m_pFlashObject->StopPlay();
    }

    /// @brief Stop.
    void CFlashPlayer::Stop()
    {
        m_pFlashObject->Stop();
    }

    /// @brief Rewind.
    void CFlashPlayer::Rewind()
    {
        m_pFlashObject->Rewind();
    }

    /// @brief Goto the specified frame by number.
    /// 
    /// @param _iFrame Number of frame to go.
    void CFlashPlayer::Goto(long _iFrame)
    {
        m_pFlashObject->GotoFrame(_iFrame);
    }

    /// @brief Goto the specified frame by label.
    /// 
    /// @param _sLabel Label of the frame to go.
    void CFlashPlayer::Goto(const String &_sFrame)
    {
        m_pFlashObject->TGotoLabel(L"level0/", sam::toWString(_sFrame).c_str());
    }

    /*****************************************/
    /*               RENDERING               */
    /*****************************************/
    /// @brief Set rendering quality.
    /// 
    /// @param _eQuality Rendering quality.
    void CFlashPlayer::SetQuality(sam::EFlashQuality _eQuality)
    {
        switch(_eQuality)
        {
        case sam::FQ_LOW:
            m_pFlashObject->Quality2 = L"low";
            break;
        case sam::FQ_MEDIUM:
            m_pFlashObject->Quality2 = L"medium";
            break;
        case sam::FQ_HIGH:
            m_pFlashObject->Quality2 = L"high";
            break;
        case sam::FQ_BEST:
            m_pFlashObject->Quality2 = L"best";
            break;
        case sam::FQ_AUTO_LOW:
            m_pFlashObject->Quality2 = L"autolow";
            break;
        case sam::FQ_AUTO_HIGH:
            m_pFlashObject->Quality2 = L"autohigh";
            break;
        }        
    }

    /// @brief Set scale mode.
    /// 
    /// @param _eScale Scale mode.
    void CFlashPlayer::SetScale(sam::EFlashScale _eScale)
    {
       m_pFlashObject->ScaleMode = _eScale;
    }

    /// @brief Set alignment.
    /// 
    /// @param _iAlignment Alignment.
    void CFlashPlayer::SetAlignment(int _iAlignment)
    {
         //m_pFlashObject->AlignMode = _iAlignment;

        // Center by default.
        int iXPos = (m_pRenderTarget->GetWidth() >> 1) - (m_iWidth >> 1);
        int iYPos = (m_pRenderTarget->GetHeight() >> 1) - (m_iHeight >> 1);

        // Left or right.
        if(_iAlignment & sam::FA_LEFT)
            iXPos = 0;
        else if(_iAlignment & sam::FA_RIGHT)
            iXPos = m_pRenderTarget->GetWidth() - m_iWidth;

        // Top or bottom.
        if(_iAlignment & sam::FA_TOP)
            iYPos = 0;
        else if(_iAlignment & sam::FA_BOTTOM)
            iYPos = m_pRenderTarget->GetHeight() - m_iHeight;

        // Set position.
        m_Sprite.SetPosition((float)iXPos, (float)iYPos);
    }

    /// @brief Set background color.
    /// 
    /// @param _Red Red channel.
    /// @param _Green Green channel.
    /// @param _Blue Blue channel.
    void CFlashPlayer::SetBackgroundColor(uint8 _Red, uint8 _Green, uint8 _Blue)
    {
        m_pFlashObject->PutBackgroundColor(_Red << 16 | _Green << 8 | _Blue);
    }

    /// @brief Get background color.
    /// 
    /// @param _Red Red channel.
    /// @param _Green Green channel.
    /// @param _Blue Blue channel.
    void CFlashPlayer::GetBackgroundColor(uint8 &_Red, uint8 &_Green, uint8 &_Blue)
    {
        long colors = m_pFlashObject->GetBackgroundColor();
        _Red = colors >> 16;
        
        colors <<= 8;
        _Green = colors >> 16;

        colors <<= 16;
        _Blue = colors >> 16;
    }

    /// @brief Set if it's transparent.
    ///
    /// @param _bTransparent True to make it transparent.
    void CFlashPlayer::SetTransparent(bool _bTransparent)
    {
        if(_bTransparent)
            m_pFlashObject->WMode = L"transparent";
        else
            m_pFlashObject->WMode = L"opaque";
    }

    /// @brief Set dirty rectangle which have to be drawn again.
    /// 
    /// @param _iLeft Left position.
    /// @param _iTop Top position.
    /// @param _iRight Right position.
    /// @param _iBottom Bottom position.
    void CFlashPlayer::InvalidateRect(int _iLeft, int _iTop, int _iRight, int _iBottom)
    {
        if(!m_bDirty)
        {
            m_DirtyRect.left = _iLeft;
            m_DirtyRect.right = _iRight;
            m_DirtyRect.top = _iTop;
            m_DirtyRect.bottom = _iBottom;
            m_bDirty = true;
        }
        else
        {
            m_DirtyRect.left = min(m_DirtyRect.left, _iLeft);
            m_DirtyRect.right = max(m_DirtyRect.right, _iRight);
            m_DirtyRect.top = min(m_DirtyRect.top, _iTop);
            m_DirtyRect.bottom = max(m_DirtyRect.bottom, _iBottom);
        }
    }

    /// @brief Render the movie clip.
    void CFlashPlayer::Render()
    {
        if(m_bDirty)
        {
#ifdef TEST_THREAD
            CCopyBuffer *thread = SAM_NEW CCopyBuffer(&m_Image, &m_bDirty);
            thread->m_DirtyRect.left = m_DirtyRect.left;
            thread->m_DirtyRect.top = m_DirtyRect.top;
            thread->m_DirtyRect.right = m_DirtyRect.right;
            thread->m_DirtyRect.bottom = m_DirtyRect.bottom;
            thread->m_pFlashObject = m_pFlashObject;
            thread->Launch();
#else
            // Compute size of the dirty zone.
            int iDirtyWidth  = m_DirtyRect.right - m_DirtyRect.left;
            int iDirtyHeight = m_DirtyRect.bottom - m_DirtyRect.top;

            // Compute dirty rectangle to draw.
            RECT local;
            local.left   = -m_DirtyRect.left;
            local.top    = -m_DirtyRect.top;
            local.right  = local.left + m_DirtyRect.right;
            local.bottom = local.top + m_DirtyRect.bottom; 

            // Retrieves view
            IViewObject* pCurView = 0;
            m_pFlashObject->QueryInterface(IID_IViewObject, (void**)&pCurView);

            // Create buffer.
            HDC hdc = GetDC(0);
            BITMAPINFOHEADER bih = {0};
            bih.biSize = sizeof(BITMAPINFOHEADER);
            bih.biBitCount = 32;
            bih.biCompression = BI_RGB;
            bih.biPlanes = 1;
            bih.biWidth = iDirtyWidth;
            bih.biHeight = -iDirtyHeight;
            HDC mainContext = CreateCompatibleDC(hdc);
            HBITMAP mainBitmap = CreateDIBSection(hdc, (BITMAPINFO*)&bih, DIB_RGB_COLORS, (void**)&m_pBuffer, 0, 0);
            SelectObject(mainContext, mainBitmap);
            ReleaseDC(0, hdc);

            // Draw.            
            int iDirtyBufSize = iDirtyWidth * iDirtyHeight * 4;
            memset(m_pBuffer, 0, iDirtyBufSize);
            HRESULT hr = OleDraw(pCurView, DVASPECT_TRANSPARENT, mainContext, &local);

            // Copy buffer.                  
            sf::Image tmp;
            tmp.LoadFromPixels(iDirtyWidth, iDirtyHeight, m_pBuffer);
            m_Image.Copy(tmp, m_DirtyRect.left, m_DirtyRect.top);

            // Release memory.
            DeleteDC(mainContext);
            DeleteObject(mainBitmap);

            m_bDirty = false;
#endif // TEST_THREAD            
        }

        // Draw it.
        m_pRenderTarget->Draw(m_Sprite);
    }

    /*****************************************/
    /*               CALLBACK                */
    /*****************************************/
    /// @brief Set the fscommand listener.
    /// 
    /// @param _pFSCommandListener FSCommand listener.
    void CFlashPlayer::SetFSCommandListener(sam::IFSCommandListener *_pFSCommandListener)
    {
        m_pFSCommandListener = _pFSCommandListener;
    }

    /// @brief Set the ExternalInterface listener.
    /// 
    /// @param _pExternalInterfaceListener ExternalInterface listener.
    void CFlashPlayer::SetExternalInterfaceListener(sam::IExternalInterfaceListener *_pExternalInterfaceListener)
    {

        m_pExternalInterfaceListener = _pExternalInterfaceListener;
    }

    /*****************************************/
    /*            ACTION SCRIPT              */
    /*****************************************/
    /// @brief Set variable.
    /// 
    /// @param _sVariable Variable name.
    /// @param _Value Value of the specified variable.
    void CFlashPlayer::SetVariable(const UString &_sVariable, const sam::SFlashArgument &_Value)
    {
        m_pFlashObject->SetVariable(_sVariable.c_str(), helper::Variable(_Value).c_str());
    }

    /// @brief Retrieves value of the specified variable.
    /// 
    /// @param _sVariable Variable name.
    /// @param _Value Value of the specified variable.
    void CFlashPlayer::GetVariable(const UString &_sVariable, sam::SFlashArgument *_Value)
    {
        helper::Result(_Value, UString((wchar_t*)m_pFlashObject->GetVariable(_sVariable.c_str())));
    }

    /// @brief Invoke action script function.
    /// 
    /// @param _sFunction Function name.
    /// @param _pArgs Array of arguments.
    /// @param _iNbArgs Size of the array.
    /// @param _pResult Function result.
    void CFlashPlayer::Invoke(const UString &_sFunction, const sam::SFlashArgument *_pArgs, uint32 _iNbArgs, sam::SFlashArgument *_pResult /*= 0*/)
    {
        // Serialize.
        std::wstring result;
        helper::Invoke(_sFunction, _pArgs, _iNbArgs, result);

        try
        {
            // Call function.
            result = m_pFlashObject->CallFunction(result.c_str());
        }
        catch (...)
        {
            SamLogWarning("Unable to Invoke function '%s' in flash object '%s'", sam::toString(_sFunction.c_str()).c_str(), sam::toString((wchar_t*)m_pFlashObject->Movie).c_str());
        }        

        // Deserialize the result.
        helper::Result(_pResult, result);
    }

    /*****************************************/
    /*              KEYBOARD/MOUSE           */
    /*****************************************/
    /// @brief Send keyboard event.
    /// 
    /// @param _KeyEvent Keyboard event.
    void CFlashPlayer::SendKeyEvent(const sam::SFlashKeyEvent &_KeyEvent)
    {
        LRESULT result;
        m_pWindowlessObj->OnWindowMessage(_KeyEvent.keystate == sam::FKS_Down?WM_KEYDOWN:WM_KEYUP, _KeyEvent.keycode, 0, &result);
    }

    /// @brief Send mouse event.
    /// 
    /// @param _MouseEvent Mouse event.
    void CFlashPlayer::SendMouseEvent(const sam::SFlashMouseEvent &_MouseEvent)
    {       
        // Setup message.
        UINT message = 0;
        WPARAM wparam = 0;   
        switch(_MouseEvent.mousestate)
        {
        case sam::FMS_Move:
            message = WM_MOUSEMOVE;
            break;
        case sam::FMS_Pressed:
            message = WM_LBUTTONDOWN;
            wparam = MK_LBUTTON;
            break;
        case sam::FMS_Released:
            message = WM_LBUTTONUP;
            wparam = MK_LBUTTON;
            break;
        case sam::FMS_Wheel:
            message = WM_MOUSEWHEEL;
            wparam = MAKEWPARAM(0, _MouseEvent.wheel);
        }

        // Compute relative position.
        int iXPos = _MouseEvent.x - m_Sprite.GetPosition().x;
        int iYPos = _MouseEvent.y - m_Sprite.GetPosition().y;

        // Send window message.
        LRESULT result;
        m_pWindowlessObj->OnWindowMessage(message, wparam, MAKELPARAM(iXPos, iYPos), &result);
        result;
    }

    /// @brief Callback when fscommand is called in action script.
    /// 
    /// @param _sCommand Name of the command.
    /// @param _sArgs Arguments.
    void CFlashPlayer::OnFSCommand(const UString &_sCommand, const UString &_sArgs)
    {
        if(m_pFSCommandListener)
            m_pFSCommandListener->OnFSCommand(_sCommand, _sArgs);
    }

    /// @brief Callback when ExternalInterface.call is called in action script.
    /// 
    /// @param _sFunction Name of the function.
    /// @param _pArgs List of arguments.
    /// @param _iNbArgs Number of arguments.
    void CFlashPlayer::OnExternalInterface(const UString &_sFunction, sam::SFlashArgument *_pArgs, int _iNbArgs)
    {
        if(m_pExternalInterfaceListener)
            m_pExternalInterfaceListener->OnExternalInterface(_sFunction, _pArgs, _iNbArgs);
    }
}

#endif //ENABLE_FLASH
