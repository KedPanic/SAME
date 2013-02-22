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
#ifndef __EFLASH_PLAYER__
#define __EFLASH_PLAYER__

#include <SamConfig.h>
#include <renderer/SFlashEvent.h>

namespace sam
{
    /// @enum Flash argument type.
    enum EFlashArgumentType
    {
        FAT_Bool,
        FAT_Int,
        FAT_Float,
        FAT_String,
        FAT_Void,
    };

    /// @brief Flash argument.
    struct SFlashArgument : public IAllocated
    {
        /// @brief Value of the argument.
        union Value
        {
            bool  b;
            int   i;
            float f;
            const wchar_t *s;
        }value;

        EFlashArgumentType type; ///< Type of the argument.

        /// @brief null constructor.
        SFlashArgument()
            : type(FAT_Void) {}

        /// @brief boolean constructor.
        /// 
        /// @param _bValue Value of the argument.
        SFlashArgument(bool _bValue)
            : type(FAT_Bool)
        {
            value.b = _bValue;
        }

        /// @brief integer constructor.
        /// 
        /// @param _iValue Value of the argument.
        SFlashArgument(int _iValue)
            : type(FAT_Int)
        {
            value.i = _iValue;
        }

        /// @brief float constructor.
        /// 
        /// @param _fValue Value of the argument.
        SFlashArgument(float _fValue)
            : type(FAT_Float)
        {
            value.f = _fValue;
        }

        /// @brief string constructor.
        /// 
        /// @param _sValue Value of the argument.
        SFlashArgument(const wchar_t *_sValue)
            : type(FAT_String)
        {
            value.s = _sValue;
        }
    };

    /// @brief Interface for fscommand listener.
    struct IFSCommandListener
    {
        /// @brief Callback when fscommand is called in action script.
        /// 
        /// @param _sCommand Name of the command.
        /// @param _sArgs Arguments.
        virtual void OnFSCommand(const UString &_sCommand, const UString &_sArgs) = 0;
    };

    /// @brief Interface for ExternalInterface listener.
    struct IExternalInterfaceListener
    {
        /// @brief Callback when ExternalInterface.call is called in action script.
        /// 
        /// @param _sFunction Name of the function.
        /// @param _pArgs List of arguments.
        /// @param _iNbArgs Number of arguments.
        virtual void OnExternalInterface(const UString &_sFunction, SFlashArgument *_pArgs, int _inbArgs) = 0;
    };

    /// @enum Scale mode.
    enum EFlashScale
    {
        FS_SHOW_ALL,
        FS_NO_BORDER,
        FS_EXACT_FIT,
        FS_NO_SCALE,
    };

    /// @enum Rendering quality.
    enum EFlashQuality
    {
        FQ_LOW,
        FQ_MEDIUM,
        FQ_HIGH,
        FQ_BEST,
        FQ_AUTO_LOW,
        FQ_AUTO_HIGH,
    };

    /// @enum Alignment.
    enum EFlashAlignment
    {
        FA_CENTER = 0,
        FA_LEFT   = 1,
        FA_TOP    = 2,
        FA_RIGHT  = 4,
        FA_BOTTOM = 8,
    };
}

#endif // __EFLASH_PLAYER__
