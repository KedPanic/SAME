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
#include <input/CInputManager.h>

#define MOUSE_BUFFERSIZE 64

namespace sam
{
    EKey g_aMouseButton[] = {
        e_K_Mouse_1, // Button1
        e_K_Mouse_2, // Button2
        e_K_Mouse_3, // Button3
        e_K_Mouse_4, // Button4
        e_K_Mouse_5, // Button5
    };

	// Default constructor.
	CMouse::CMouse()
		: m_pDisplay(NULL), m_bEnabled(false)
	{
	}

	// Destructor.
	CMouse::~CMouse()
	{
		SAM_ASSERT(m_pDisplay == NULL, "Should be destroyed in shutdown");
    }

	// Initialize the device.
	bool CMouse::Init()
	{
		SAM_ASSERT(m_pDisplay == NULL, "Mouse is already initialized");

        // open X connection.
        m_pDisplay = XOpenDisplay(NULL);
		if(!m_pDisplay)
		{
            SamLogError("Unable to create mouse device, unable to connect to X\n");
            return false;
		}

		// listen keyboard events.
		SAM_HWND oWindow = g_Env->pInputManager->GetHWND();
		int nResult = XSelectInput(m_pDisplay, oWindow, ButtonPressMask | ButtonReleaseMask | PointerMotionMask);
		if(nResult != Success)
		{
			SamLogError("Unable to create mouse device, X error code: %d\n", nResult);
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
	void CMouse::Update(float p_fElapsedTime)
	{
		XEvent oXEvent;
        SInputEvent oEvent;

        while(XPending(m_pDisplay) > 0)
        {
            XNextEvent(m_pDisplay, &oXEvent);

            if(oXEvent.type == MotionNotify)
            {
                oEvent.m_eState = e_IS_Changed;
                oEvent.m_fValue = oXEvent.xmotion.x << 16 | oXEvent.xmotion.y;
            }
            else
            {
                oEvent.m_eKey = g_aMouseButton[oXEvent.xbutton.button - 1];
                oEvent.m_eState = oXEvent.type == ButtonPress?e_IS_Pressed:e_IS_Released;
            }

			oEvent.m_iInternalID = 0;
			oEvent.m_nModifiers = 0;
			oEvent.m_sKeyName = g_aKeyName[oEvent.m_eKey];

			// send input event.
			g_Env->pInputManager->FireInputEvent(oEvent);
		}
	}

	// Enable the device.
	bool CMouse::Enable(bool p_bEnable)
	{
		SAM_ASSERT(m_pDisplay != NULL, "Mouse was not initialized");

		m_bEnabled = p_bEnable;
		return true;
	}

	// Retrieves if device is active.
	bool CMouse::IsEnable() const
	{
		return m_bEnabled;
	}

	// Exclusive mode.
	bool CMouse::SetExclusiveMode(bool p_bExclusive)
	{
		SAM_ASSERT(m_pDisplay!= NULL, "Mouse was not initialized");

		SAM_UNIMPLEMENTED;
		return true;
	}
}
