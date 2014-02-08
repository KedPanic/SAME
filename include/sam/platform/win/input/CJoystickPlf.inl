/// @brief Set dead zone for stick.
/// 
/// @param _fDeadZone Dead zone value: 0.0-1.0
INLINE void CJoystick::SetDeadZone(float _fDeadZone)
{
	SAM_ASSERT(_fDeadZone >= 0.0f && _fDeadZone <= 1.0f, "Bad value, dead zone must to be between 0.0 and 1.0");
	m_fDeadZone = _fDeadZone;
}

/// @brief Prepare stick event.
/// 
/// @param _fThumbX Value of the x-axis.
/// @param _fThumbY Value of the y-axis.
/// @param _fNormalizedThumbX Normalized x-axis (-1.0 1.0)
/// @param _fNormalizedThumbY Normalized y-axis (-1.0 1.0)
/// 
/// @return true if event can be sended
///
/// see: http://msdn.microsoft.com/en-us/library/windows/desktop/ee417001(v=vs.85).aspx
INLINE bool CJoystick::PrepareStickEvent(float _fThumbX, float _fThumbY, float &_fNormalizedThumbX, float &_fNormalizedThumbY)
{
	float fMagnitude = sqrt_fast(_fThumbX * _fThumbX + _fThumbY * _fThumbY);

	// check if the controller is outside a circular dead zone.
	if(fMagnitude > m_fDeadZone * 32767.0f)
	{
		_fNormalizedThumbX = _fThumbX / fMagnitude;
		_fNormalizedThumbY = _fThumbY / fMagnitude;
		
		// clip the magnitude at its expected maximum value.
		if(fMagnitude > 32767.0f) 
			fMagnitude = 32767.0f;

		// normalize the magnitude with respect to its expected range.
		float fNormalizedMagnitude = fMagnitude / 32767.0f;

		// adjust magnitude relative to the end of the dead zone.
		fNormalizedMagnitude = (fNormalizedMagnitude - m_fDeadZone) / (1.0f - m_fDeadZone);

		return true;
	}

	return false;
}

/// @brief Send input event.
/// 
/// @param _oEvent Event to send.
INLINE void CJoystick::SendEvent(SInputEvent &_oEvent)
{
	// send button event.
	_oEvent.m_nModifiers = 0;			
	_oEvent.m_sKeyName = g_aKeyName[_oEvent.m_eKey];

	// send input event.
	g_Env->pInputManager->FireInputEvent(_oEvent);
}
