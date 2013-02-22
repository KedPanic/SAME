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
#ifndef __STRING_UTIL__
#define __STRING_UTIL__

#include <common/SamConfig.h>

namespace sam
{
    /// @brief Convert char to wchar_t
    /// 
    /// @param _sStr String to convert.
    ///
    /// @return String converted.
    inline wchar_t *toWChar(const char *_sStr)
    {
        uint32 _nLength = strlen(_sStr);

        wchar_t *wStr = SAM_ALLOC_ARRAY(wchar_t, _nLength);
        mbstowcs(wStr, _sStr, _nLength);

        return wStr;
    }

    /// @brief Convert string to wstring
    /// 
    /// @param _sStr String to convert.
    /// @param _Loc Language.
    /// @return String converted.
    inline std::wstring toWString(const String &_sStr, std::locale _Loc = std::locale())
    {        
        std::wstring wStr;
        wStr.resize(_sStr.length());

        std::ctype<wchar_t> const& ct = std::_USE(std::locale(), std::ctype<wchar_t>);
        for(uint32 i = 0; i < _sStr.length(); i++)
            wStr[i] = ct.widen(_sStr[i]);

        return wStr;
    }

    /// @brief Convert wstring to string
    /// 
    /// @param _sWStr wstring to convert.
    /// @param _Loc Language.
    /// @return wstring converted.
    inline String toString(const std::wstring &_sWStr, std::locale _Loc = std::locale())
    {        
        String str;
        str.resize(_sWStr.length());

        std::ctype<wchar_t> const& ct = std::_USE(std::locale(), std::ctype<wchar_t>);
        for(uint32 i = 0; i < _sWStr.length(); i++)
            str[i] = ct.narrow(_sWStr[i]);

        return str;
    }

    /// @brief Replace specified characters.
    /// 
    /// @param _sBase Base of the string.
    /// @param _sReplace Characters to remove.
    /// @param _sWith Characters to put.
    inline String replace(String &_sBase, const String &_sReplace, const String &_sWith)
    {
        for(size_t i = _sBase.find(_sReplace); i != UString::npos; i = _sBase.find(_sReplace, i + _sWith.length()))
        {
            _sBase.replace(i, _sReplace.size(), _sWith);
        }

        return _sBase;
    }

    /// @brief Replace specified characters.
    /// 
    /// @param _sBase Base of the string.
    /// @param _sReplace Characters to remove.
    /// @param _sWith Characters to put.
    inline UString replace(UString &_sBase, const UString &_sReplace, const UString &_sWith)
    {
        for(size_t i = _sBase.find(_sReplace); i != UString::npos; i = _sBase.find(_sReplace, i + _sWith.length()))
        {
            _sBase.replace(i, _sReplace.size(), _sWith);
        }

        return _sBase;
    }

    /// @brief Replace specified characters.
    /// 
    /// @param _sBase Base of the string.
    /// @param _sReplace Characters to remove.
    /// @param _sWith Characters to put.
    inline char *replace(char *_sBase, const char *_sReplace, const char *_sWith)
    {
        char *sPCH = strstr(_sBase, _sReplace);
        if(sPCH != _sBase)
        {
            strncpy(sPCH, _sWith, strlen(_sWith));
            return replace(_sBase, _sReplace, _sWith);
        }

        return _sBase;
    }

    /// @brief Replace specified characters.
    /// 
    /// @param _sBase Base of the string.
    /// @param _sReplace Characters to remove.
    /// @param _sWith Characters to put.
    inline wchar_t *replace(wchar_t *_sBase, const wchar_t *_sReplace, const wchar_t *_sWith)
    {
        wchar_t *sPCH = wcsstr(_sBase, _sReplace);
        if(sPCH != _sBase)
        {
            wcsncpy(sPCH, _sWith, wcslen(_sWith));
            return replace(_sBase, _sReplace, _sWith);
        }

        return _sBase;
    }


    /// @brief split the string with specified character(s)
    /// 
    /// @param _sBase String have to split.
    /// @param _sDelimiter Delimiter.
    inline VString split(const String &_sBase, const String &_sDelimiter)
    {
        size_t start, end;
        VString split_str;

        start = 0;
        do
        {
            end = _sBase.find_first_of(_sDelimiter, start);

            split_str.push_back(_sBase.substr(start, end - start));

            start = end + 1;
        }
        while(end != String::npos);

        return split_str;
    }

    /// @brief split the string with specified character(s)
    /// 
    /// @param _sBase String have to split.
    /// @param _sDelimiter Delimiter.
    /// @param _asListStr List of string.
    inline void split(char *_sBase, const char *_sDelimiter, std::vector<char*> &_asListStr)
    {
        char *sPCH = strtok(_sBase, _sDelimiter);
        while(sPCH != NULL)
        {
            _asListStr.push_back(sPCH);
            sPCH = strtok(NULL, _sDelimiter);            
        }
    }

    /// @brief Convert string value to specified type.
    /// 
    /// @param _sValue Base string to convert.
    /// 
    /// @return The converted value.
    template<typename T>
    inline T parseValue(const String &_sValue)
    {
        std::istringstream stream(_sValue);
        T result;
        stream >> result;
        if (stream.fail()) 
            return T();
        else
        {
            int item = stream.get();
            while (item != -1)
            {
                if (item != ' ' && item != '\t') return T();
                item = stream.get();
            }
        }

        return result;
    }

    /// @brief Convert specified value to string.
    /// 
    /// @param _tValue Value to convert.
    /// 
    /// @return Converted value.
    template <typename T>
    inline const char *toStringT(const T &_tValue)
    {
        std::ostringstream stream;
        stream << _tValue;
        return stream.str().c_str();
    }

    /// @brief Remove white space from the string.
    /// 
    /// @param _pStr String to remove white space.
    ///
    /// @return Number of removed characters.
    inline uint32 RemoveWhiteSpace(char *_pStr)
    {
        SAM_ASSERT(_pStr != NULL, "String is null");

        uint32 nNbChar = 0;
        char *pBuffer = _pStr;
        while(*pBuffer && (*pBuffer == ' ' || *pBuffer == '\t'))
        {
            ++nNbChar;
            ++pBuffer;
        }

        return nNbChar;
    }
}

#endif // __STRING_UTIL__