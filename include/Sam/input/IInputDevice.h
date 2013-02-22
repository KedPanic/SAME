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
#ifndef __IINPUT_DEVICE__
#define __IINPUT_DEVICE__

namespace sam
{
	/// @brief Interface for a physical input device.
	class IInputDevice : public IAllocated, public tpl::TList<IInputDevice>
	{
		friend class CInputManager;

	public:
		IInputDevice() : m_nIndex(-1) {}
		virtual ~IInputDevice() {}

		/// @brief Retrieves type of device.
		/// 
		/// @return Device type.
		virtual EDeviceType GetType() const = 0;

		/// @brief Retrieves device name.
		/// 
		/// @return Device name.
		virtual const char *GetName() const = 0;

		/// @brief Retrieve device index.
		/// 
		/// @return Device index.
		int GetIndex() const {return m_nIndex;}

		/// @brief Initialize the device.
		/// 
		/// @return true if no error occurred.
		virtual bool Init() = 0;

		/// @brief Update the device.
		/// 
		/// @param _fElapsedTime Elapsed time since the last frame.
		virtual void Update(float _fElapsedTime) = 0;

		/// @brief Enable the device.
		/// 
		/// @param _bEnable True to enable the device.
		/// 
		/// @return True if no error occurred.
		virtual bool Enable(bool _bEnable) = 0;

		/// @brief Retrieves if device is active.
		///
		/// @return True if device is active.
		virtual bool IsEnable() const = 0;

		/// @brief Set vibration effect.
		/// 
		/// @param _oVibrationParams Vibration effect parameters.
		virtual bool SetVibration(const SVibrationParams &_oVibrationParams) = 0;

	protected:
		int m_nIndex; ///< Device index.

		/// @brief Set device index.
		/// 
		/// @param _nIndex Device index.
		void SetIndex(int _nIndex)
		{
			SAM_ASSERT(m_nIndex == -1, "Device index was already initialized");

			m_nIndex = _nIndex;
		}
	};
}

#endif // __IINPUT_DEVICE__
