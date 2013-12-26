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
#include "SamInputPCH.h"
#include <input/CInputManager.h>
#include <input/IInputDevice.h>

namespace sam
{
    // Constructor.
    CInputManager::CInputManager()
        : m_pWinHandle(NULL), m_pInputDriver(NULL), m_pFirstDevice(NULL), m_nCurrentIndex(-1), m_nModifiers(e_ModifierMask_None)
    {
    }

    // Destructor.
    CInputManager::~CInputManager()
    {

    }

    // Initialize.
    bool CInputManager::Initialize(SAM_HWND p_pWinHandler)
    {
		m_pWinHandle = p_pWinHandler;

		return InitializeInputDriver();
    }

	// Add a new input device.
	bool CInputManager::AddDevice(IInputDevice *p_pDevice)
	{
		SAM_ASSERT(p_pDevice != NULL, "p_pDevice is NULL");

		if(m_pFirstDevice == NULL)
			m_pFirstDevice = p_pDevice;
		// Add device to the end of the list.
		else if(m_pFirstDevice->Add(p_pDevice) == false)
		{
			SamLogWarning("Device %s was already added", p_pDevice->GetName());
			return false;
		}

		// set internal index.
		p_pDevice->SetIndex(m_nCurrentIndex);
		m_nCurrentIndex++;

		return p_pDevice->Init();
	}

    // Add a new mouse listener.
    void CInputManager::AddInputListener(IInputListener *p_pListener)
    {
        SAM_ASSERT(p_pListener != NULL, "p_pListener is NULL");

        m_aInputListeners.insert(p_pListener);
    }

    // Remove an old mouse listener.
    void CInputManager::RemoveInputListener(IInputListener *p_pListener)
    {
        m_aInputListeners.erase(p_pListener);
    }

	// Update modifiers.
	void CInputManager::UpdateModifiers(EKey p_eKey, bool p_bPressed)
	{
		EModifierMask eModifier;
		switch(p_eKey)
		{
		case e_K_LShift:
			eModifier = e_ModifierMask_LShift;
			break;

		case e_K_LCtrl:
			eModifier = e_ModifierMask_LCtrl;
			break;

		case e_K_LAlt:
			eModifier = e_ModifierMask_LAlt;
			break;

		case e_K_LWin:
			eModifier = e_ModifierMask_LWin;
			break;

		case e_K_RShift:
			eModifier = e_ModifierMask_RShift;

		case e_K_RCtrl:
			eModifier = e_ModifierMask_RCtrl;
			break;

		case e_K_RAlt:
			eModifier = e_ModifierMask_RAlt;
			break;

		case e_K_RWin:
			eModifier = e_ModifierMask_RWin;
			break;

		case e_K_CapsLock:
			eModifier = e_ModifierMask_CapsLock;
			break;

		case e_K_NumLock:
			eModifier = e_ModifierMask_NumLock;
			break;

		case e_K_ScrollLock:
			eModifier = e_ModifierMask_ScrollLock;
			break;

		default:
			return;
		}

		// check if its a modifier.
		if(p_bPressed)
		{
			m_nModifiers &= ~p_eKey;
        }
		else
		{
			m_nModifiers |= p_eKey;
        }
	}

    // Send event to all input listeners.
    void CInputManager::FireInputEvent(SInputEvent &p_Event)
    {
		p_Event.m_nModifiers = m_nModifiers;

        InputListeners::iterator it = m_aInputListeners.begin(), it_end = m_aInputListeners.end();
        while(it != it_end)
        {
            if((*it)->OnInputEvent(p_Event))
                break;

            it++;
        }
    }

	// Set vibration effect of the specified device.
	void CInputManager::SetVibration(int p_nDeviceID, const SVibrationParams &p_oVibrationParams)
	{
		IInputDevice *p_pDevice = GetDevice(p_nDeviceID);
		if(p_pDevice)
		{
			p_pDevice->SetVibration(p_oVibrationParams);
		}
	}

    // Update input device.
    void CInputManager::Update(float p_fElapsedTime)
    {
		IInputDevice *pDevice = m_pFirstDevice;
		while(pDevice)
		{
			if(pDevice->IsEnable())
				pDevice->Update(p_fElapsedTime);

			pDevice = pDevice->GetNext();
		}
    }

    // Shutdown.
    void CInputManager::Shutdown()
    {
		SAM_ASSERT(m_pInputDriver != NULL, "input driver was not initialized");

		// Close all associated physical device.
		IInputDevice *pCurrent = m_pFirstDevice;
		while(pCurrent)
		{
			IInputDevice *pToDelete = pCurrent;
			pCurrent = pCurrent->GetNext();

			delete pToDelete;
		}

		// Close the input driver.
		ShutdownInputDriver();
		m_pInputDriver = NULL;
    }

    // Retrieves current pressed input modifiers.
    int32 CInputManager::GetModifiers() const
    {
        return m_nModifiers;
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
