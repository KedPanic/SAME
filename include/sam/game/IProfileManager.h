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
#ifndef __IPROFILEMANAGER__
#define __IPROFILEMANAGER__

namespace sam
{
	/// @brief Manager players profiles.
	class IProfileManager : public IAllocated
	{
	public:
		/// @brief Initialize and list all profile.
		/// 
		/// @param _sFolder Folder where profiles was saved.
		virtual void Initialize(const String &_sFolder) = 0;

		/// @brief Create a new profile.
		/// 
		/// @param _sName Name of the profile.
		/// @return Pointer to the created profile.
		virtual IProfile *CreateProfile(const String &_sName) = 0;

		/// @brief Remove the specified profile.
		/// 
		/// @param _sName Name of the profile.
		/// @return true if no error occurred.
		virtual bool RemoveProfile(const String &_sName) = 0;

        /// @brief Remove the specified profile.
        /// 
        /// @param _iIndex Index of the profile.
        /// @return true if no error occurred.
        virtual bool RemoveProfile(unsigned int _iIndex) = 0;

		/// @brief Rename the specified profile.
		/// 
		/// @param _sOldName Current name of the profile.
		/// @param _sNewName New name of the profile.
		/// @return true if no error occurred.
		virtual bool RenameProfile(const String &_sOldName, const String &_sNewName) = 0;

        /// @brief Save the specified profile.
        /// 
        /// @param _sName Name of the profile.
        /// @return true if no error occurred.
        virtual bool SaveProfile(const String &_sName) = 0;

		/// @brief Retrieves profile by name.
		/// 
		/// @param _sName Name of the profile.
		/// @return Pointer to the profile (or NULL if not found).
		virtual IProfile *GetProfile(const String &_sName) = 0;

		/// @brief Retrieves profile by index.
		/// 
		/// @param _iIndex Index of the profile.
		/// @return Pointer to the profile (or NULL if not found).
		virtual IProfile *GetProfile(unsigned int _iIndex) = 0;

		/// @brief Retrieves number of profiles.
		/// @return Number of profiles.
		virtual unsigned int GetNbProfiles(void) = 0;

        /// @brief Activate specified profile by name.
        /// 
        /// @param _sName name of the profile.
        /// @return The activated profile.
        virtual IProfile *ActivateProfile(const String &_sName) = 0;

        /// @brief Activate specified profile by index.
        /// 
        /// @param _iIndex Index of the profile.
        /// @return The activated profile.
        virtual IProfile *ActivateProfile(unsigned int _iIndex) = 0;

        /// @brief Retrieves the current profile.
        /// 
        /// @return Current profile.
        virtual IProfile *GetCurrentProfile(void) const = 0;      

        /// @brief Retrieves the folder where we save profiles.
        /// 
        /// @return The folder where we save profiles.
        virtual const String GetFolder(void) const = 0;
	};
}

#endif // ~__IProfileMANAGER__
