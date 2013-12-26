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

#include <X11/keysym.h>

#define KEY_BUFFERSIZE 16
#define ENABLE_BUFFER_MODE

namespace sam
{
	// Globals variables to convert direct input key to sam key
	std::map<int, EKey> g_aXToSamKey;

	// Default constructor.
	CKeyboard::CKeyboard()
		: m_pDisplay(NULL), m_bEnabled(false)
	{
		g_aXToSamKey[XK_Escape] = e_K_Escape;
        g_aXToSamKey[XK_1] = e_K_1;
        g_aXToSamKey[XK_2] = e_K_2;
        g_aXToSamKey[XK_3] = e_K_3;
        g_aXToSamKey[XK_4] = e_K_4;
        g_aXToSamKey[XK_5] = e_K_5;
        g_aXToSamKey[XK_6] = e_K_6;
        g_aXToSamKey[XK_7] = e_K_7;
        g_aXToSamKey[XK_8] = e_K_8;
        g_aXToSamKey[XK_9] = e_K_9;
        g_aXToSamKey[XK_0] = e_K_0;
        g_aXToSamKey[XK_minus] = e_K_Minus;
        g_aXToSamKey[XK_equal] = e_K_Equals;
        g_aXToSamKey[XK_BackSpace] = e_K_Backspace;
        g_aXToSamKey[XK_Tab] = e_K_Tab;
        g_aXToSamKey[XK_q] = e_K_Q;
        g_aXToSamKey[XK_w] = e_K_W;
        g_aXToSamKey[XK_e] = e_K_E;
        g_aXToSamKey[XK_r] = e_K_R;
        g_aXToSamKey[XK_t] = e_K_T;
        g_aXToSamKey[XK_y] = e_K_Y;
        g_aXToSamKey[XK_u] = e_K_U;
        g_aXToSamKey[XK_i] = e_K_I;
        g_aXToSamKey[XK_o] = e_K_O;
        g_aXToSamKey[XK_p] = e_K_P;
        g_aXToSamKey[XK_bracketleft] = e_K_LBracket;
        g_aXToSamKey[XK_braceright] = e_K_RBracket;
        g_aXToSamKey[XK_Return] = e_K_Enter;
        g_aXToSamKey[XK_Control_L] = e_K_LCtrl;
        g_aXToSamKey[XK_a] = e_K_A;
        g_aXToSamKey[XK_s] = e_K_S;
        g_aXToSamKey[XK_d] = e_K_D;
        g_aXToSamKey[XK_f] = e_K_F;
        g_aXToSamKey[XK_g] = e_K_G;
        g_aXToSamKey[XK_h] = e_K_H;
        g_aXToSamKey[XK_j] = e_K_J;
        g_aXToSamKey[XK_k] = e_K_K;
        g_aXToSamKey[XK_l] = e_K_L;
        g_aXToSamKey[XK_semicolon] = e_K_SemiColon;
        g_aXToSamKey[XK_apostrophe] = e_K_Apostrophe;
        g_aXToSamKey[XK_grave] = e_K_Unknown;
        g_aXToSamKey[XK_Shift_L] = e_K_LShift;
        g_aXToSamKey[XK_backslash] = e_K_Backslash;
        g_aXToSamKey[XK_z] = e_K_Z;
        g_aXToSamKey[XK_x] = e_K_X;
        g_aXToSamKey[XK_c] = e_K_C;
        g_aXToSamKey[XK_v] = e_K_V;
        g_aXToSamKey[XK_b] = e_K_B;
        g_aXToSamKey[XK_n] = e_K_N;
        g_aXToSamKey[XK_m] = e_K_M;
        g_aXToSamKey[XK_comma] = e_K_Comma;
        g_aXToSamKey[XK_period] = e_K_Period;
        g_aXToSamKey[XK_slash] = e_K_Slash;
        g_aXToSamKey[XK_Shift_R] = e_K_RShift;
        g_aXToSamKey[XK_multiply] = e_K_NP_Multiply;
        g_aXToSamKey[XK_Alt_L] = e_K_LAlt;
        g_aXToSamKey[XK_space] = e_K_Space;
        g_aXToSamKey[XK_Caps_Lock] = e_K_CapsLock;
        g_aXToSamKey[XK_F1] = e_K_F1;
        g_aXToSamKey[XK_F2] = e_K_F2;
        g_aXToSamKey[XK_F3] = e_K_F3;
        g_aXToSamKey[XK_F4] = e_K_F4;
        g_aXToSamKey[XK_F5] = e_K_F5;
        g_aXToSamKey[XK_F6] = e_K_F6;
        g_aXToSamKey[XK_F7] = e_K_F7;
        g_aXToSamKey[XK_F8] = e_K_F8;
        g_aXToSamKey[XK_F9] = e_K_F9;
        g_aXToSamKey[XK_F10] = e_K_F10;
        g_aXToSamKey[XK_Num_Lock] = e_K_NumLock;
        g_aXToSamKey[XK_Scroll_Lock] = e_K_ScrollLock;
        g_aXToSamKey[XK_KP_7] = e_K_NP_7;
        g_aXToSamKey[XK_KP_8] = e_K_NP_8;
        g_aXToSamKey[XK_KP_9] = e_K_NP_9;
        g_aXToSamKey[XK_KP_Subtract] = e_K_NP_Substract;
        g_aXToSamKey[XK_KP_4] = e_K_NP_4;
        g_aXToSamKey[XK_KP_5] = e_K_NP_5;
        g_aXToSamKey[XK_KP_6] = e_K_NP_6;
        g_aXToSamKey[XK_KP_Add] = e_K_NP_Add;
        g_aXToSamKey[XK_KP_1] = e_K_NP_1;
        g_aXToSamKey[XK_KP_2] = e_K_NP_2;
        g_aXToSamKey[XK_KP_3] = e_K_NP_3;
        g_aXToSamKey[XK_KP_0] = e_K_NP_0;
        g_aXToSamKey[XK_KP_Delete] = e_K_NP_Delete;
        g_aXToSamKey[XK_F11] = e_K_F11;
        g_aXToSamKey[XK_F12] = e_K_F12;
		g_aXToSamKey[XK_KP_Enter] = e_K_NP_Enter;
		g_aXToSamKey[XK_Control_R] = e_K_RCtrl;
		g_aXToSamKey[XK_KP_Divide] = e_K_NP_Divide;
		g_aXToSamKey[XK_Alt_R] = e_K_RAlt;
		g_aXToSamKey[XK_Home] = e_K_Home;
		g_aXToSamKey[XK_Up] = e_K_Up;
		g_aXToSamKey[XK_Page_Up] = e_K_PageUp;
		g_aXToSamKey[XK_Left] = e_K_Left;
		g_aXToSamKey[XK_Right] = e_K_Right;
		g_aXToSamKey[XK_End] = e_K_End;
		g_aXToSamKey[XK_Down] = e_K_Down;
		g_aXToSamKey[XK_Page_Down] = e_K_PageDown;
		g_aXToSamKey[XK_Insert] = e_K_Insert;
		g_aXToSamKey[XK_Delete] = e_K_Delete;
		g_aXToSamKey[XK_Meta_L] = e_K_LWin;
		g_aXToSamKey[XK_Meta_R] = e_K_RWin;

		memset(m_aKeyStates, 0, sizeof(m_aKeyStates));
	}

	// Destructor.
	CKeyboard::~CKeyboard()
	{
		SAM_ASSERT(m_pDisplay != NULL, "Should be closed before destroyed");
	}

	// Initialize the device.
	bool CKeyboard::Init()
	{
		SAM_ASSERT(m_pDisplay == NULL, "Keyboard is already initialized");

        // open X connection.
        m_pDisplay = XOpenDisplay(NULL);
		if(!m_pDisplay)
		{
            SamLogError("Unable to create keyboard device, unable to connect to X\n");
            return false;
		}

		// listen keyboard events.
		SAM_HWND oWindow = g_Env->pInputManager->GetHWND();
		int nResult = XSelectInput(m_pDisplay, oWindow, KeyPressMask | KeyReleaseMask);
		if(nResult != Success)
		{
			SamLogError("Unable to create keyboard device, X error code: %d\n", nResult);
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

	// Update the device.
	void CKeyboard::Update(float p_fElapsedTime)
	{
        XEvent oXEvent;
        SInputEvent oEvent;

        while(XPending(m_pDisplay) > 0)
        {
            XNextEvent(m_pDisplay, &oXEvent);

            KeySym nKey = XLookupKeysym(&oXEvent.xkey, 0);
            std::map<int, EKey>::iterator oIt = g_aXToSamKey.find(nKey);
            if(oIt != g_aXToSamKey.end())
            {
                oEvent.m_eKey = oIt->second;
            }
            else
            {
                oEvent.m_eKey = e_K_Unknown;
            }

            // setup event.
            oEvent.m_eDevice = e_DT_Keyboard;
            oEvent.m_eState  = oXEvent.type == KeyPress?e_IS_Pressed:e_IS_Released;
            oEvent.m_iInternalID = 0;
            oEvent.m_nModifiers = 0;
            oEvent.m_sKeyName = g_aKeyName[oEvent.m_eKey];

            // update modifiers.
            g_Env->pInputManager->UpdateModifiers(oEvent.m_eKey, oEvent.m_eState == e_IS_Pressed);

            // send input event.
            g_Env->pInputManager->FireInputEvent(oEvent);

            // memorise current state.
            m_aKeyStates[nKey] = oXEvent.xkey.keycode;
        }
	}

	// Enable the device.
	bool CKeyboard::Enable(bool p_bEnable)
	{
		SAM_ASSERT(m_pDisplay != NULL, "Keyboard was not initialized");

		m_bEnabled = p_bEnable;
		return true;
	}

	// Retrieves if device is active.
	bool CKeyboard::IsEnable() const
	{
		return m_bEnabled;
	}

	// Exclusive mode.
	bool CKeyboard::SetExclusiveMode(bool p_bExclusive)
	{
		SAM_ASSERT(m_pDisplay != NULL, "Keyboard was not initialized");

		SAM_UNIMPLEMENTED;
		return true;
	}
}
