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
#ifndef __CLOCALIZATION_MANAGER__
#define __CLOCALIZATION_MANAGER__

namespace sam
{
    /// @brief Interface to manage localization.
    class SAM_FRAMEWORK_API CLocalizationManager : public IAllocated
    {
    public:
        /// @brief Constructor.
        CLocalizationManager();

        /// @brief Destructor.
        ~CLocalizationManager();

        /// @brief Set current language.
        /// 
        /// @param _sLanguage Language folder where we load XML file.
        /// @return True if no error occurred.
        bool SetLanguage(const char *_sLanguage);

        /// @brief Retrieves current language.
        /// 
        /// @return Current language.
        const char *GetLanguage() const;

        /// @brief Load the specified XML file.
        /// 
        /// @param _sFile Name of the file.
        /// @param _sGroup Name of the localization group.
        bool LoadXML(const char *_sFile, const char *_sGroup = "global");

        /// @brief Unload specified group.
        /// 
        /// @param _sGroup Name of the localization group.
        void UnloadGroup(const char *_sGroup);

        /// @brief Unload all data.
        void Unload();

        /// @brief Retrieves text from code.
        /// 
        /// @param _sGroup Localization group where we can find the code.
        /// @param _sCode Localization code.
        /// @return Localized text or code if it not found.
        wchar_t *GetText(const char *_sGroup, const wchar_t *_sCode);

        /// @brief Retrieves text from code with special format.
        /// 
        /// @param _sGroup Localization group where we can find the code.
        /// @param _sCode Localization code.
        /// @param _pParams Array of parameters.
        /// @param _iNbParams Number of parameters.
        /// @return Localized text or code if it not found.
        /// 
        /// @remarks
        ///        Extra arguments have to be string.
        /// 
        ///        GetFormatedText("global", "ui_Example", "ok", "go");
        ///        "this is an example, we replace %1 and %2"
        ///        return "this is an example, we replace ok and go"
        const wchar_t *GetFormatedText(const char *_sGroup, const wchar_t *_sCode, const wchar_t **_pParams, int _iNbParams);

    private:
        char m_sCurrentLanguage[3]; ///< Current language.

        typedef std::map<const wchar_t *, wchar_t *> Dictionnary;
        typedef std::map<const char *, Dictionnary*> DictionnaryGroup;

        DictionnaryGroup m_DictionnaryGroups; ///< Dictionnary translation per group.
    };
}

#endif // __CLOCALIZATION_MANAGER__
