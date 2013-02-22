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
#ifndef __CACTION_HANDLER__
#define __CACTION_HANDLER__

#include <SamConfig.h>

namespace sam
{
	/// @brief Action handler : helper class to dispatch event.
	template<class T>
	class CActionHandler
	{
	public:
		typedef void (T::*OnActionHandler)(const String &_sAction, EActionMode _eActionMode, float _fValue);

		/// @brief Constructor.
		CActionHandler(T *_pHandler)
			: m_pHandler(_pHandler) {}

		/// @brief Add action handler.
		/// 
		/// @param _sAction Action name.
		/// @param _fnHandler Handler.
		void AddActionHandler(const String &_sAction, OnActionHandler _fnHandler)
		{
			m_aActions.insert(Actions::value_type(_sAction, _fnHandler));
		}

		/// @brief Callback when an action occurred.
		/// 
		/// @param _sAction Action name.
		/// @param _eActionMode Mode was activated the action.
		/// @param _fValue Extra value.
		void OnAction(const String &_sAction, EActionMode _eActionMode, float _fValue)
		{
			OnActionHandler pHandler = GetHandler(_sAction);
			if(pHandler)
			{
				// call the function
				(m_pHandler->*pHandler)(_sAction, _eActionMode, _fValue);
			}
		}

	private:
		T *m_pHandler; ///< Pointer to the class which receive action.

		typedef std::map<String, OnActionHandler> Actions;
		Actions m_aActions; ///< Array of mapped actions.

		/// @brief Retrieves the handler by action name.
		/// 
		/// @param _sAction Action name.
		/// @return Handler or NULL if not found.
		OnActionHandler GetHandler(const String &_sAction)
		{
			Actions::iterator it = m_aActions.find(_sAction);
			if(it != m_aActions.end())
				return it->second;

			return 0;
		}
	};
}

#endif // __CATION_HANDLER__
