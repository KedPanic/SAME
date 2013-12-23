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
#ifndef __CJOYSTICK_PLF__
#define __CJOYSTICK_PLF__

#include <input/IInputDevice.h>

namespace sam
{
	/// @brief Joystick device.
	class SAM_INPUT_API CJoystick : public IInputDevice
	{
	public:
		/// @brief Default constructor.
		CJoystick();

		/// @brief Destructor.
		~CJoystick();

		/// @brief Retrieves type of device.
		/// 
		/// @return Device type.
		EDeviceType GetType() const {return e_DT_Joystick;}

		/// @brief Retrieves device name.
		/// 
		/// @return Device name.
		const char *GetName() const {return "XInput";}

		/// @brief Initialize the device.
		/// 
		/// @return true if no error occurred.
		bool Init();

		/// @brief Update the device.
		///
		/// @param _fElapsedTime Elapsed time since the last frame.
		void Update(float _fElapsedTime);

		/// @brief Enable the device.
		/// 
		/// @param _bEnable True to enable the device.
		/// 
		/// @return True if no error occurred.
		bool Enable(bool _bEnable);

		/// @brief Retrieves if device is active.
		///
		/// @return True if device is active.
		bool IsEnable() const;

		/// @brief Set vibration effect.
		/// 
		/// @param _oVibrationParams Vibration effect parameters.
		bool SetVibration(const SVibrationParams &_oVibrationParams);

		//======================================================//
		//					JOYSTICK SPECIFIC					//
		//======================================================//
		
		/// @brief Set dead zone for stick.
		/// 
		/// @param _fDeadZone Dead zone value: 0.0-1.0
		INLINE void SetDeadZone(float _fDeadZone);

	private:
		static int m_nCurrentIndex; ///< Device counter (max 4).

		int	m_nUserIndex;		///< ID of the device.
		XINPUT_STATE m_oState;	///< XInput state.
		bool m_bEnabled;		///< True if device is enabled.
		bool m_bConnected;		///< True if device is connected.
		float m_fDeadZone;		///< Dead zone for stick.

		SVibrationEffect m_oVibrationEffect; ///< Vibration effect system.
		XINPUT_VIBRATION m_oVibration;	///< Level of vibration.

		/// @brief Prepare stick event.
		/// 
		/// @param _fThumbX Value of the x-axis.
		/// @param _fThumbY Value of the y-axis.
		/// @param _fNormalizedThumbX Normalized x-axis (-1.0 1.0)
		/// @param _fNormalizedThumbY Normalized y-axis (-1.0 1.0)
		/// 
		/// @return true if event can be sended
		INLINE bool PrepareStickEvent(float _fThumbX, float _fThumbY, float &_fNormalizedThumbX, float &_fNormalizedThumbY);

		/// @brief Send input event.
		/// 
		/// @param _oEvent Event to send.
		INLINE void SendEvent(SInputEvent &_oEvent);
	};

#include <input/CJoystickPlf.inl>
}

#endif // __CJOYSTICK_PLF__
