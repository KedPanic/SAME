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
#ifndef __SR_CFLASH_EVENT__
#define __SR_CFLASH_EVENT__

namespace sam
{
    class CFlashPlayer;

    /// @brief Flash event listener.
    class CFlashEvent : public sam::IAllocated, public ShockwaveFlashObjects::_IShockwaveFlashEvents
    {
    public:
        /// @brief Default constructor.
        /// 
        /// @param _pFlashPlayer Flash player which will receive the events.
        CFlashEvent(CFlashPlayer *_pFlashPlayer);

        /// @brief Destructor.
        ~CFlashEvent();

        /// @brief Initialize.        
        void Initialize();

        /// @brief Release flash event.
        void Shutdown();

        /************************************/
        /*              IUnknown            */
        /************************************/
        HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppv);

        ULONG STDMETHODCALLTYPE AddRef();

        ULONG STDMETHODCALLTYPE Release();

        /************************************/
        /*              IDispatch           */
        /************************************/
        HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT* pctinfo);

        HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo);        

        HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId);

        HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, ::DISPPARAMS __RPC_FAR *pDispParams, VARIANT __RPC_FAR *pVarResult, ::EXCEPINFO __RPC_FAR *pExcepInfo, UINT __RPC_FAR *puArgErr);

        /************************************/
        /*      _IShockwaveFlashEvents      */
        /************************************/
        HRESULT STDMETHODCALLTYPE OnReadyStateChange (long newState);

        HRESULT STDMETHODCALLTYPE OnProgress(long percentDone);

        HRESULT STDMETHODCALLTYPE FSCommand(_bstr_t command, _bstr_t args);

        HRESULT STDMETHODCALLTYPE FlashCall(_bstr_t request);

    private:
        CFlashPlayer *m_pFlashPlayer; ///< Flash player which will receive the events.
        LPCONNECTIONPOINT m_ConnectionPoint;
        DWORD m_Cookie;
        int m_iRefCount;
    };
}

#endif // __SR_CFLASH_EVENT__
