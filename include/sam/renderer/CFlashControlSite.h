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
#ifndef __SR_CFLASH_CONTROL_SITE__
#define __SR_CFLASH_CONTROL_SITE__

namespace sam 
{
    class CFlashPlayer;

    /// @brief To perform drawing operation.
    /// 
    /// @remarks 
    ///     The windowless object calls the methods in this interface to process window messages, 
    ///     to participate in drag and drop operations, and to perform drawing operations.
    class CFlashControlSite : public sam::IAllocated, public IOleInPlaceSiteWindowless, public IOleClientSite
    {   
    public:
        /// @brief Default constructor.
        /// 
        /// @param _pFlashPlayer Flash player which will receive the events.
        CFlashControlSite(CFlashPlayer *_pFlashPlayer);

        /// @brief Destructor.
        ~CFlashControlSite();

        /************************************/
        /*            IUnknown              */
        /************************************/        
        HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppv);

        ULONG STDMETHODCALLTYPE AddRef();

        ULONG STDMETHODCALLTYPE Release();

        /************************************/
        /*          IOleClientSite          */
        /************************************/
        HRESULT STDMETHODCALLTYPE SaveObject(void);

        HRESULT STDMETHODCALLTYPE GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker** ppmk);

        HRESULT STDMETHODCALLTYPE GetContainer(IOleContainer ** theContainerP);

        HRESULT  STDMETHODCALLTYPE ShowObject(void);

        HRESULT  STDMETHODCALLTYPE OnShowWindow(BOOL);

        HRESULT  STDMETHODCALLTYPE RequestNewObjectLayout(void);

        HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL fEnterMode);

        HRESULT STDMETHODCALLTYPE GetWindow(HWND __RPC_FAR* theWnndow);

        /************************************/
        /*          IOleInPlaceSite         */
        /************************************/
        HRESULT STDMETHODCALLTYPE CanInPlaceActivate(void);

        HRESULT STDMETHODCALLTYPE OnInPlaceActivate(void);

        HRESULT STDMETHODCALLTYPE OnUIActivate(void);

        HRESULT STDMETHODCALLTYPE GetWindowContext(IOleInPlaceFrame __RPC_FAR *__RPC_FAR *ppFrame, IOleInPlaceUIWindow __RPC_FAR *__RPC_FAR *ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo);

        HRESULT STDMETHODCALLTYPE Scroll(SIZE scrollExtant);

        HRESULT STDMETHODCALLTYPE OnUIDeactivate(BOOL fUndoable);

        HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate(void);

        HRESULT STDMETHODCALLTYPE DiscardUndoState(void);

        HRESULT STDMETHODCALLTYPE DeactivateAndUndo(void);

        HRESULT STDMETHODCALLTYPE OnPosRectChange(LPCRECT lprcPosRect);
        
        /************************************/
        /*        IOleInPlaceSiteEx         */
        /************************************/
        HRESULT STDMETHODCALLTYPE OnInPlaceActivateEx(BOOL __RPC_FAR *pfNoRedraw, DWORD dwFlags);

        HRESULT STDMETHODCALLTYPE OnInPlaceDeactivateEx(BOOL fNoRedraw);

        HRESULT STDMETHODCALLTYPE RequestUIActivate(void);

        /************************************/
        /*     IOleInPlaceSiteWindowless    */
        /************************************/
        HRESULT STDMETHODCALLTYPE CanWindowlessActivate(void);

        HRESULT STDMETHODCALLTYPE GetCapture(void);

        HRESULT STDMETHODCALLTYPE SetCapture(BOOL fCapture);

        HRESULT STDMETHODCALLTYPE GetFocus(void);

        HRESULT STDMETHODCALLTYPE SetFocus(BOOL fFocus);

        HRESULT STDMETHODCALLTYPE GetDC(LPCRECT pRect, DWORD grfFlags, HDC __RPC_FAR *phDC);

        HRESULT STDMETHODCALLTYPE ReleaseDC(HDC hDC);

        HRESULT STDMETHODCALLTYPE InvalidateRect(LPCRECT pRect, BOOL fErase);

        HRESULT STDMETHODCALLTYPE InvalidateRgn(HRGN hRGN, BOOL fErase);      

        HRESULT STDMETHODCALLTYPE ScrollRect(INT dx, INT dy, LPCRECT pRectScroll, LPCRECT pRectClip);

        HRESULT STDMETHODCALLTYPE AdjustRect(LPRECT prc);

        HRESULT STDMETHODCALLTYPE OnDefWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT __RPC_FAR *plResult);

    private:
         CFlashPlayer *m_pFlashPlayer; ///< Flash player which will receive the events.
         int m_iRefCount;
    };
}

#endif // __SR_CFLASH_CONTROL_SITE__
