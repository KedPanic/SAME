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
#ifndef __SVIBRATION_EFFECT__
#define __SVIBRATION_EFFECT__

namespace sam
{
	/// @enum Motor ID.
	enum EVibrationMotorID
	{
		e_VM_Motor_0 = 1 << 0,
		e_VM_Motor_1 = 1 << 1,

		e_VM_All     =  e_VM_Motor_0 | e_VM_Motor_1
	};


	/// @brief Vibration effect system.
	struct SVibrationEffect
	{
		int m_nMotor;		///< ID of the motor to apply the vibration effect
		float m_fDuration;	///< Total duration (millisecond)
		float m_fLevel;		///< Level of vibration (0.0f - 1.0f)		

		//=======================================//
		// Variable used by the callback effect. //
		//=======================================//		
		float m_fDelay;
		int   m_nRepeat;
		float m_fFadeIn;
		float m_fFadeOut;

		typedef float (*VibrationFX)(SVibrationEffect *_pFX, float _fDeltaTime);
		VibrationFX m_pfCallback; ///< Callback used to process the vibration effect.

		/// @brief Retrieves current level.
		/// 
		/// @return Current vibration level.
		INLINE float GetCurrentLevel() {return m_fCurrentLevel;}

		/// @brief Retrieves current time.
		/// 
		/// @return Current time.
		INLINE float GetCurrentTime() {return m_fCurrentTime;}

		/// @brief Default constructor.
		SVibrationEffect();

		/// @brief Set parameters.
		/// 
		/// @param _oParams List of parameters.
		void SetParameters(const SVibrationParams &_oParams);

		/// @brief Update the vibration effect.
		/// 
		/// @param _pDevice Device to apply the effect.
		/// @param _fDeltaTime Elapsed time since the last frame.
		void Process(IInputDevice *_pDevice, float _fDeltaTime);

	private:
		float m_fCurrentLevel;	///< Current vibration level
		float m_fCurrentTime;	///< Current time (millisecond)
	};	
}

#endif // __SVIBRATION_EFFECT__
