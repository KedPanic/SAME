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
#ifndef __CINPUT_MANAGER_PLF__
#define __CINPUT_MANAGER_PLF__

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
		/// @param _pWinHandler Window handler to receive input event.
		/// @return True if no error occurred.
		bool Initialize(SAM_HWND _pWinHandler);

		/// @brief Update input device.
		/// 
		/// @param _fElapsedTime Elapsed time since the last frame.
		void Update(float _fElapsedTime);

		/// @brief Shutdown.
		void Shutdown();

		/// @brief Add a new input device.
		/// 
		/// @return True if no error occurred.
		bool AddDevice(IInputDevice *_pDevice);

		/// @brief Add a new listener.
		/// 
		/// @param _pListener New listener to add.
		void AddInputListener(IInputListener *_pListener);

		/// @brief Remove an old listener.
		/// 
		/// @param _pListener Old listener to remove.
		void RemoveInputListener(IInputListener *_pListener);

		/// @brief Update modifiers.
		/// 
		/// @param _eKey Key id.
		/// @param _bPressed True if key is pressed.
		void UpdateModifiers(EKey _eKey, bool _bPressed);

		/// @brief Retrieves current pressed input modifiers.
		/// 
		/// @return Return current pressed input modifiers.
		int GetModifiers() const;

		/// @brief Query if the specified type of device is connected.
		/// 
		/// @param _eDevice Type of device.
		/// @return true if the specified type of device is connected.
		bool HasInputDeviceOfType(EDeviceType _eDevice);

		/// @brief Retrieves directx input system.
		/// 
		/// @return DirectX input system.
		LPDIRECTINPUT8 GetInputSystem() const {return m_pDirectInput;}

		/// @brief Retrieves window handler.
		/// 
		/// @return Window handler.
		SAM_HWND GetHWND() const {return m_pWinHandle;}

		/// @brief Send event to all input listeners.
		/// 
		/// @param _Event Event to send.
		void FireInputEvent(SInputEvent &_Event);

		/// @brief Set vibration effect of the specified device.
		/// 
		/// @param _nDeviceID Internal device id.
		/// @param _oVibrationParams Vibration effect parameters.
		void SetVibration(int _nDeviceID, const SVibrationParams &_oVibrationParams);

	private:
		SAM_HWND m_pWinHandle;
		LPDIRECTINPUT8 m_pDirectInput;	///< DirectX 8 input system.
		IInputDevice *m_pFirstDevice;
		int m_nCurrentIndex;			///< Incremental index to set internal device ID.

		int m_iModifiers;    ///< Current pressed input modifiers.

		typedef std::set<IInputListener*> InputListeners;
		InputListeners m_aInputListeners; ///< Array of input listeners.

		/// @brief Retrieves device by index.
		/// 
		/// @param _nIndex Internal device ID.
		///
		/// @return null or pointer to the device.
		IInputDevice *GetDevice(int _nIndex);
	};
}

#endif // __CINPUT_MANAGER_PLF__

