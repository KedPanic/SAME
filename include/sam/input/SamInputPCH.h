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
#ifndef __SAM_INPUT_PCH__
#define __SAM_INPUT_PCH__

/* sam engine */
#include <SamCommon.h>
#include <input/EInput.h>

#if defined( SAM_PLATFORM_LINUX )
#   include <X11/Xutil.h>
#elif defined( SAM_PLATFORM_WIN )
#	include <dinput.h>
#	include <Xinput.h>
#else
#   error "unsupported platform"
#endif

// sam engine input subsystem macro export
#ifdef SAM_INPUT_EXPORTS
#   define SAM_INPUT_API LIBRARY_EXPORT
#else
#   define SAM_INPUT_API LIBRARY_IMPORT
#endif

#include <input/SVibrationParams.h>

namespace sam
{
	class IInputDevice;
	class CInputManager;

	/// @brief Create input manager.
	///
	/// @param _pEnv Global environment variable.
	/// @param _pWinHandle Window handler.
	///
	/// @return Created input manager.
	extern SAM_INPUT_API CInputManager *CreateInputManager(Env *_pEnv, SAM_HWND _pWinHandle);

	/// @brief Destroy input manager.
	extern SAM_INPUT_API void DestroyInputManager();
}

#endif // __SAM_INPUT_PCH__
