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
#include <input/CMousePlf.h>
#include <input/CInputManagerPlf.h>

#define MOUSE_BUFFERSIZE 64

namespace sam
{
	/// @brief Default constructor.
	CMouse::CMouse()
		: m_pMouse(NULL), m_bEnabled(false)
	{		
	}

	/// @brief Destructor.
	CMouse::~CMouse()
	{
		if(m_pMouse)
		{
			m_pMouse->Unacquire();
			m_pMouse->Release();
		}
	}

	/// @brief Initialize the device.
	/// 
	/// @return true if no error occurred.
	bool CMouse::Init()
	{
		SAM_ASSERT(m_pMouse == NULL, "Mouse is already initialized");

		// create device
		HRESULT hResult = g_Env->pInputManager->GetInputSystem()->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);
		if(FAILED(hResult))
		{
			SamLogWarning("Unable to create keyboard device, error code: %d\n", hResult);
			return false;
		}

		hResult = m_pMouse->SetDataFormat(&c_dfDIMouse2);
		if(FAILED(hResult))
		{
			SamLogError("Unable to set data format for keyboard device, error code: %d\n", hResult);
			return false;
		}

		// Enable buffered mode.
		DIPROPDWORD oProperty;
		oProperty.diph.dwSize = sizeof(DIPROPDWORD);
		oProperty.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		oProperty.diph.dwObj = 0;
		oProperty.diph.dwHow = DIPH_DEVICE;
		oProperty.dwData = MOUSE_BUFFERSIZE;

		hResult = m_pMouse->SetProperty(DIPROP_BUFFERSIZE, &oProperty.diph);
		if(FAILED(hResult))
		{
			SamLogError("Unable to set buffered mode for keyboard device, error code: %d\n", hResult);
			return false;
		}

		// Exclusive by default.
		if(!SetExclusiveMode(false))
			return false;

		// Enable the device.
		if(!Enable(true))
			return false;

		return true;
	}

	/// @brief Update the device.
	///
	/// @param _fElapsedTime Elapsed time since the last frame.
	void CMouse::Update(float _fElapsedTime)
	{		
		DIDEVICEOBJECTDATA oBuffer[MOUSE_BUFFERSIZE];
		DWORD nNbItems = MOUSE_BUFFERSIZE;
		HRESULT hResult = m_pMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), oBuffer, &nNbItems, 0);

		// check if access to the device has been lost
		if(hResult != S_OK)
		{
			Enable(true);
			return;
		}

		// check state
		while(nNbItems--)
		{
			unsigned int nKey = (unsigned int)oBuffer[nNbItems].dwOfs;

			// setup event.
			SInputEvent oEvent;
			oEvent.m_eDevice = e_DT_Mouse;
			switch(oBuffer[nNbItems].dwOfs)
			{
			case DIMOFS_BUTTON0:
				oEvent.m_eKey = e_K_Mouse_1;
				oEvent.m_eState = oBuffer[nNbItems].dwData & 0x80?e_IS_Pressed:e_IS_Released;
				break;

			case DIMOFS_BUTTON1:
				oEvent.m_eKey = e_K_Mouse_2;
				oEvent.m_eState = oBuffer[nNbItems].dwData & 0x80?e_IS_Pressed:e_IS_Released;
				break;

			case DIMOFS_BUTTON2:
				oEvent.m_eKey = e_K_Mouse_3;
				oEvent.m_eState = oBuffer[nNbItems].dwData & 0x80?e_IS_Pressed:e_IS_Released;
				break;

			case DIMOFS_BUTTON3:
				oEvent.m_eKey = e_K_Mouse_4;
				oEvent.m_eState = oBuffer[nNbItems].dwData & 0x80?e_IS_Pressed:e_IS_Released;
				break;

			case DIMOFS_BUTTON4:
				oEvent.m_eKey = e_K_Mouse_5;
				oEvent.m_eState = oBuffer[nNbItems].dwData & 0x80?e_IS_Pressed:e_IS_Released;
				break;

			case DIMOFS_X:
				oEvent.m_eKey = e_K_Mouse_X;
				oEvent.m_eState = e_IS_Changed;
				oEvent.m_fValue = (float)oBuffer[nNbItems].dwData;
				break;

			case DIMOFS_Y:
				oEvent.m_eKey = e_K_Mouse_Y;
				oEvent.m_eState = e_IS_Changed;
				oEvent.m_fValue = (float)oBuffer[nNbItems].dwData;
				break;

			case DIMOFS_Z:				
				oEvent.m_eState = e_IS_Changed;
				oEvent.m_fValue = (float)oBuffer[nNbItems].dwData;
				oEvent.m_eKey = oEvent.m_fValue > 0?e_K_Mouse_WheelUp:e_K_Mouse_WheelDown;
				break;

			default:
				oEvent.m_eKey = e_K_Unknown;
				oEvent.m_eState = e_IS_Unknown;
			}			
			
			oEvent.m_iInternalID = 0;
			oEvent.m_iModifiers = 0;			
			oEvent.m_sKeyName = g_aKeyName[oEvent.m_eKey];

			// send input event.
			g_Env->pInputManager->FireInputEvent(oEvent);			
		}
	}

	/// @brief Enable the device.
	/// 
	/// @param _bEnable True to enable the device.
	/// 
	/// @return True if no error occurred.
	bool CMouse::Enable(bool _bEnable)
	{
		SAM_ASSERT(m_pMouse != NULL, "Keyboard was not initialized");

		m_bEnabled = _bEnable;

		HRESULT hResult = S_OK;
		if(_bEnable)
			hResult = m_pMouse->Acquire();
		else
			hResult = m_pMouse->Unacquire();

		if(FAILED(hResult))
		{
			SamLogWarning("Unable to enable the keyboard device, error code: %d", hResult);
			return false;
		}

		return true;
	}

	/// @brief Retrieves if device is active.
	///
	/// @return True if device is active.
	bool CMouse::IsEnable() const
	{
		return m_bEnabled;
	}

	/// @brief Exclusive mode.
	/// 
	/// @param _bExclusive True to active exclusive mode.
	/// 
	/// @return True if no error occurred.
	bool CMouse::SetExclusiveMode(bool _bExclusive)
	{
		SAM_ASSERT(m_pMouse != NULL, "Keyboard was not initialized");

		int nFlags = DISCL_FOREGROUND;
		if(_bExclusive)
			nFlags |= DISCL_EXCLUSIVE;
		else
			nFlags |= DISCL_NONEXCLUSIVE | DISCL_NOWINKEY;

		HRESULT hResult = m_pMouse->SetCooperativeLevel(g_Env->pInputManager->GetHWND(), nFlags);
		if(FAILED(hResult))
		{
			SamLogWarning("Unable to set exclusive mode for keyboard device, error code: %d", hResult);
			return false;
		}

		return true;
	}
}
