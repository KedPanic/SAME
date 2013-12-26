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
#ifndef __CMOUSE_PLF__
#define __CMOUSE_PLF__

#include <input/IInputDevice.h>

namespace sam
{
	/// @brief Mouse device.
	class SAM_INPUT_API CMouse : public IInputDevice
	{
	public:
		/// @brief Default constructor.
		CMouse();

		/// @brief Destructor.
		~CMouse();

		/// @brief Retrieves type of device.
		///
		/// @return Device type.
		EDeviceType GetType() const {return e_DT_Mouse;}

		/// @brief Retrieves device name.
		///
		/// @return Device name.
		const char *GetName() const {return "Mouse DX8";}

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
		bool SetVibration(const SVibrationParams &) {return true;}

		/// @brief Exclusive mode.
		///
		/// @param _bExclusive True to active exclusive mode.
		///
		/// @return True if no error occurred.
		bool SetExclusiveMode(bool _bExclusive);

	private:
		Display *m_pDisplay;		///< X11 display client.
		bool m_bEnabled;			///< True if device is enabled.
	};
}

#endif // __CMOUSE_PLF__
