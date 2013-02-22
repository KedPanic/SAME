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
#ifndef __SR_FLASH_SERIALIZATION__
#define __SR_FLASH_SERIALIZATION__

#include <SamConfig.h>
#include <sstream>

namespace sam
{
    namespace helper
    {
        static std::list<const wchar_t*> s_StringToFree;
        inline void FreeString()
        {
            std::list<const wchar_t*>::iterator it = s_StringToFree.begin(), it_end = s_StringToFree.end();
            while(it != it_end)
            {
                SAM_FREE(*it);
                it = s_StringToFree.erase(it);
            }
        }

        /// @brief Convert flash argument to xml flash argument.
        /// 
        /// @param _Arv Argument to convert.
        /// @return XML Flash argument.
        inline std::wstring Value(const sam::SFlashArgument &_Arg)
        {
            switch(_Arg.type)
            {
            case sam::FAT_Bool:
                return _Arg.value.b?L"<true/>":L"<false/>";

            case sam::FAT_Int:
                {
                    std::wstringstream wss;
                    wss << L"<number>" << _Arg.value.i << L"</number>";
                    return wss.str();
                }                

            case sam::FAT_Float:
                {
                    std::wstringstream wss;
                    wss << L"<number>" << _Arg.value.f << L"</number>";
                    return wss.str();
                }                

            case sam::FAT_String:
                {
                    UString value(_Arg.value.s);
                    sam::replace(value, L"&", L"&amp;");
                    sam::replace(value, L"\"", L"&quot;");
                    sam::replace(value, L"'", L"&apos;");
                    sam::replace(value, L"<", L"&lt;");
                    sam::replace(value, L">", L"&gt;");

                    return L"<string>" + value + L"</string>";
                }                
            }

            return L"<null/>";
        }

        /// @brief Serialize flash invocation.
        /// 
        /// @param _sFunction Function name.
        /// @param _pArgs Array of arguments.
        /// @param _iNbArgs Size of the array.
        /// @param _sResult Serialization result.
        inline void Invoke(const UString &_sFunction, const sam::SFlashArgument *_pArgs, uint32 _iNbArgs, std::wstring &_sResult)
        {
            _sResult += L"<invoke name=\"" + _sFunction + L"\" returntype=\"xml\">";

            _sResult += L"<arguments>";
            // Add argument list.
            if(_pArgs && _iNbArgs)
            {                
                for(uint32 i = 0; i < _iNbArgs; i++)
                    _sResult += Value(_pArgs[i]);                
            }
            _sResult += L"</arguments>";

            _sResult += L"</invoke>";
        }

        // Deserialize the result.
        inline void Result(sam::SFlashArgument *_pResult, UString &_sResult)
        {
            if(_pResult)
            {
                // null return.
                if(_sResult == L"<null/>" || _sResult == L"<undefined/>")
                    _pResult->type = sam::FAT_Void;
                // boolean return
                else if(_sResult == L"<true/>")
                {
                    _pResult->type = sam::FAT_Bool;
                    _pResult->value.b = true;
                }
                else if(_sResult == L"<false/>")
                {
                    _pResult->type = sam::FAT_Bool;
                    _pResult->value.b = false;
                }
                // number return.
                else if(_sResult.substr(0, 8) == L"<number>")
                {
                    std::wstringstream result;
                    result.str(_sResult.substr(8, _sResult.find(L"</number>", 8) - 8));
                    // float
                    if(_sResult.find(L".") != -1)
                    {
                        _pResult->type = sam::FAT_Float;
                        result >> _pResult->value.f;
                    }                    
                    else
                    {
                        _pResult->type = sam::FAT_Int;
                        result >> _pResult->value.i;
                    }
                }
                else if(_sResult.substr(0, 8) == L"<string>")
                {
                    _sResult = _sResult.substr(8, _sResult.find(L"</string>", 8) - 8);
                    sam::replace(_sResult, L"&quot;", L"\"");
                    sam::replace(_sResult, L"&apos;", L"'");
                    sam::replace(_sResult, L"&lt;", L"<");
                    sam::replace(_sResult, L"&gt;", L">");
                    sam::replace(_sResult, L"&amp;", L"&");

                    int iSize = (_sResult.size() * sizeof(wchar_t)) + 1;
                    _pResult->type = sam::FAT_String;

                    // Copy wstring to buffer.
                    wchar_t *pBuffer = SAM_ALLOC_ARRAY(wchar_t, iSize);
                    memset(pBuffer, '\0', iSize);
                    _pResult->value.s = wcsncpy(pBuffer, _sResult.c_str(), iSize);

                    s_StringToFree.push_back(_pResult->value.s);
                }
                else
                    _pResult->type = sam::FAT_Void;
            }
        }

        /// @brief Deserialize flash call.
        /// 
        /// 
        inline sam::SFlashArgument *FlashCall(const UString &_sRequest, UString &_sFunction, int &_iNbArgs)
        {
            // retrieves function name.
            int iIndex = _sRequest.find(L"<invoke name=\"");
            if(iIndex == std::string::npos)
                return 0;
            _sFunction = _sRequest.substr(iIndex + 14, _sRequest.find(L"\"", iIndex + 14) - (iIndex + 14));

            // retrieves arguments.
            iIndex = _sRequest.find(L"<arguments>", iIndex + 14 + _sFunction.length() + 19) + 11;
            UString args = _sRequest.substr(iIndex, _sRequest.find(L"</arguments>", iIndex) - iIndex);

            std::vector<sam::SFlashArgument> vArgs;
            iIndex = 0;
            while(true)
            {              
                if( (iIndex = args.find_first_of(L"<", iIndex)) == UString::npos)
                    break;

                int iEnd = args.find_first_of(L">", args.find(L"</", iIndex));
                if(iEnd != std::string::npos)
                {
                    sam::SFlashArgument arg;
                    Result(&arg, args.substr(iIndex,  iEnd + 1 - iIndex));
                    vArgs.push_back(arg);

                    iIndex = iEnd;
                }
                else
                    break;
            }

            // Set flash argument.
            _iNbArgs = vArgs.size();
            sam::SFlashArgument *pArgs = SAM_NEW sam::SFlashArgument[_iNbArgs];
            memcpy(pArgs, &vArgs[0], sizeof(sam::SFlashArgument) * _iNbArgs);       

            return pArgs;
        }        

        /// @brief Convert SFlashArgument to BStr
        /// 
        /// @param _sValue Value to convert.
        /// @return Argument converted.
        inline std::wstring Variable(const sam::SFlashArgument &_Value)
        {
            switch(_Value.type)
            {
            case sam::FAT_Bool:
                return _Value.value.b?L"true":L"false";

            case sam::FAT_Int:
                {
                    std::wstringstream wss;
                    wss << _Value.value.i;
                    return wss.str();
                }                

            case sam::FAT_Float:
                {
                    std::wstringstream wss;
                    wss << _Value.value.f;
                    return wss.str();
                }                

            case sam::FAT_String:
                return _Value.value.s; 
            }

            return L"";
        }

    }
}

#endif // __SR_FLASH_SERIALIZATION__
