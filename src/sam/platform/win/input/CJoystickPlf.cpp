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
#include <input/SVibrationEffect.h>
#include <input/CInputManager.h>
#include <input/CJoystickPlf.h>

namespace sam
{
	int g_aJoyKey[] = {
		XINPUT_GAMEPAD_DPAD_UP,			e_K_Joy_PadUp,
		XINPUT_GAMEPAD_DPAD_DOWN,		e_K_Joy_PadDown,
		XINPUT_GAMEPAD_DPAD_LEFT,		e_K_Joy_PadLeft,
		XINPUT_GAMEPAD_DPAD_RIGHT,		e_K_Joy_PadRight,
		XINPUT_GAMEPAD_START,			e_K_Joy_Start,
		XINPUT_GAMEPAD_BACK,			e_K_Joy_Select,
		XINPUT_GAMEPAD_LEFT_THUMB,		e_K_Joy_L3,
		XINPUT_GAMEPAD_RIGHT_THUMB,		e_K_Joy_R3,
		XINPUT_GAMEPAD_LEFT_SHOULDER,	e_K_Joy_L1,
		XINPUT_GAMEPAD_RIGHT_SHOULDER,	e_K_Joy_R1,
		XINPUT_GAMEPAD_A,				e_K_Joy_1,
		XINPUT_GAMEPAD_B,				e_K_Joy_2,
		XINPUT_GAMEPAD_X,				e_K_Joy_3,
		XINPUT_GAMEPAD_Y,				e_K_Joy_4,
	};
#define JOYKEY_ARRAY_SIZE 28 ///< to do not compute it per frame.

	int CJoystick::m_nCurrentIndex = 0;
	/// @brief Default constructor.
	CJoystick::CJoystick()
		: m_nUserIndex(-1), m_bEnabled(false), m_bConnected(false), m_fDeadZone(0.25f)
	{
		memset(&m_oState, 0, sizeof(XINPUT_STATE));
		memset(&m_oVibration, 0, sizeof(XINPUT_VIBRATION));
	}

	/// @brief Destructor.
	CJoystick::~CJoystick()
	{
	}

	/// @brief Initialize the device.
	/// 
	/// @return true if no error occurred.
	bool CJoystick::Init()
	{
		SAM_ASSERT(m_nUserIndex == -1, "Joystick was already initialized");
		SAM_ASSERT(m_nCurrentIndex < 4, "Too many joystick created, only 4 are supported");
		
		// set index.
		m_nUserIndex = m_nCurrentIndex;
		m_nCurrentIndex++;

		// Enable the device.
		Enable(true);

		// check if input is connected.		
		XINPUT_STATE oState;
		return XInputGetState(m_nUserIndex, &oState) == ERROR_SUCCESS;
	}

	/// @brief Update the device.
	///
	/// @param _fElapsedTime Elapsed time since the last frame.
	void CJoystick::Update(float _fElapsedTime)
	{	
		// setup event.
		SInputEvent oEvent;
		oEvent.m_eDevice = e_DT_Joystick;
		oEvent.m_iInternalID = m_nIndex;
		oEvent.m_nModifiers = 0;

		// retreive input state.
		XINPUT_STATE oState;
		DWORD dwResult = XInputGetState(m_nUserIndex, &oState);
		if(dwResult != ERROR_SUCCESS)
		{			
			if(!m_bConnected)
				return; // waiting...
		
			// disconnected.
			m_bConnected = false;
			oEvent.m_eKey = e_K_Disconnected;
			oEvent.m_eState = e_IS_Changed;			
			oEvent.m_sKeyName = g_aKeyName[oEvent.m_eKey];

			// send input event.
			g_Env->pInputManager->FireInputEvent(oEvent);

			return; // no more need to be updated
		}
		// send connected event.
		else if(m_bConnected == false)
		{
			// connected.
			m_bConnected = true;
			oEvent.m_eKey = e_K_Connected;
			oEvent.m_eState = e_IS_Changed;
			oEvent.m_sKeyName = g_aKeyName[oEvent.m_eKey];

			// send input event.
			g_Env->pInputManager->FireInputEvent(oEvent);
		}
		
		// check input state.
		if(oState.dwPacketNumber != m_oState.dwPacketNumber)
		{
			m_oState.dwPacketNumber = oState.dwPacketNumber;

			//--------------------------
			// check if buttons changes.
			//--------------------------
			if(oState.Gamepad.wButtons != m_oState.Gamepad.wButtons)
			{
				for(int i = 0; i < JOYKEY_ARRAY_SIZE; i += 2)
				{
					// check if its pressed.
					if(oState.Gamepad.wButtons & g_aJoyKey[i])
					{
						// check if already pressed.
						if(!(m_oState.Gamepad.wButtons & g_aJoyKey[i]))
						{
							oEvent.m_eState = e_IS_Pressed;
							oEvent.m_eKey = (sam::EKey)g_aJoyKey[i + 1];

							// send button event.
							SendEvent(oEvent);
						}
					}
					// check if its released.
					else if(m_oState.Gamepad.wButtons & g_aJoyKey[i])
					{
						oEvent.m_eState = e_IS_Released;
						oEvent.m_eKey = (sam::EKey)g_aJoyKey[i + 1];

						// send button event.
						SendEvent(oEvent);
					}					
				}

				m_oState.Gamepad.wButtons = oState.Gamepad.wButtons;
			}

			//--------------------------
			// check if sticks changes.
			//--------------------------
			if(oState.Gamepad.sThumbLX != m_oState.Gamepad.sThumbLX || oState.Gamepad.sThumbLY != m_oState.Gamepad.sThumbLY)
			{			
				float _fNormalizedThumbX, _fNormalizedThumbY;

				oEvent.m_eState = e_IS_Changed;
				if(PrepareStickEvent(oState.Gamepad.sThumbLX, oState.Gamepad.sThumbLY, _fNormalizedThumbX, _fNormalizedThumbY))
				{
					// x-axis
					if(oState.Gamepad.sThumbLX != m_oState.Gamepad.sThumbLX)
					{
						oEvent.m_eKey = e_K_Joy_LStickX;					
						oEvent.m_fValue = _fNormalizedThumbX;
						SendEvent(oEvent);
					}

					// y-axis
					if(oState.Gamepad.sThumbLY != m_oState.Gamepad.sThumbLY)
					{
						oEvent.m_eKey = e_K_Joy_LStickY;
						oEvent.m_fValue = _fNormalizedThumbY;
						SendEvent(oEvent);
					}

					m_oState.Gamepad.sThumbLX  = oState.Gamepad.sThumbLX;
					m_oState.Gamepad.sThumbLY  = oState.Gamepad.sThumbLY;
				}				
			}

			if(oState.Gamepad.sThumbRX != m_oState.Gamepad.sThumbRX || oState.Gamepad.sThumbRY != m_oState.Gamepad.sThumbRY)
			{			
				float _fNormalizedThumbX, _fNormalizedThumbY;

				oEvent.m_eState = e_IS_Changed;
				if(PrepareStickEvent(oState.Gamepad.sThumbRX, oState.Gamepad.sThumbRY, _fNormalizedThumbX, _fNormalizedThumbY))
				{
					// x-axis
					if(oState.Gamepad.sThumbLX != m_oState.Gamepad.sThumbLX)
					{
						oEvent.m_eKey = e_K_Joy_RStickX;					
						oEvent.m_fValue = _fNormalizedThumbX;
						SendEvent(oEvent);
					}

					// y-axis
					if(oState.Gamepad.sThumbLY != m_oState.Gamepad.sThumbLY)
					{
						oEvent.m_eKey = e_K_Joy_RStickY;
						oEvent.m_fValue = _fNormalizedThumbY;
						SendEvent(oEvent);
					}

					m_oState.Gamepad.sThumbRX  = oState.Gamepad.sThumbRX;
					m_oState.Gamepad.sThumbRY  = oState.Gamepad.sThumbRY;
				}				
			}

			//--------------------------
			// check if trigger changes.
			//--------------------------
			if(oState.Gamepad.bLeftTrigger != m_oState.Gamepad.bLeftTrigger)
			{				
				// check if in dead zone.
				if(oState.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
				{
					oState.Gamepad.bLeftTrigger = 0;
					oEvent.m_eState = e_IS_Released;
				}
				else
					oEvent.m_eState = e_IS_Changed;
				
				// check if already in dead zone.
				if(oState.Gamepad.bLeftTrigger != m_oState.Gamepad.bLeftTrigger)
				{
					oEvent.m_fValue = oState.Gamepad.bLeftTrigger;
					oEvent.m_eKey = e_K_Joy_L2;
					SendEvent(oEvent);

					m_oState.Gamepad.bLeftTrigger  = oState.Gamepad.bLeftTrigger;
				}
			}

			if(oState.Gamepad.bRightTrigger != m_oState.Gamepad.bRightTrigger)
			{				
				// check if in dead zone.
				if(oState.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
				{
					oState.Gamepad.bRightTrigger = 0;
					oEvent.m_eState = e_IS_Released;
				}
				else
					oEvent.m_eState = e_IS_Changed;

				// check if already in dead zone.
				if(oState.Gamepad.bRightTrigger != m_oState.Gamepad.bRightTrigger)
				{
					oEvent.m_fValue = oState.Gamepad.bRightTrigger;
					oEvent.m_eState = e_IS_Changed;
					oEvent.m_eKey = e_K_Joy_R2;
					SendEvent(oEvent);

					m_oState.Gamepad.bRightTrigger  = oState.Gamepad.bRightTrigger;
				}
			}
		}

		// update vibration.
		m_oVibrationEffect.Process(this, _fElapsedTime);
		if(m_oVibrationEffect.m_nMotor & e_VM_Motor_0)
			m_oVibration.wLeftMotorSpeed = (unsigned short)(m_oVibrationEffect.GetCurrentLevel() * 65535.0f);
		if(m_oVibrationEffect.m_nMotor & e_VM_Motor_1)
			m_oVibration.wRightMotorSpeed = (unsigned short)(m_oVibrationEffect.GetCurrentLevel() * 65535.0f);
		
		XInputSetState(m_nUserIndex, &m_oVibration);
	}

	/// @brief Enable the device.
	/// 
	/// @param _bEnable True to enable the device.
	/// 
	/// @return True if no error occurred.
	bool CJoystick::Enable(bool _bEnable)
	{
		m_bEnabled = _bEnable;

		XInputEnable(m_bEnabled);
		return true;
	}

	/// @brief Retrieves if device is active.
	///
	/// @return True if device is active.
	bool CJoystick::IsEnable() const
	{
		return m_bEnabled;
	}

	/// @brief Set vibration effect.
	/// 
	/// @param _oVibrationParams Vibration effect parameters.
	bool CJoystick::SetVibration(const SVibrationParams &_oVibrationParams)
	{
		m_oVibrationEffect.SetParameters(_oVibrationParams);
		return true;
	}
}
