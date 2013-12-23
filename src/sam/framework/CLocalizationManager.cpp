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
#include "SamFrameworkPCH.h"
#include "framework/CLocalizationManager.h"
#include "framework/IFramework.h"

//#include <tinyxml.h>
#include <sstream>

namespace sam
{
    /// @brief Constructor.
    CLocalizationManager::CLocalizationManager()
    {
    }

    /// @brief Destructor.
    CLocalizationManager::~CLocalizationManager()
    {        
    }

    /// @brief Set current language.
    /// 
    /// @param _sLanguage Language folder where we load XML file.
    /// @return True if no error occurred.
    bool CLocalizationManager::SetLanguage(const char *_sLanguage)
    {
        SAM_ASSERT(_sLanguage != NULL, "Language is null");

        char sPath[64] = {'\0'};
        sprintf(sPath, "%s/localisation/%s", g_Env->pFramework->GetDataDirectory(), _sLanguage);

        // Check if folder exist
        if(IsDirectory(sPath))
        {
//             g_Env->pStreamManager->RemoveStreamLocation("localization");
//             g_Env->pStreamManager->CreateStreamLocation("localization", sPath);
            strcpy(m_sCurrentLanguage, _sLanguage);
            return true;
        }      

        SamLogError("Unable to find the language folder '%s'", _sLanguage);
        return false;
    }

    /// @brief Retrieves current language.
    /// 
    /// @return Current language.
    const char *CLocalizationManager::GetLanguage() const
    {
        return m_sCurrentLanguage;
    }

    /// @brief Load the specified XML file.
    /// 
    /// @param _sFile Name of the file.
    /// @param _sGroup Name of the localization group.
    bool CLocalizationManager::LoadXML(const char *_sFile, const char *_sGroup)
    {
/*
        // Find group or create it.
        Dictionnary *dictionnary = 0;
        DictionnaryGroup::iterator it = m_DictionnaryGroups.find(_sGroup);
        if(it != m_DictionnaryGroups.end())
            dictionnary = it->second;
        else
        {
            dictionnary = SAM_ALLOC(Dictionnary);
            m_DictionnaryGroups.insert(DictionnaryGroup::value_type(_sGroup, dictionnary));
        }

        TiXmlDocument xmlDoc;
        // Try to load XML file.        
        IStream *pFile = g_Env->pStreamManager->GetStream(_sFile, "localization");
        if(!pFile)
            return false;

        char *pBuffer = (char*)pFile->Data();
        if(xmlDoc.Parse(pBuffer, 0, TIXML_ENCODING_LEGACY))
        {
            // Retrieves root element
            TiXmlElement *pRootElement = xmlDoc.FirstChildElement();
            if(pRootElement)
            {
                // Get all language elements
                TiXmlElement *pTextElement = pRootElement->FirstChildElement();
                while(pTextElement)
                {
                    const char *sCode = pTextElement->Attribute("id");
                    const char *sText = pTextElement->GetText();                    
                    dictionnary->insert(Dictionnary::value_type(toWChar(sCode),  toWChar(sText)));

                    pTextElement = pTextElement->NextSiblingElement();
                }

                // Release buffer.
                SAM_FREE(pBuffer);

                // Release file.
                SAM_DELETE pFile;

                return true;
            }
            else
                SamLogError("Unable to retrieves root node in the XML localization file '%s'", _sFile);
        }

        // Release buffer.
        SAM_FREE(pBuffer);

        // Release file.
        SAM_DELETE pFile;
*/
        return false;
    }

    /// @brief Unload specified group.
    /// 
    /// @param _sGroup Name of the localization group.
    void CLocalizationManager::UnloadGroup(const char *_sGroup)
    {
        // find group.
        DictionnaryGroup::iterator it =  m_DictionnaryGroups.find(_sGroup);
        if(it != m_DictionnaryGroups.end())
        {
            SAM_FREE(it->second);
            m_DictionnaryGroups.erase(it);
        }
    }

    /// @brief Unload all data.
    void CLocalizationManager::Unload()
    {
        DictionnaryGroup::iterator it = m_DictionnaryGroups.begin(), it_end = m_DictionnaryGroups.end();
        while(it != it_end)
        {
            SAM_FREE(it->second);
            it = m_DictionnaryGroups.erase(it);
        }        
    }

    /// @brief Retrieves text from code.
    /// 
    /// @param _sGroup Localization group where we can find the code.
    /// @param _sCode Localization code.
    /// @return Localized text or code if it not found.
    wchar_t *CLocalizationManager::GetText(const char *_sGroup, const wchar_t *_sCode)
    {
        // find group.
        DictionnaryGroup::iterator it =  m_DictionnaryGroups.find(_sGroup);
        if(it != m_DictionnaryGroups.end())
        {
            // find code.
            Dictionnary::iterator dico_it = it->second->find(_sCode);
            if(dico_it != it->second->end())
                return dico_it->second;
        }

        return NULL;
    }

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
    const wchar_t *CLocalizationManager::GetFormatedText(const char *_sGroup, const wchar_t *_sCode, const wchar_t **_pParams, int _iNbParams)
    {
        wchar_t *sText = GetText(_sGroup, _sCode);
        if(sText)
        {
            // replace code per string argument
            for(int i = 1; i <= _iNbParams; i++)   
            {
                wchar_t sReplace[4] = L"%00";
                _itow(i, &sReplace[1], 10);

                replace(sText, sReplace, _pParams[i - 1]);
            }

            return sText;
        }

        return _sCode;
    }
}
