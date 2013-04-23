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
#include "SamRendererPCH.h"

#if defined(ENABLE_FLASH)
namespace sam
{
    const EFlashKeycode FK_UNKNOWN = FK_Num;

    EFlashKeycode s_InputKey2FlashKey[K_Keyboard_End] = 
    {
        FK_Escape, // K_Escape,
        FK_F1,     // K_F1,
        FK_F2,     // K_F2,
        FK_F3,     // K_F3,
        FK_F4,     // K_F4,
        FK_F5,     // K_F5,
        FK_F6,     // K_F6,
        FK_F7,     // K_F7,
        FK_F8,     // K_F8,
        FK_F9,     // K_F9,
        FK_F10,    // K_F10,
        FK_F11,    // K_F11,
        FK_F12,    // K_F12,        
        FK_1,      // K_1,
        FK_2,      // K_2,
        FK_3,      // K_3,
        FK_4,      // K_4,
        FK_5,      // K_5,
        FK_6,      // K_6,
        FK_7,      // K_7,
        FK_8,      // K_8,
        FK_9,      // K_9,
        FK_0,      // K_0,              
        FK_Minus,  // K_Minus,    // -
        FK_Equal,  // K_Equals,   // =
        FK_Backspace, // K_Backspace,
        FK_Tab,    // K_Tab,
        FK_Q,
        FK_W,
        FK_E,
        FK_R,
        FK_T,
        FK_Y,
        FK_U,
        FK_I,
        FK_O,
        FK_P,
        FK_LBracket, // [
        FK_RBracket, // ]
        FK_Enter,
        FK_Caps_Lock,
        FK_A,
        FK_S,
        FK_D,
        FK_F,
        FK_G,
        FK_H,
        FK_J,
        FK_K,
        FK_L,
        FK_Semicolon, // ;
        FK_UNKNOWN, // FK_Apostrophe,// '
        FK_UNKNOWN, // K_Tilde,     // ~
        FK_Backslash,
        FK_UNKNOWN, // K_LShift,
        FK_Z,
        FK_X,
        FK_C,
        FK_V,
        FK_B,
        FK_N,
        FK_M,
        FK_Comma,     // ,
        FK_Period,    // .
        FK_Slash,     // /
        FK_UNKNOWN, // K_RShift,
        FK_UNKNOWN, // K_LCtrl,
        FK_UNKNOWN, // K_LWin,
        FK_UNKNOWN, // K_LAlt,
        FK_Spacebar,
        FK_UNKNOWN, // K_RAlt,
        FK_UNKNOWN, // K_RWin,
        FK_UNKNOWN, // K_RCtrl,
        FK_UNKNOWN, // K_Print,
        FK_Scroll_Lock,
        FK_Pause,
        FK_Insert,
        FK_Home,
        FK_Page_Up,
        FK_Delete,
        FK_End,
        FK_Page_Down,
        FK_Up,
        FK_Left,
        FK_Down,
        FK_Right,
        FK_Num_Lock,
        FK_NP_Divide,
        FK_NP_Multiply,
        FK_NP_Substract,
        FK_NP_7,
        FK_NP_8,
        FK_NP_9,
        FK_NP_Add,
        FK_NP_4,
        FK_NP_5,
        FK_NP_6,
        FK_NP_1,
        FK_NP_2,
        FK_NP_3,
        FK_NP_Enter,
        FK_NP_0,
        FK_UNKNOWN, // FK_NP_Delete,            
    };

    /// @brief Retrieves flash key from input key.
    /// 
    /// @return flash key or FK_Num if not found.
    EFlashKeycode toFlashKey(EKey _eKey)
    {
        SamAssert(_eKey < K_Keyboard_End, "_eKey is equal or higher than K_Keyboard_End");
        return s_InputKey2FlashKey[_eKey];
    }
}

#endif // ENABLE_FLASH