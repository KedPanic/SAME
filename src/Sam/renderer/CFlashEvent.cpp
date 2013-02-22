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
#include "CFlashEvent.h"
#include "CFlashPlayer.h"
#include "FlashSerialization.h"

namespace sam
{
    /// @brief Default constructor.
    /// 
    /// @param _pFlashPlayer Flash player which will receive the events.
    CFlashEvent::CFlashEvent(CFlashPlayer *_pFlashPlayer)
        : m_pFlashPlayer(_pFlashPlayer), m_ConnectionPoint(0), m_Cookie(0), m_iRefCount(0)
    {}

    /// @brief Destructor.
    CFlashEvent::~CFlashEvent()
    {

    }

    /// @brief Initialize.        
    void CFlashEvent::Initialize()
    {
        LPCONNECTIONPOINTCONTAINER connectionPointContainer = 0;

        if(m_pFlashPlayer->GetFlashObject()->QueryInterface(IID_IConnectionPointContainer, (void**)&connectionPointContainer) == S_OK)
        {
           if(connectionPointContainer->FindConnectionPoint(__uuidof(ShockwaveFlashObjects::_IShockwaveFlashEvents), &m_ConnectionPoint) == S_OK)
           {
               m_ConnectionPoint->Advise(this, &m_Cookie);
               AddRef();
           }

           connectionPointContainer->Release();
        }        
    }

    /// @brief Release flash event.
    void CFlashEvent::Shutdown()
    {
        if(m_ConnectionPoint)
        {
            if(m_Cookie)
            {
                m_ConnectionPoint->Unadvise(m_Cookie);
                m_Cookie = 0;
            }

            m_ConnectionPoint->Release();
            m_ConnectionPoint = 0;
        }
    }

    /************************************/
    /*              IUnknown            */
    /************************************/
    HRESULT STDMETHODCALLTYPE CFlashEvent::QueryInterface(REFIID riid, LPVOID* ppv)
    {
        if(riid == IID_IUnknown || riid == IID_IDispatch || riid == __uuidof(ShockwaveFlashObjects::_IShockwaveFlashEvents))
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

    ULONG STDMETHODCALLTYPE CFlashEvent::AddRef()
    {
       return ++m_iRefCount;
    }

    ULONG STDMETHODCALLTYPE CFlashEvent::Release()
    {
        --m_iRefCount;
//         if(!m_iRefCount)
//             SAM_DELETE this;
        
        return m_iRefCount;
    }

    /************************************/
    /*              IDispatch           */
    /************************************/
    HRESULT STDMETHODCALLTYPE CFlashEvent::GetTypeInfoCount(UINT* pctinfo)
    {
        *pctinfo = 1;
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashEvent::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo)
    {
        *ppTInfo = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CFlashEvent::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId)
    {
        return E_NOTIMPL; 
    }

    HRESULT STDMETHODCALLTYPE CFlashEvent::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, ::DISPPARAMS __RPC_FAR *pDispParams, VARIANT __RPC_FAR *pVarResult, ::EXCEPINFO __RPC_FAR *pExcepInfo, UINT __RPC_FAR *puArgErr)
    {
        switch(dispIdMember)
        {
        case 0x7a6:
            break;
        case 0x96:			
            if((pDispParams->cArgs == 2) && (pDispParams->rgvarg[0].vt == VT_BSTR) && (pDispParams->rgvarg[1].vt == VT_BSTR))
                FSCommand(pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal);
            break;
        case 0xC5:
            if((pDispParams->cArgs == 1) && (pDispParams->rgvarg[0].vt == VT_BSTR))
                FlashCall(pDispParams->rgvarg[0].bstrVal);
            break;
        case DISPID_READYSTATECHANGE:
            break;
        default:
            return DISP_E_MEMBERNOTFOUND;
        } 

        return S_OK;
    }

    /************************************/
    /*      _IShockwaveFlashEvents      */
    /************************************/
    HRESULT STDMETHODCALLTYPE CFlashEvent::OnReadyStateChange (long newState)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashEvent::OnProgress(long percentDone)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashEvent::FSCommand(_bstr_t command, _bstr_t args)
    {
        m_pFlashPlayer->OnFSCommand((wchar_t*)command, (wchar_t*)args);
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CFlashEvent::FlashCall(_bstr_t request)
    {
        UString sFunction;
        int iNbArgs = 0;
        
        // deserialize request.
        if(sam::SFlashArgument *pArgs = helper::FlashCall((wchar_t*)request, sFunction, iNbArgs))
        {
            m_pFlashPlayer->OnExternalInterface(sFunction, pArgs, iNbArgs);

            // release memory.
            if(pArgs)
            {
                helper::FreeString();
                SAM_DELETE_ARRAY pArgs;
            }
        }

        return S_OK;
    }
}
