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
    // Initialize.
    bool CInputManager::InitializeInputDriver()
    {
		SAM_ASSERT(m_pInputDriver == NULL, "Input manager is already initialized.")

		m_pInputDriver = SAM_ALLOC(SInputDriver);

		// Create input system
        HRESULT nResult = DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInputDriver->m_pDirectInput, NULL);
		if(FAILED(nResult))
		{
			SamLogError("Unable to create directx 8 input system, error code: %d\n", nResult);
			return false;
		}

        return true;
    }

    // Shutdown.
    void CInputManager::ShutdownInputDriver()
    {
		SAM_ASSERT(m_pInputDriver->m_pDirectInput != NULL, "direct input was not initialized");

		// Close the input system.
		m_pInputDriver->m_pDirectInput->Release();
		m_pInputDriver->m_pDirectInput = NULL;

		SAM_FREE(m_pInputDriver);
		m_pInputDriver = NULL;
    }
}
