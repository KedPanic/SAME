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
#include "SamConfig.h"
#include "action/CActionMap.h"

namespace sam
{
	/// @brief Constructor.
	/// 
	/// @param _sName Name of the action map.
	CActionMap::CActionMap(const String &_sName)
		: m_sName(_sName), m_bActive(true) {}

	/// @brief Destructor.
	CActionMap::~CActionMap()
	{
		m_aActionMap.clear();

		// memory clean
		Actions::iterator it = m_aActions.begin(), it_end = m_aActions.end();
		for(; it != it_end; it++)
		{
			SAM_DELETE *it;
		}
	}

	/// @brief Add an action.
	/// 
	/// @param _sAction Action name.
	/// @param _iActionMode Flag of action mode.
	void CActionMap::AddAction(const String &_sAction, int _iActionMode)
	{		
		// check if the action doesn't exist!
		if(!GetAction(_sAction))
		{
			SAction *pAction = SAM_NEW SAction;
			pAction->name = _sAction;
			pAction->mode = _iActionMode;
		}		
	}

	/// @brief Add a key for the specified action.
	/// 
	/// @param _sKey Input key (need to be a valid key).
	/// @param _sAction Action name.
	void CActionMap::AddKey(const String &_sKey, const String &_sAction)
	{
		EKey eKey = GetKeyFromString(_sKey);
		if(eKey < K_Nb)
		{
			// Get the action
			SAction *pAction = GetAction(_sAction);
			if(pAction != 0)
				m_aActionMap.insert(ActionMap::value_type(eKey, pAction));
		}		
		else
            SamLogWarning("Unable to find key '%s' for the action '%s'", _sKey, _sAction);
	}

	/// @brief Remove a key for the specified action.
	/// 
	/// @param _sKey Input key.
	void CActionMap::RemoveKey(EKey _eKey)
	{
		m_aActionMap.erase(_eKey);
	}

	/// @brief Remove a key for the specified action.
	/// 
	/// @param _sKey Input key (need to be a valid key).
	void CActionMap::RemoveKey(const String &_sKey)
	{
		EKey eKey = GetKeyFromString(_sKey);
		if(eKey < K_Nb)
			m_aActionMap.erase(eKey);
	}

	/// @brief Generate a list of valid action for the specified key.
	/// 
	/// @param _sKey Input key.
	/// @param _eActionMode Activation mode.
	/// @param _aActions Array of valid action.
	void CActionMap::GetAction(EKey _eKey, EActionMode _eActionMode, VString &_aActions) const
	{
		ActionMap::const_iterator it = m_aActionMap.find(_eKey);
		if(it != m_aActionMap.end())
			_aActions.push_back(it->second->name);
	}

	/// @brief Generate a list of valid action for the specified key.
	/// 
	/// @param _sKey Input key.
	/// @param _eActionMode Activation mode.
	/// @param _aActions Array of valid action.
	void CActionMap::GetAction(const String &_sKey, EActionMode _eActionMode, VString &_aActions) const
	{
		EKey eKey = GetKeyFromString(_sKey);
		if(eKey < K_Nb)
			GetAction(eKey, _eActionMode, _aActions);
	}

	/// @brief Retrieves action by name.
	/// 
	/// @param _sName Action name.
	CActionMap::SAction *CActionMap::GetAction(const String &_sName) const
	{
		Actions::const_iterator it = m_aActions.begin(), it_end = m_aActions.end();
		for(; it != it_end; it++)
		{
			if((*it)->name == _sName)
				return *it;
		}

		return 0;
	}
}
