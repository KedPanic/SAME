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
#ifndef __SVIBRATION_PARAMS__
#define __SVIBRATION_PARAMS__

namespace sam
{
	/// @enum Type of vibration effect.
	enum EVibrationEffectType
	{
		e_VET_Basic,
		e_VET_Fade,
		e_VET_Custom, ///< Effect specified by user.
	};

	/// @brief Parameter for vibration effect.
	/// @see sam::SVibrationEffect
	struct SVibrationParams
	{			
		int m_nMotor;					///< ID of the motor to apply the vibration effect
		float m_fDuration;				///< Total duration (millisecond)
		float m_fLevel;					///< Level of vibration (0.0f - 1.0f)		
		float m_fDelay;
		int   m_nRepeat;
		float m_fFadeIn;
		float m_fFadeOut;

		EVibrationEffectType m_eType;	///< Type of effect.
	};	
}

#endif
