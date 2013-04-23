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
#ifndef __SFLASH_EVENT__
#define __SFLASH_EVENT__

#include <SamConfig.h>

#if defined(ENABLE_FLASH)
namespace sam
{
    /// @enum Flash keycode
    enum EFlashKeycode
    {
        FK_Backspace = 8,
        FK_Tab,
        FK_Enter = 13,
        FK_Shift = 16,
        FK_Control,
        FK_Pause = 19,
        FK_Caps_Lock,
        FK_Escape = 27,
        FK_Spacebar = 32,
        FK_Page_Up,
        FK_Page_Down,
        FK_End,
        FK_Home,
        FK_Left,
        FK_Up,
        FK_Right,
        FK_Down,
        FK_Insert = 45,
        FK_Delete,

        FK_0 = 48,
        FK_1,
        FK_2,
        FK_3,
        FK_4,
        FK_5,
        FK_6,
        FK_7,
        FK_8,
        FK_9,

        FK_A = 65,
        FK_B,
        FK_C,
        FK_D,
        FK_E,
        FK_F,
        FK_G,
        FK_H,
        FK_I,
        FK_J,
        FK_K,
        FK_L,
        FK_M,
        FK_N,
        FK_O,
        FK_P,
        FK_Q,
        FK_R,
        FK_S,
        FK_T,
        FK_U,
        FK_V,
        FK_W,
        FK_X,
        FK_Y,
        FK_Z,   

        FK_NP_0 = 96,
        FK_NP_1,
        FK_NP_2,
        FK_NP_3,
        FK_NP_4,
        FK_NP_5,
        FK_NP_6,
        FK_NP_7,
        FK_NP_8,
        FK_NP_9,
        FK_NP_Multiply,
        FK_NP_Add,
        FK_NP_Enter,
        FK_NP_Substract,
        FK_NP_Decimal,
        FK_NP_Divide,

        FK_F1,
        FK_F2,
        FK_F3,
        FK_F4,
        FK_F5,
        FK_F6,
        FK_F7,
        FK_F8,
        FK_F9,
        FK_F10,
        FK_F11,
        FK_F12,
        FK_F13,
        FK_F14,
        FK_F15,

        FK_Num_Lock = 144,
        FK_Scroll_Lock,

        FK_Semicolon = 186,
        FK_Equal,
        FK_Comma,
        FK_Minus,
        FK_Period,
        FK_Slash,        
        FK_Bar,
        FK_LBracket,
        FK_Backslash,
        FK_RBracket,
        FK_Quote,

        FK_Num, ///< Number of key
    };

    /// @enum Flash key state
    enum EFlashKeyState
    {
        FKS_Down,
        FKS_Up,
    };

    /// @brief Flash keyboard event.
    struct SFlashKeyEvent
    {
        EFlashKeycode  keycode;
        EFlashKeyState keystate;

        /// @brief Default constructor.
        /// 
        /// @param _eKeycode Keycode.
        /// @param _eKeyState State of the key.
        SFlashKeyEvent(EFlashKeycode _eKeycode, EFlashKeyState _eKeyState)
            : keycode(_eKeycode), keystate(_eKeyState) {}        
    };

    /// @enum Flash mouse state.
    enum EFlashMouseState
    {
        FMS_Move,
        FMS_Pressed,
        FMS_Released,
        FMS_Wheel,
    };

    /// @brief Flash mouse event.
    struct SFlashMouseEvent
    {
        EFlashMouseState mousestate;
        int x; ///< Position on X-Axis.
        int y; ///< Position on Y-Axis.
        int wheel; ///< Wheel value.

        /// @brief Default constructor.
        /// 
        /// @param _eMouseState Mouse state.
        /// @param _iPosX Position on X-Axis.
        /// @param _iPosY Position on Y-Axis.
        SFlashMouseEvent(EFlashMouseState _eMouseState, int _iPosX, int _iPosY)
            : mousestate(_eMouseState), x(_iPosX), y(_iPosY) {}
    };

    /// @brief Retrieves flash key from input key.
    /// 
    /// @return flash key or FK_Num if not found.
    extern SAM_API EFlashKeycode toFlashKey(EKey _eKey);
}

#endif // ENABLE_FLASH

#endif // __SFLASH_EVENT__