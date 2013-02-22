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
#include "common/SamPCH.h"
#include "common/io/CFile.h"
#include "common/base/CLog.h"

namespace sam
{
    /// @brief Constructor.
    CLog::CLog()
    {

    }

    /// @brief Destructor.
    CLog::~CLog()
    {
    }

    /// @brief Set filename.
    /// 
    /// @param _sFilename Name of file.
    /// @remarks Close and open new file.
    void CLog::SetFilename(const char *_sFilename)
    {
        m_sFilename = _sFilename;
        m_File.Open(_sFilename, e_OM_Write);
    }

    /// @brief Write message.
    /// 
    /// @param _eType Type of log message.
    /// @param _sFormat Message format.
    /// @param ... List of arguments.
    void CLog::LogMessage(ELogType _eType, const char *_sFormat, ...)
    {
        va_list args;
        va_start(args, _sFormat);
        LogMessage(_eType, _sFormat, args);
        va_end(args);
    }

    /// @brief Write message.
    /// 
    /// @param _eType Type of log message.
    /// @param _sFormat Message format.
    /// @param _pArg List of arguments.
    void CLog::LogMessage(ELogType _eType, const char *_sFormat, va_list _pArg)
    {
        char aBuffer[1024];
        memset(aBuffer, '\0', sizeof(aBuffer));
        switch(_eType)
        {
        case ELog_Message:
            strcat(aBuffer, "M - ");
            break;
        case ELog_Warning:
            strcat(aBuffer, "W - ");
            break;
        case ELog_Error:
            strcat(aBuffer, "E - ");
            break;
        }

        // write message.        
        vsnprintf_s(&aBuffer[4], sizeof(aBuffer) - 4, _TRUNCATE, _sFormat, _pArg);

        uint32 nSize = strlen(aBuffer) + 1;
        aBuffer[nSize] = '\n';
        m_File.Write(aBuffer, nSize);
		m_File.Flush();

        // send message to callback.
        LogCallbacks::iterator it = m_aLogCallbacks.begin(), it_end = m_aLogCallbacks.end();
        while(it != it_end)
        {
            (*it)->OnWriteMessage(_eType, aBuffer);
            it++;
        }
    }

    /// @brief Add a new callback.
    /// 
    /// @param _pCallback Pointer to a new callback.
    void CLog::AddCallback(ILogCallback *pCallback)
    {
        SAM_ASSERT(pCallback != NULL, "pCallback is null");

        m_aLogCallbacks.insert(pCallback);
    }

    /// @brief Remove old callback.
    /// 
    /// @param _pCallback Pointer to the old callback.
    void CLog::RemoveCallback(ILogCallback *pCallback)
    {
        m_aLogCallbacks.erase(pCallback);
    }
}
