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
#ifndef __EINPUT__
#define __EINPUT__

namespace sam
{
	/// @enum Define the type of device
	enum EDeviceType
	{
        e_DT_Unknown,
		e_DT_Keyboard,
		e_DT_Mouse,
		e_DT_Joystick,
	};

    /// @enum Define modifier mask
    enum EModifierMask
    {
        e_MM_None       = 0,
        e_MM_LShift     = 1 << 0,
        e_MM_LCtrl      = 1 << 1,
        e_MM_LAlt       = 1 << 2,
        e_MM_LWin       = 1 << 3,
        e_MM_RShift     = 1 << 4,
        e_MM_RCtrl      = 1 << 5,
        e_MM_RAlt       = 1 << 6,
        e_MM_RWin       = 1 << 7,
        e_MM_CapsLock   = 1 << 8,
        e_MM_NumLock    = 1 << 9,
        e_MM_ScrollLock = 1 << 10,

        e_MM_Shift      = e_MM_LShift | e_MM_RShift,
        e_MM_Ctrl       = e_MM_LCtrl  | e_MM_RCtrl,
        e_MM_Alt        = e_MM_LAlt   | e_MM_RAlt,
        e_MM_Win        = e_MM_LWin   | e_MM_RWin,
    };

    /// @enum Type of event.
    enum EInputState
    {
        e_IS_Unknown  = 0,
        e_IS_Pressed  = 1 << 0,
        e_IS_Released = 1 << 1,
        e_IS_Down     = 1 << 2,
        e_IS_Changed  = 1 << 3    ///< used when input value has changed.
    };

	/// @enum Define the id of key
	enum EKey
	{
		// Keyboard
		e_K_Escape,
		e_K_F1,
		e_K_F2,
		e_K_F3,
		e_K_F4,
		e_K_F5,
		e_K_F6,
		e_K_F7,
		e_K_F8,
		e_K_F9,
		e_K_F10,
		e_K_F11,
		e_K_F12,
        e_K_0,
		e_K_1,
		e_K_2,
		e_K_3,
		e_K_4,
		e_K_5,
		e_K_6,
		e_K_7,
		e_K_8,
		e_K_9,		
		e_K_Minus,    // -
		e_K_Equals,   // =
		e_K_Backspace,
		e_K_Tab,
		e_K_Q,
		e_K_W,
		e_K_E,
		e_K_R,
		e_K_T,
		e_K_Y,
		e_K_U,
		e_K_I,
		e_K_O,
		e_K_P,
		e_K_LBracket, // [
		e_K_RBracket, // ]
		e_K_Enter,
		e_K_CapsLock,
		e_K_A,
		e_K_S,
		e_K_D,
		e_K_F,
		e_K_G,
		e_K_H,
		e_K_J,
		e_K_K,
		e_K_L,
		e_K_SemiColon, // ;
		e_K_Apostrophe,// '
        e_K_Tilde,     // ~
		e_K_Backslash,
		e_K_LShift,
		e_K_Z,
		e_K_X,
		e_K_C,
		e_K_V,
		e_K_B,
		e_K_N,
		e_K_M,
		e_K_Comma,     // ,
		e_K_Period,    // .
		e_K_Slash,     // /
		e_K_RShift,
		e_K_LCtrl,
		e_K_LWin,
		e_K_LAlt,
		e_K_Space,
		e_K_RAlt,
		e_K_RWin,
		e_K_RCtrl,
		e_K_Print,
		e_K_ScrollLock,
		e_K_Pause,
		e_K_Insert,
		e_K_Home,
		e_K_PageUp,
		e_K_Delete,
		e_K_End,
        e_K_PageDown,
		e_K_Up,
		e_K_Left,
		e_K_Down,
		e_K_Right,
		e_K_NumLock,
		e_K_NP_Divide,
		e_K_NP_Multiply,
		e_K_NP_Substract,
        e_K_NP_Add,
        e_K_NP_0,
        e_K_NP_1,
        e_K_NP_2,
        e_K_NP_3,
        e_K_NP_4,
        e_K_NP_5,
        e_K_NP_6,
		e_K_NP_7,
		e_K_NP_8,
		e_K_NP_9,			
		e_K_NP_Enter,		
		e_K_NP_Delete,
		e_K_Keyboard_End,

		// Mouse
		e_K_Mouse_1 = e_K_Keyboard_End,
		e_K_Mouse_2,
		e_K_Mouse_3,
		e_K_Mouse_4,
		e_K_Mouse_5,
		e_K_Mouse_WheelUp,
		e_K_Mouse_WheelDown,
		e_K_Mouse_X,
		e_K_Mouse_Y,
		e_K_Mouse_End,

		// Joystick
		e_K_Joy_1 = e_K_Mouse_End,
		e_K_Joy_2,
		e_K_Joy_3,
		e_K_Joy_4,
		e_K_Joy_L1,
		e_K_Joy_R1,		
		e_K_Joy_L2,
		e_K_Joy_R2,
		e_K_Joy_L3,
		e_K_Joy_R3,
		e_K_Joy_Select,
		e_K_Joy_Start,
		e_K_Joy_PadUp,
		e_K_Joy_PadLeft,
		e_K_Joy_PadDown,
		e_K_Joy_PadRight,
		e_K_Joy_LStickX,
		e_K_Joy_LStickY,	
		e_K_Joy_RStickX,
		e_K_Joy_RStickY,
		e_K_Joy_End,

		// Global events.
		e_K_Connected,
		e_K_Disconnected,
		e_K_Nb = e_K_Disconnected,

        e_K_Unknown = 0xFFFFFFFFU,
	};

	
	//============================================================//
	//				  		  READABLE INPUT					  //
	//============================================================//

	// Array of key name
	const String g_aKeyName[e_K_Nb] =
	{
		"escape",
		"f1",
		"f2",
		"f3",
		"f4",
		"f5",
		"f6",
		"f7",
		"f8",
		"f9",
		"f10",
		"f11",
		"f12",
        "0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",		
		"minus",
		"equals",
		"backspace",
		"tab",
		"q",
		"w",
		"e",
		"r",
		"t",
		"y",
		"u",
		"i",
		"o",
		"p",
		"[",
		"]",
		"enter",
		"capslock",
		"a",
		"s",
		"d",
		"f",
		"g",
		"h",
		"j",
		"k",
		"l",
		";",
		"'", 
        "~",
		"\"",
		"lshift",
		"z",
		"x",
		"c",
		"v",
		"b",
		"n",
		"m",
		",",
		".",
		"/",
		"rshift",
		"lctrl",
		"lwin",
		"lalt",
		"space",
		"ralt",
		"rwin",
		"rctrl",
		"print",
		"scrolllock",
		"pause",
		"insert",
		"home",
		"pageup",
		"delete",
		"end",
		"pagedown",
		"up",
		"left",
		"down",
		"right",
		"numlock",
		"np_divide",
		"np_multiply",
		"np_substract",
		"np_add",
        "np_0",		
		"np_1",
		"np_2",
		"np_3",
        "np_4",
        "np_5",
        "np_6",
        "np_7",
        "np_8",
        "np_9",
		"np_enter",		
		"np_delete",

		// Mouse
		"m_button1",
		"m_button2",
		"m_button3",
		"m_button4",
		"m_button5",
		"m_wheel_up",
		"m_wheel_down",
		"m_axis_x",
		"m_axis_y",

		// Joystick
		"j_button1",
		"j_button2",
		"j_button3",
		"j_button4",
		"j_l1",
		"j_r1",
		"j_l2",
		"j_r2",
		"j_l3",
		"j_r3",
		"j_select",
		"j_start",
		"j_up",
		"j_left",
		"j_down",
		"j_right",
		"j_laxis_x",
		"j_laxis_y",
		"j_raxis_x",
		"j_raxis_y",

		// Global events.
		"connected",
		"disconnected"
	};

	// Helper method to get key from string
	inline EKey GetKeyFromString(const String &_sKey)
	{
		int iStart = 0, iEnd = e_K_Keyboard_End;

		if(_sKey.size() > 2)
		{
			// check if its mouse
			if(_sKey[0] == 'm' && _sKey[1] == '_')
			{
				iStart = e_K_Mouse_1;
				iEnd   = e_K_Mouse_End;
			}
			// check if its joypad
			else if(_sKey[0] == 'j' && _sKey[1] == '_')
			{
				iStart = e_K_Joy_1;
				iEnd   = e_K_Joy_End;
			}
		}

		// get key from string
		for(int i = iStart; i < iEnd; i++)
		{
			if(_sKey.compare(g_aKeyName[i]) == 0)
				return static_cast<EKey>(i);
		}

		return e_K_Nb;
	}

    /// @brief Define an input event.
    struct SInputEvent
    {
        EDeviceType m_eDevice;          ///< Device ID.
        int         m_iInternalID;      ///< Internal device ID.
        EInputState m_eState;           ///< Type of input event.
        EKey        m_eKey;             ///< Key corresponding of the event.
        int         m_iModifiers;       ///< Flag of key modifier.
        String      m_sKeyName;         ///< Name of the key in human readable.
        float       m_fValue;           ///< Value associated with the input event.

        /// @brief Default constructor.
        SInputEvent()
            : m_eDevice(e_DT_Unknown), m_iInternalID(0), m_eState(e_IS_Unknown), m_eKey(e_K_Unknown), m_iModifiers(0), m_sKeyName(""), m_fValue(0.0f)
        {}
    };

    /// Helper MACRO
    inline short GetMouseX(int _iValue)
    {
        return _iValue >> 16;
    }

    inline short GetMouseY(int _iValue)
    {
        return _iValue & 0x0000FFFF;
    }

    /// @brief Interface for input listener.
    class IInputListener
    {
    public:
        /// @brief Called every time when an input event occurred.
        /// 
        /// @param _Event Input event.
        /// @return true if other input listener should not received this event.
        virtual bool OnInputEvent(SInputEvent &_Event) = 0;
    };
}

#endif // __EINPUT__
