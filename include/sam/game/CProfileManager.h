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
#ifndef __CPROFILE_MANAGER__
#define __CPROFILE_MANAGER__

namespace sam
{
    /// @brief Manager players profiles.
    class SAM_GAME_API CProfileManager : public IAllocated
    {
    public:
        /// @brief Constructor.
        CProfileManager(void);

        /// @brief Destructor.
        ~CProfileManager(void);

        /// @brief Initialize and list all profile.
        /// 
        /// @param _sFolder Folder where profiles was saved.
        void Initialize(const String &_sFolder);

        /// @brief Create a new profile.
        /// 
        /// @param _sName Name of the profile.
        /// @return Pointer to the created profile.
        IProfile *CreateProfile(const String &_sName);

        /// @brief Remove the specified profile.
        /// 
        /// @param _sName Name of the profile.
        /// @return true if no error occurred.
        bool RemoveProfile(const String &_sName);

        /// @brief Remove the specified profile.
        /// 
        /// @param _iIndex Index of the profile.
        /// @return true if no error occurred.
        bool RemoveProfile(unsigned int _iIndex);

        /// @brief Rename the specified profile.
        /// 
        /// @param _sOldName Current name of the profile.
        /// @param _sNewName New name of the profile.
        /// @return true if no error occurred.
        bool RenameProfile(const String &_sOldName, const String &_sNewName);

        /// @brief Save the specified profile.
        /// 
        /// @param _sName Name of the profile.
        /// @return true if no error occurred.
        bool SaveProfile(const String &_sName);

        /// @brief Retrieves profile by name.
        /// 
        /// @param _sName Name of the profile.
        /// @return Pointer to the profile (or NULL if not found).
        IProfile *GetProfile(const String &_sName);

        /// @brief Retrieves profile by index.
        /// 
        /// @param _iIndex Index of the profile.
        /// @return Pointer to the profile (or NULL if not found).
        IProfile *GetProfile(unsigned int _iIndex);

        /// @brief Retrieves number of profiles.
        /// @return Number of profiles.
        unsigned int GetNbProfiles() {return m_aProfiles.size();}

        /// @brief Activate specified profile by name.
        /// 
        /// @param _sName name of the profile.
        /// @return The activated profile.
        IProfile *ActivateProfile(const String &_sName);

        /// @brief Activate specified profile by index.
        /// 
        /// @param _iIndex Index of the profile.
        /// @return The activated profile.
        IProfile *ActivateProfile(unsigned int _iIndex);

        /// @brief Retrieves the current profile.
        /// 
        /// @return Current profile.
        IProfile *GetCurrentProfile() const {return m_pCurrentProfile;}        

        /// @brief Retrieves the folder where we save profiles.
        /// 
        /// @return The folder where we save profiles.
        const String GetFolder() const {return m_sFolder;}

    private:
        String m_sFolder; ///< Folder where we save profiles.

        typedef std::vector<IProfile*> Profiles;
        Profiles m_aProfiles;           ///< Array of profile.
        IProfile *m_pCurrentProfile;    ///< Pointer to the current profile.
    };
}

#endif // __CPROFILE_MANAGER__
