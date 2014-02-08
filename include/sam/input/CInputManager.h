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
#ifndef __CINPUT_MANAGER__
#define __CINPUT_MANAGER__

#include <input/SInputDriverPlf.h>

namespace sam
{
	/// @brief Input manager to manage device.
	class SAM_INPUT_API CInputManager : public IAllocated
	{
	public:
		/// @brief Constructor.
		CInputManager();

		/// @brief Destructor.
		~CInputManager();

		/// @brief Initialize.
		///
		/// @param p_pWinHandler Window handler to receive input event.
		///
		/// @return True if no error occurred.
		bool Initialize(SAM_HWND p_pWinHandler);

		/// @brief Update input device.
		///
		/// @param p_fElapsedTime Elapsed time since the last frame.
		void Update(float p_fElapsedTime);

		/// @brief Shutdown.
		void Shutdown();

		/// @brief Add a new input device.
		///
		/// @param p_pDevice Device to add.
		///
		/// @return True if no error occurred.
		bool AddDevice(IInputDevice *p_pDevice);

		/// @brief Add a new listener.
		///
		/// @param p_pListener New listener to add.
		void AddInputListener(IInputListener *p_pListener);

		/// @brief Remove an old listener.
		///
		/// @param p_pListener Old listener to remove.
		void RemoveInputListener(IInputListener *p_pListener);

		/// @brief Update modifiers.
		///
		/// @param p_eKey Key id.
		/// @param p_bPressed True if key is pressed.
		void UpdateModifiers(EKey p_eKey, bool p_bPressed);

		/// @brief Retrieves current pressed input modifiers.
		///
		/// @return Return current pressed input modifiers.
		int32 GetModifiers() const;

		/// @brief Query if the specified type of device is connected.
		///
		/// @param p_eDevice Type of device.
		///
		/// @return true if the specified type of device is connected.
		bool HasInputDeviceOfType(EDeviceType p_eDevice);

		/// @brief Retrieves input driver (platform specific).
		///
		/// @return Input driver.
		SInputDriver *GetInputDriver() const {return m_pInputDriver;}

		/// @brief Retrieves window handler.
		///
		/// @return Window handler.
		SAM_HWND GetHWND() const {return m_pWinHandle;}

		/// @brief Send event to all input listeners.
		///
		/// @param p_Event Event to send.
		void FireInputEvent(SInputEvent &p_Event);

		/// @brief Set vibration effect of the specified device.
		///
		/// @param p_nDeviceID Internal device id.
		/// @param p_oVibrationParams Vibration effect parameters.
		void SetVibration(int32 p_nDeviceID, const SVibrationParams &p_oVibrationParams);

	private:
		SAM_HWND m_pWinHandle;
		SInputDriver *m_pInputDriver;
		IInputDevice *m_pFirstDevice;
		int32 m_nCurrentIndex;  ///< Incremental index to set internal device ID.

		int32 m_nModifiers;     ///< Current pressed input modifiers.

		typedef std::set<IInputListener*> InputListeners;
		InputListeners m_aInputListeners; ///< Array of input listeners.

		/// @brief Retrieves device by index.
		///
		/// @param p_nIndex Internal device ID.
		///
		/// @return null or pointer to the device.
		IInputDevice *GetDevice(int32 p_nIndex);

        ////////////////////////////////////////////////////////
        //                  PLATFORM SPECIFIC                 //
        ////////////////////////////////////////////////////////
        /// @brief Initialize the input driver.
        ///
        /// @return True if no error occurred.
        bool InitializeInputDriver();

        /// @brief Shutdown the input driver.
        void ShutdownInputDriver();
	};
}

#endif // __CINPUT_MANAGER__
