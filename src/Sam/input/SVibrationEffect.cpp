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
#include <input/SamPCH.h>
#include <input/SVibrationEffect.h>

#include <input/IInputDevice.h>

namespace sam
{
	namespace fx
	{
		/// @brief Just apply level vibration.
		float Basic(SVibrationEffect *_pFX, float _fDeltaTime)
		{
			return _pFX->m_fLevel;
		}

		/// @brief Apply fx with fade in and out effect.
		float Fade(SVibrationEffect *_pFX, float _fDeltaTime)
		{
			float fCurrentTime = _pFX->GetCurrentTime();

			// apply fade in
			if(_pFX->m_fFadeIn - fCurrentTime > 0.0f)
			{				
				return (fCurrentTime / _pFX->m_fFadeIn) * _pFX->m_fLevel;
			}
			// apply fade out
			else if(_pFX->m_fFadeOut >= (_pFX->m_fDuration - fCurrentTime))
			{
				return ((_pFX->m_fDuration - fCurrentTime) / _pFX->m_fFadeOut) * _pFX->m_fLevel;
			}

			return _pFX->m_fLevel;
		}

		// Array of vibration effect.
		SVibrationEffect::VibrationFX g_aVibrationEffect[e_VET_Custom] =
		{
			&Basic,
			&Fade
		};
	}

	/// @brief Default constructor.
	SVibrationEffect::SVibrationEffect() 
		: m_nMotor(e_VM_All), m_fDuration(1000.0f), m_fLevel(1.0f), m_pfCallback(NULL), m_fDelay(0.0f), 
		m_nRepeat(0), m_fFadeIn(0.0f), m_fFadeOut(0.0f), m_fCurrentLevel(0.0f), 
		m_fCurrentTime(0.0f) 
	{

	}

	/// @brief Set parameters.
	/// 
	/// @param _oParams List of parameters.
	void SVibrationEffect::SetParameters(const SVibrationParams &_oParams)
	{
		// setup
		m_nMotor = _oParams.m_nMotor;
		m_fDuration = _oParams.m_fDuration;
		m_fLevel = _oParams.m_fLevel;
		m_fDelay = _oParams.m_fDelay;
		m_nRepeat = _oParams.m_nRepeat;
		m_fFadeIn = _oParams.m_fFadeIn;
		m_fFadeOut = _oParams.m_fFadeOut;

		m_pfCallback = fx::g_aVibrationEffect[_oParams.m_eType];

		// reset
		m_fCurrentTime = 0.0f;
		m_fCurrentLevel = 0.0f;
	}

	/// @brief Update the vibration effect.
	/// 
	/// @param _pDevice Device to apply the effect.
	/// @param _fDeltaTime Elapsed time since the last frame.
	void SVibrationEffect::Process(IInputDevice *_pDevice, float _fDeltaTime)
	{			
		if(m_pfCallback)
		{
			m_fCurrentTime += _fDeltaTime;
			if(m_fCurrentTime < m_fDuration)
			{
				SAM_ASSERT(m_pfCallback != NULL, "Vibration effect callback is null");

				m_fCurrentLevel = m_pfCallback(this, _fDeltaTime);
				return;
			}

			// end of vibration effect.
			m_fCurrentLevel = 0.0f;
			m_pfCallback = NULL;
		}		
	}
}
