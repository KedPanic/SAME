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
#include <input/SamPCH.h>
#include <input/CInputManagerPlf.h>
#include <input/IInputDevice.h>

namespace sam
{
    /// @brief Constructor.
    CInputManager::CInputManager()
        : m_pWinHandle(NULL), m_pDirectInput(NULL), m_pFirstDevice(NULL), m_nCurrentIndex(-1), m_iModifiers(e_MM_None)
    {
    }

    /// @brief Destructor.
    CInputManager::~CInputManager()
    {

    }

    /// @brief Initialize.
    /// 
    /// @param _pWinHandler Window handler to receive input event.
    /// @return True if no error occurred.
    bool CInputManager::Initialize(SAM_HWND _pWinHandler)
    {
		m_pWinHandle = _pWinHandler;

		// Create input system
        HRESULT nResult = DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL);
		if(FAILED(nResult))
		{
			SamLogError("Unable to create directx 8 input system, error code: %d\n", nResult);
			return false;
		}

        return true;
    }

	/// @brief Add a new input device.
	/// 
	/// @return True if no error occurred.
	bool CInputManager::AddDevice(IInputDevice *_pDevice)
	{
		SAM_ASSERT(_pDevice != NULL, "_pDevice is NULL");

		if(m_pFirstDevice == NULL)
			m_pFirstDevice = _pDevice;
		// Add device to the end of the list.
		else if(m_pFirstDevice->Add(_pDevice) == false)
		{
			SamLogWarning("Device %s was already added", _pDevice->GetName());
			return false;
		}

		// set internal index.
		_pDevice->SetIndex(m_nCurrentIndex);
		m_nCurrentIndex++;

		return _pDevice->Init();
	}

    /// @brief Add a new mouse listener.
    /// 
    /// @param _pListener New listener to add.
    void CInputManager::AddInputListener(IInputListener *_pListener)
    {
        SAM_ASSERT(_pListener != NULL, "_pListener is NULL");

        m_aInputListeners.insert(_pListener);
    }

    /// @brief Remove an old mouse listener.
    /// 
    /// @param _pListener Old listener to remove.
    void CInputManager::RemoveInputListener(IInputListener *_pListener)
    {
        m_aInputListeners.erase(_pListener);
    }

	/// @brief Update modifiers.
	/// 
	/// @param _eKey Key id.
	/// @param _bPressed True if key is pressed.
	void CInputManager::UpdateModifiers(EKey _eKey, bool _bPressed)
	{
		EModifierMask eModifier;
		switch(_eKey)
		{
		case e_K_LShift:
			eModifier = e_MM_LShift;
			break;

		case e_K_LCtrl:
			eModifier = e_MM_LCtrl;
			break;

		case e_K_LAlt:
			eModifier = e_MM_LAlt;
			break;

		case e_K_LWin:
			eModifier = e_MM_LWin;
			break;

		case e_K_RShift:
			eModifier = e_MM_RShift;
		
		case e_K_RCtrl:
			eModifier = e_MM_RCtrl;
			break;

		case e_K_RAlt:
			eModifier = e_MM_RAlt;
			break;

		case e_K_RWin:
			eModifier = e_MM_RWin;
			break;

		case e_K_CapsLock:
			eModifier = e_MM_CapsLock;
			break;

		case e_K_NumLock:
			eModifier = e_MM_NumLock;
			break;

		case e_K_ScrollLock:
			eModifier = e_MM_ScrollLock;
			break;

		default:
			return;
		}

		// check if its a modifier.
		if(_bPressed)
			m_iModifiers &= ~_eKey;
		else
			m_iModifiers |= _eKey;
	}

    /// @brief Send event to all input listeners.
    /// 
    /// @param _Event Event to send.
    void CInputManager::FireInputEvent(SInputEvent &_Event)
    {
		_Event.m_iModifiers = m_iModifiers;

        InputListeners::iterator it = m_aInputListeners.begin(), it_end = m_aInputListeners.end();
        while(it != it_end)
        {
            if((*it)->OnInputEvent(_Event))
                break;

            it++;
        }
    }

	/// @brief Set vibration effect of the specified device.
	/// 
	/// @param _nDeviceID Internal device id.
	/// @param _oVibrationParams Vibration effect parameters.
	void CInputManager::SetVibration(int _nDeviceID, const SVibrationParams &_oVibrationParams)
	{
		IInputDevice *_pDevice = GetDevice(_nDeviceID);
		if(_pDevice)
		{
			_pDevice->SetVibration(_oVibrationParams);
		}
	}

    /// @brief Update input device.
	/// 
	/// @param _fElapsedTime Elapsed time since the last frame.
    void CInputManager::Update(float _fElapsedTime)
    {
		IInputDevice *pDevice = m_pFirstDevice;
		while(pDevice)
		{
			if(pDevice->IsEnable())
				pDevice->Update(_fElapsedTime);

			pDevice = pDevice->GetNext();
		}
    }

    /// @brief Shutdown.
    void CInputManager::Shutdown()
    {
		SAM_ASSERT(m_pDirectInput != NULL, "direct input was not initialized");

		// Close all associated physical device.
		IInputDevice *pCurrent = m_pFirstDevice;
		while(pCurrent)
		{
			IInputDevice *pToDelete = pCurrent;
			pCurrent = pCurrent->GetNext();	

			delete pToDelete;
		}

		// Close the input system.
		m_pDirectInput->Release();
		m_pDirectInput = NULL;
    }

    /// @brief Retrieves current pressed input modifiers.
    /// 
    /// @return Return current pressed input modifiers.
    int CInputManager::GetModifiers() const
    {
        return m_iModifiers;
    }

    /// @brief Query if the specified type of device is connected.
    /// 
    /// @param _eDevice Type of device.
    /// @return true if the specified type of device is connected.
    bool CInputManager::HasInputDeviceOfType(EDeviceType _eDevice)
    {
		IInputDevice *pDevice = m_pFirstDevice;
		while(pDevice)
		{
			if(pDevice->GetType() == _eDevice)
				return true;

			pDevice = pDevice->GetNext();
		}

        return false;
    }

	/// @brief Retrieves device by index.
	/// 
	/// @param _nIndex Internal device ID.
	///
	/// @return null or pointer to the device.
	IInputDevice *CInputManager::GetDevice(int _nIndex)
	{
		IInputDevice *pDevice = m_pFirstDevice;
		while(pDevice)
		{
			if(pDevice->GetIndex() == _nIndex)
				return pDevice;

			pDevice = pDevice->GetNext();
		}

		return NULL;
	}
}
