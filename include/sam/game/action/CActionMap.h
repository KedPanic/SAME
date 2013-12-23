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
#ifndef __CACTION_MAP__
#define __CACTION_MAP__

namespace sam
{
    /// @brief Action map : manage a map of input key (mouse, joystick, keyboard and any other supported device)
    ///		with a specified action. Only one input key per action map allowed.
    class SAM_GAME_API CActionMap : public IAllocated
    {
    public:
        /// @brief Constructor.
        /// 
        /// @param _sName Name of the action map.
        CActionMap(const String &_sName);

        /// @brief Destructor.
        ~CActionMap();

        /// @brief Add an action.
        /// 
        /// @param _sAction Action name.
        /// @param _iActionMode Flag of action mode.
        void AddAction(const String &_sAction, int _iActionMode);

        /// @brief Add a key for the specified action.
        /// 
        /// @param _sKey Input key (need to be a valid key).
        /// @param _sAction Action name.
        void AddKey(const String &_sKey, const String &_sAction);

        /// @brief Remove a key for the specified action.
        /// 
        /// @param _sKey Input key.
        void RemoveKey(EKey _eKey);

        /// @brief Remove a key for the specified action.
        /// 
        /// @param _sKey Input key (need to be a valid key).
        /// @param _sAction Action name.
        void RemoveKey(const String &_sKey);

        /// @brief Generate a list of valid action for the specified key.
        /// 
        /// @param _sKey Input key.
        /// @param _eActionMode Activation mode.
        /// @param _aActions Array of valid action.
        void GetAction(EKey _eKey, EActionMode _eActionMode, VString &_aActions) const;

        /// @brief Generate a list of valid action for the specified key.
        /// 
        /// @param _sKey Input key.
        /// @param _eActionMode Activation mode.
        /// @param _aActions Array of valid action.
        void GetAction(const String &_sKey, EActionMode _eActionMode, VString &_aActions) const;

        /// @brief Get true if the the action map is active.
        /// 
        /// @return True if the action map is active.
        bool IsActive() {return m_bActive;}

        /// @brief Set true to active the action map.
        /// 
        /// @param _bActive True to active it.
        void SetActive(bool _bActive) {m_bActive = _bActive;}

    private:
        /// @brief Define an action.
        struct SAction : public IAllocated
        {
            String name; ///< Name of the action.
            int mode;	 ///< Flag of available activation mode.
        };

        typedef std::list<SAction*> Actions;
        Actions m_aActions; ///< Array of actions.

        typedef std::map<EKey, SAction*> ActionMap;
        ActionMap m_aActionMap; ///< Array of mapped actions.

        String m_sName;		///< Name of the action map.
        bool   m_bActive;	///< True if the action map is activate.

        /// @brief Retrieves action by name.
        /// 
        /// @param _sName Action name.
        SAction *GetAction(const String &_sName) const;
    };
}

#endif // __CACTION_MAP__
