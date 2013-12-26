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
		-1, e_K_Joy_PadUp,
		-1, e_K_Joy_PadDown,
		-1, e_K_Joy_PadLeft,
		-1, e_K_Joy_PadRight,
		-1, e_K_Joy_Start,
		-1, e_K_Joy_Select,
		-1, e_K_Joy_L3,
		-1, e_K_Joy_R3,
		-1,	e_K_Joy_L1,
		-1,	e_K_Joy_R1,
		-1, e_K_Joy_1,
		-1, e_K_Joy_2,
		-1,	e_K_Joy_3,
		-1, e_K_Joy_4,
	};
#define JOYKEY_ARRAY_SIZE 28 ///< to do not compute it per frame.

	/// @brief Default constructor.
	CJoystick::CJoystick()
		: m_nFileDesc(-1), m_bEnabled(false), m_bConnected(false), m_fDeadZone(0.25f)
	{

	}

	/// @brief Destructor.
	CJoystick::~CJoystick()
	{
	}

	// Initialize the device.
	bool CJoystick::Init()
	{
		SAM_ASSERT(m_nFileDesc == -1, "Joystick was already initialized");

        // find available joystick.
        char sFilename[14];
        for(int32 nIndex = 0; nIndex < 4; ++nIndex)
        {
            sprintf(sFilename, "/dev/event/js%d", nIndex);
            m_nFileDesc = open(sFilename, O_RDONLY | O_NONBLOCK);
            if(m_nFileDesc > 0)
            {
                break;
            }
        }

        if(m_nFileDesc == -1)
        {
            SamLogError("Unable to find available joystick\n");
            return false;
        }

		// Enable the device.
		return Enable(true);
	}

	// Update the device.
	void CJoystick::Update(float p_fElapsedTime)
	{
		// setup event.
		SInputEvent oEvent;
		oEvent.m_eDevice = e_DT_Joystick;
		oEvent.m_iInternalID = m_nIndex;
		oEvent.m_nModifiers = 0;

        SAM_UNIMPLEMENTED;

		// update vibration.
		m_oVibrationEffect.Process(this, p_fElapsedTime);
		// TODO: implement vibration.
	}

	// Enable the device.
	bool CJoystick::Enable(bool p_bEnable)
	{
		m_bEnabled = p_bEnable;

		return true;
	}

	// Retrieves if device is active.
	bool CJoystick::IsEnable() const
	{
		return m_bEnabled;
	}

	// Set vibration effect.
	bool CJoystick::SetVibration(const SVibrationParams &p_oVibrationParams)
	{
		m_oVibrationEffect.SetParameters(p_oVibrationParams);
		return true;
	}
}
