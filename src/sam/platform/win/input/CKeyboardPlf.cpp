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
#include <input/CKeyboardPlf.h>
#include <input/CInputManager.h>

#define KEY_BUFFERSIZE 16
#define ENABLE_BUFFER_MODE

namespace sam
{
	// Globals variables to convert direct input key to sam key
	EKey g_aDXToSamKey[0xED + 1 /* key code max */] = {e_K_Unknown};

	/// @brief Default constructor.
	CKeyboard::CKeyboard()
		: m_pKeyboard(NULL), m_bEnabled(false)
	{
		g_aDXToSamKey[0] = e_K_Unknown;
		g_aDXToSamKey[DIK_ESCAPE] = e_K_Escape;
        g_aDXToSamKey[DIK_1] = e_K_1;
        g_aDXToSamKey[DIK_2] = e_K_2;
        g_aDXToSamKey[DIK_3] = e_K_3;
        g_aDXToSamKey[DIK_4] = e_K_4;
        g_aDXToSamKey[DIK_5] = e_K_5;
        g_aDXToSamKey[DIK_6] = e_K_6;
        g_aDXToSamKey[DIK_7] = e_K_7;
        g_aDXToSamKey[DIK_8] = e_K_8;
        g_aDXToSamKey[DIK_9] = e_K_9;
        g_aDXToSamKey[DIK_0] = e_K_0;
        g_aDXToSamKey[DIK_MINUS] = e_K_Minus;
        g_aDXToSamKey[DIK_EQUALS] = e_K_Equals;
        g_aDXToSamKey[DIK_BACK] = e_K_Backspace;
        g_aDXToSamKey[DIK_TAB] = e_K_Tab;
        g_aDXToSamKey[DIK_Q] = e_K_Q;
        g_aDXToSamKey[DIK_W] = e_K_W;
        g_aDXToSamKey[DIK_E] = e_K_E;
        g_aDXToSamKey[DIK_R] = e_K_R;
        g_aDXToSamKey[DIK_T] = e_K_T;
        g_aDXToSamKey[DIK_Y] = e_K_Y;
        g_aDXToSamKey[DIK_U] = e_K_U;
        g_aDXToSamKey[DIK_I] = e_K_I;
        g_aDXToSamKey[DIK_O] = e_K_O;
        g_aDXToSamKey[DIK_P] = e_K_P;
        g_aDXToSamKey[DIK_LBRACKET] = e_K_LBracket;
        g_aDXToSamKey[DIK_RBRACKET] = e_K_RBracket;
        g_aDXToSamKey[DIK_RETURN] = e_K_Enter;
        g_aDXToSamKey[DIK_LCONTROL] = e_K_LCtrl;
        g_aDXToSamKey[DIK_A] = e_K_A;
        g_aDXToSamKey[DIK_S] = e_K_S;
        g_aDXToSamKey[DIK_D] = e_K_D;
        g_aDXToSamKey[DIK_F] = e_K_F;
        g_aDXToSamKey[DIK_G] = e_K_G;
        g_aDXToSamKey[DIK_H] = e_K_H;
        g_aDXToSamKey[DIK_J] = e_K_J;
        g_aDXToSamKey[DIK_K] = e_K_K;
        g_aDXToSamKey[DIK_L] = e_K_L;
        g_aDXToSamKey[DIK_SEMICOLON] = e_K_SemiColon;
        g_aDXToSamKey[DIK_APOSTROPHE] = e_K_Apostrophe;
        g_aDXToSamKey[DIK_GRAVE] = e_K_Unknown;
        g_aDXToSamKey[DIK_LSHIFT] = e_K_LShift;
        g_aDXToSamKey[DIK_BACKSLASH] = e_K_Backslash;
        g_aDXToSamKey[DIK_Z] = e_K_Z;
        g_aDXToSamKey[DIK_X] = e_K_X;
        g_aDXToSamKey[DIK_C] = e_K_C;
        g_aDXToSamKey[DIK_V] = e_K_V;
        g_aDXToSamKey[DIK_B] = e_K_B;
        g_aDXToSamKey[DIK_N] = e_K_N;
        g_aDXToSamKey[DIK_M] = e_K_M;
        g_aDXToSamKey[DIK_COMMA] = e_K_Comma;
        g_aDXToSamKey[DIK_PERIOD] = e_K_Period;
        g_aDXToSamKey[DIK_SLASH] = e_K_Slash;
        g_aDXToSamKey[DIK_RSHIFT] = e_K_RShift;
        g_aDXToSamKey[DIK_MULTIPLY] = e_K_NP_Multiply;
        g_aDXToSamKey[DIK_LMENU] = e_K_LAlt;
        g_aDXToSamKey[DIK_SPACE] = e_K_Space;
        g_aDXToSamKey[DIK_CAPITAL] = e_K_CapsLock;
        g_aDXToSamKey[DIK_F1] = e_K_F1;
        g_aDXToSamKey[DIK_F2] = e_K_F2;
        g_aDXToSamKey[DIK_F3] = e_K_F3;
        g_aDXToSamKey[DIK_F4] = e_K_F4;
        g_aDXToSamKey[DIK_F5] = e_K_F5;
        g_aDXToSamKey[DIK_F6] = e_K_F6;
        g_aDXToSamKey[DIK_F7] = e_K_F7;
        g_aDXToSamKey[DIK_F8] = e_K_F8;
        g_aDXToSamKey[DIK_F9] = e_K_F9;
        g_aDXToSamKey[DIK_F10] = e_K_F10;
        g_aDXToSamKey[DIK_NUMLOCK] = e_K_NumLock;
        g_aDXToSamKey[DIK_SCROLL] = e_K_ScrollLock;
        g_aDXToSamKey[DIK_NUMPAD7] = e_K_NP_7;
        g_aDXToSamKey[DIK_NUMPAD8] = e_K_NP_8;
        g_aDXToSamKey[DIK_NUMPAD9] = e_K_NP_9;
        g_aDXToSamKey[DIK_SUBTRACT] = e_K_NP_Substract;
        g_aDXToSamKey[DIK_NUMPAD4] = e_K_NP_4;
        g_aDXToSamKey[DIK_NUMPAD5] = e_K_NP_5;
        g_aDXToSamKey[DIK_NUMPAD6] = e_K_NP_6;
        g_aDXToSamKey[DIK_ADD] = e_K_NP_Add;
        g_aDXToSamKey[DIK_NUMPAD1] = e_K_NP_1;
        g_aDXToSamKey[DIK_NUMPAD2] = e_K_NP_2;
        g_aDXToSamKey[DIK_NUMPAD3] = e_K_NP_3;
        g_aDXToSamKey[DIK_NUMPAD0] = e_K_NP_0;
        g_aDXToSamKey[DIK_DECIMAL] = e_K_NP_Delete;
        g_aDXToSamKey[DIK_OEM_102] = e_K_Unknown;
        g_aDXToSamKey[DIK_F11] = e_K_F11;
        g_aDXToSamKey[DIK_F12] = e_K_F12;
        g_aDXToSamKey[DIK_F13] = e_K_Unknown;
        g_aDXToSamKey[DIK_F14] = e_K_Unknown;
        g_aDXToSamKey[DIK_F15] = e_K_Unknown;
        g_aDXToSamKey[DIK_KANA] = e_K_Unknown;
        g_aDXToSamKey[DIK_ABNT_C1] = e_K_Unknown;
        g_aDXToSamKey[DIK_CONVERT] = e_K_Unknown;
        g_aDXToSamKey[DIK_NOCONVERT] = e_K_Unknown;
        g_aDXToSamKey[DIK_YEN] = e_K_Unknown;
        g_aDXToSamKey[DIK_ABNT_C2] = e_K_Unknown;
        g_aDXToSamKey[DIK_NUMPADEQUALS] = e_K_Unknown;
        g_aDXToSamKey[DIK_PREVTRACK] = e_K_Unknown;
        g_aDXToSamKey[DIK_AT] = e_K_Unknown;
        g_aDXToSamKey[DIK_COLON] = e_K_Unknown;
        g_aDXToSamKey[DIK_UNDERLINE] = e_K_Unknown;
        g_aDXToSamKey[DIK_KANJI] = e_K_Unknown;
		g_aDXToSamKey[DIK_STOP] = e_K_Unknown;
		g_aDXToSamKey[DIK_AX] = e_K_Unknown;
		g_aDXToSamKey[DIK_UNLABELED] = e_K_Unknown;
		g_aDXToSamKey[DIK_NEXTTRACK] = e_K_Unknown;
		g_aDXToSamKey[DIK_NUMPADENTER] = e_K_NP_Enter;
		g_aDXToSamKey[DIK_RCONTROL] = e_K_RCtrl;
		g_aDXToSamKey[DIK_MUTE] = e_K_Unknown;
		g_aDXToSamKey[DIK_CALCULATOR] = e_K_Unknown;
		g_aDXToSamKey[DIK_PLAYPAUSE] = e_K_Unknown;
		g_aDXToSamKey[DIK_MEDIASTOP] = e_K_Unknown;
		g_aDXToSamKey[DIK_VOLUMEDOWN] = e_K_Unknown;
		g_aDXToSamKey[DIK_VOLUMEUP] = e_K_Unknown;
		g_aDXToSamKey[DIK_WEBHOME] = e_K_Unknown;
		g_aDXToSamKey[DIK_NUMPADCOMMA] = e_K_NP_Delete;
		g_aDXToSamKey[DIK_DIVIDE] = e_K_NP_Divide;
		g_aDXToSamKey[DIK_SYSRQ] = e_K_Unknown;
		g_aDXToSamKey[DIK_RMENU] = e_K_RAlt;
		g_aDXToSamKey[DIK_PAUSE] = e_K_Unknown;
		g_aDXToSamKey[DIK_HOME] = e_K_Home;
		g_aDXToSamKey[DIK_UP] = e_K_Up;
		g_aDXToSamKey[DIK_PRIOR] = e_K_PageUp;
		g_aDXToSamKey[DIK_LEFT] = e_K_Left;
		g_aDXToSamKey[DIK_RIGHT] = e_K_Right;
		g_aDXToSamKey[DIK_END] = e_K_End;
		g_aDXToSamKey[DIK_DOWN] = e_K_Down;
		g_aDXToSamKey[DIK_NEXT] = e_K_PageDown;
		g_aDXToSamKey[DIK_INSERT] = e_K_Insert;
		g_aDXToSamKey[DIK_DELETE] = e_K_Delete;
		g_aDXToSamKey[DIK_LWIN] = e_K_LWin;
		g_aDXToSamKey[DIK_RWIN] = e_K_RWin;
		g_aDXToSamKey[DIK_APPS] = e_K_Unknown;
		g_aDXToSamKey[DIK_POWER] = e_K_Unknown;
		g_aDXToSamKey[DIK_SLEEP] = e_K_Unknown;
		g_aDXToSamKey[DIK_WAKE] = e_K_Unknown;
		g_aDXToSamKey[DIK_WEBSEARCH] = e_K_Unknown;
		g_aDXToSamKey[DIK_WEBFAVORITES] = e_K_Unknown;
		g_aDXToSamKey[DIK_WEBREFRESH] = e_K_Unknown;
		g_aDXToSamKey[DIK_WEBSTOP] = e_K_Unknown;
		g_aDXToSamKey[DIK_WEBFORWARD] = e_K_Unknown;
		g_aDXToSamKey[DIK_WEBBACK] = e_K_Unknown;
		g_aDXToSamKey[DIK_MYCOMPUTER] = e_K_Unknown;
		g_aDXToSamKey[DIK_MAIL] = e_K_Unknown;
		g_aDXToSamKey[DIK_MEDIASELECT] = e_K_Unknown;

		memset(m_aKeyStates, 0, sizeof(m_aKeyStates));
	}

	/// @brief Destructor.
	CKeyboard::~CKeyboard()
	{
		if(m_pKeyboard)
		{
			m_pKeyboard->Unacquire();
			m_pKeyboard->Release();
		}
	}

	/// @brief Initialize the device.
	/// 
	/// @return true if no error occurred.
	bool CKeyboard::Init()
	{
		SAM_ASSERT(m_pKeyboard == NULL, "Keyboard is already initialized");

		// create device
		HRESULT hResult = g_Env->pInputManager->GetInputDriver()->m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);
		if(FAILED(hResult))
		{
			SamLogWarning("Unable to create keyboard device, error code: %d\n", hResult);
			return false;
		}

		hResult = m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if(FAILED(hResult))
		{
			SamLogError("Unable to set data format for keyboard device, error code: %d\n", hResult);
			return false;
		}

#ifdef ENABLE_BUFFER_MODE
		// Enable buffered mode.
		DIPROPDWORD oProperty;
		oProperty.diph.dwSize = sizeof(DIPROPDWORD);
		oProperty.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		oProperty.diph.dwObj = 0;
		oProperty.diph.dwHow = DIPH_DEVICE;
		oProperty.dwData = KEY_BUFFERSIZE;

		hResult = m_pKeyboard->SetProperty(DIPROP_BUFFERSIZE, &oProperty.diph);
		if(FAILED(hResult))
		{
			SamLogError("Unable to set buffered mode for keyboard device, error code: %d\n", hResult);
			return false;
		}
#endif

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
	void CKeyboard::Update(float _fElapsedTime)
	{		
#ifdef ENABLE_BUFFER_MODE
		DIDEVICEOBJECTDATA oBuffer[KEY_BUFFERSIZE];
		DWORD nNbItems = KEY_BUFFERSIZE;
		HRESULT hResult = m_pKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), oBuffer, &nNbItems, 0);

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
			oEvent.m_eDevice = e_DT_Keyboard;
			oEvent.m_eKey    = g_aDXToSamKey[nKey];
			oEvent.m_eState  = oBuffer[nNbItems].dwData & 0x80?e_IS_Pressed:e_IS_Released;
			oEvent.m_iInternalID = 0;
			oEvent.m_nModifiers = 0;
			oEvent.m_sKeyName = g_aKeyName[oEvent.m_eKey];

			// update modifiers.
			g_Env->pInputManager->UpdateModifiers(oEvent.m_eKey, oEvent.m_eState == e_IS_Pressed);

			// send input event.
			g_Env->pInputManager->FireInputEvent(oEvent);

			// memorise current state.
			m_aKeyStates[nKey] = (unsigned char)oBuffer[nNbItems].dwData;
		}
#else
		unsigned char aKeyBuffer[256];
		HRESULT hResult = m_pKeyboard->GetDeviceState();

		// check if access to the device has been lost
		if(hResult != S_OK)
		{
			Enable(true);
			return;
		}

		// check state
		for(int i = 0; i < 256; ++i)
		{
			if(aKeyBuffer[i] != m_aKeyStates[i])
			{
				// setup event.
				SInputEvent oEvent;
				oEvent.m_eDevice = e_DT_Keyboard;
				oEvent.m_eKey    = g_aDXToSamKey[i];
				oEvent.m_eState  = aKeyBuffer[i] & 0x80?e_IS_Pressed:e_IS_Released;
				oEvent.m_iInternalID = 0;
				oEvent.m_iModifiers = 0;
				oEvent.m_iValue   = 0;
				oEvent.m_sKeyName = g_aKeyName[i];

				// update modifiers.
				g_Env->pInputManager->UpdateModifiers(oEvent.m_eKey, oEvent.m_eState == e_IS_Pressed);

				// send input event.
				g_Env->pInputManager->FireInputEvent(oEvent);

				// memorise current state.
				m_aKeyStates[i] = aKeyBuffer[i];
			}
		}
#endif
	}

	/// @brief Enable the device.
	/// 
	/// @param _bEnable True to enable the device.
	/// 
	/// @return True if no error occurred.
	bool CKeyboard::Enable(bool _bEnable)
	{
		SAM_ASSERT(m_pKeyboard != NULL, "Keyboard was not initialized");

		m_bEnabled = _bEnable;

		HRESULT hResult = S_OK;
		if(_bEnable)
			hResult = m_pKeyboard->Acquire();
		else
			hResult = m_pKeyboard->Unacquire();

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
	bool CKeyboard::IsEnable() const
	{
		return m_bEnabled;
	}

	/// @brief Exclusive mode.
	/// 
	/// @param _bExclusive True to active exclusive mode.
	/// 
	/// @return True if no error occurred.
	bool CKeyboard::SetExclusiveMode(bool _bExclusive)
	{
		SAM_ASSERT(m_pKeyboard != NULL, "Keyboard was not initialized");

		int nFlags = DISCL_FOREGROUND;
		if(_bExclusive)
			nFlags |= DISCL_EXCLUSIVE;
		else
			nFlags |= DISCL_NONEXCLUSIVE | DISCL_NOWINKEY;

		HRESULT hResult = m_pKeyboard->SetCooperativeLevel(g_Env->pInputManager->GetHWND(), nFlags);
		if(FAILED(hResult))
		{
			SamLogWarning("Unable to set exclusive mode for keyboard device, error code: %d", hResult);
			return false;
		}

		return true;
	}
}
