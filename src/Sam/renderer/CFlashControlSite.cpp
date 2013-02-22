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

#import "PROGID:ShockwaveFlash.ShockwaveFlash" named_guids
#include "CFlashPlayer.h"
#include "CFlashControlSite.h"


namespace sam 
{
    /// @brief Default constructor.
    /// 
    /// @param _pFlashPlayer Flash player which will receive the events.
    CFlashControlSite::CFlashControlSite(CFlashPlayer *_pFlashPlayer)
        : m_pFlashPlayer(_pFlashPlayer), m_iRefCount(0)
    {}

    /// @brief Destructor.
    CFlashControlSite::~CFlashControlSite()
    {

    }

    /************************************/
    /*            IUnknown              */
    /************************************/        
    HRESULT STDMETHODCALLTYPE CFlashControlSite::QueryInterface(REFIID riid, LPVOID* ppv)
    {           
        if(riid == IID_IUnknown || riid == IID_IOleWindow || riid == IID_IOleInPlaceSite || 
            riid == IID_IOleInPlaceSiteEx || riid == IID_IOleInPlaceSiteWindowless || riid == IID_IOleClientSite)
        {
            *ppv = this;
            AddRef();
            return S_OK;
        }           
        else
        {
            *ppv = 0;
            return E_NOTIMPL;
        }
    }

    ULONG STDMETHODCALLTYPE CFlashControlSite::AddRef()
    {  
        return ++m_iRefCount;
    }

    ULONG STDMETHODCALLTYPE CFlashControlSite::Release()
    {  
        --m_iRefCount;
//         if(!m_iRefCount)
//             SAM_DELETE this;

        return m_iRefCount;
    }

    /************************************/
    /*          IOleClientSite          */
    /************************************/
    HRESULT STDMETHODCALLTYPE CFlashControlSite::SaveObject(void)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker** ppmk)
    {
        *ppmk = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::GetContainer(IOleContainer ** theContainerP)
    {			
        return E_NOINTERFACE;
    }

    HRESULT  STDMETHODCALLTYPE CFlashControlSite::ShowObject(void)
    {
        return E_NOTIMPL;
    }

    HRESULT  STDMETHODCALLTYPE CFlashControlSite::OnShowWindow(BOOL)
    {
        return E_NOTIMPL;
    }

    HRESULT  STDMETHODCALLTYPE CFlashControlSite::RequestNewObjectLayout(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::ContextSensitiveHelp(BOOL fEnterMode)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::GetWindow(HWND __RPC_FAR* theWnndow)
    {
        return E_FAIL;
    }

    /************************************/
    /*          IOleInPlaceSite         */
    /************************************/
    HRESULT STDMETHODCALLTYPE CFlashControlSite::CanInPlaceActivate(void)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::OnInPlaceActivate(void)
    {		
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::OnUIActivate(void)
    {		
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::GetWindowContext(IOleInPlaceFrame __RPC_FAR *__RPC_FAR *ppFrame, IOleInPlaceUIWindow __RPC_FAR *__RPC_FAR *ppDoc, 
        LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo)
    {
        RECT rect;
        rect.left = 0;
        rect.top = 0;
        rect.right = m_pFlashPlayer->GetWidth();
        rect.bottom = m_pFlashPlayer->GetHeight();

        *lprcPosRect = rect;
        *lprcClipRect = rect;

        *ppFrame = 0;
        QueryInterface(__uuidof(IOleInPlaceFrame), (void**)ppFrame);		
        *ppDoc = 0;

        lpFrameInfo->fMDIApp = FALSE;
        lpFrameInfo->hwndFrame = 0;
        lpFrameInfo->haccel = 0;
        lpFrameInfo->cAccelEntries = 0;

        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::Scroll(SIZE scrollExtant)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::OnUIDeactivate(BOOL fUndoable)
    {		
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::OnInPlaceDeactivate(void)
    {	
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::DiscardUndoState(void)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::DeactivateAndUndo(void)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::OnPosRectChange(LPCRECT lprcPosRect)
    {
        return S_OK;
    }

    /************************************/
    /*        IOleInPlaceSiteEx         */
    /************************************/
    HRESULT STDMETHODCALLTYPE CFlashControlSite::OnInPlaceActivateEx(BOOL __RPC_FAR *pfNoRedraw, DWORD dwFlags)
    {		
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::OnInPlaceDeactivateEx(BOOL fNoRedraw)
    {		
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::RequestUIActivate(void)
    {
        return S_FALSE;
    }

    /************************************/
    /*     IOleInPlaceSiteWindowless    */
    /************************************/
    HRESULT STDMETHODCALLTYPE CFlashControlSite::CanWindowlessActivate(void)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::GetCapture(void)
    {
        return S_FALSE;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::SetCapture(BOOL fCapture)
    {
        return S_FALSE;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::GetFocus(void)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::SetFocus(BOOL fFocus)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::GetDC(LPCRECT pRect, DWORD grfFlags, HDC __RPC_FAR *phDC)
    {		
        return E_INVALIDARG;		
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::ReleaseDC(HDC hDC)
    {
        return E_INVALIDARG;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::InvalidateRect(LPCRECT pRect, BOOL fErase)
    {	
        if(pRect)
            m_pFlashPlayer->InvalidateRect(pRect->left, pRect->top, pRect->right, pRect->bottom);

        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::InvalidateRgn(HRGN hRGN, BOOL fErase)
    {	
        RECT rect;
        GetRgnBox(hRGN,&rect);
        m_pFlashPlayer->InvalidateRect(rect.left, rect.top, rect.right, rect.bottom);

        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::ScrollRect(INT dx, INT dy, LPCRECT pRectScroll, LPCRECT pRectClip)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::AdjustRect(LPRECT prc)
    {
        if(!prc)
            return E_INVALIDARG;

        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashControlSite::OnDefWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT __RPC_FAR *plResult)
    {
        return S_FALSE;
    }
}
