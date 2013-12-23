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
#ifndef __CLOG__
#define __CLOG__

namespace sam
{
    /// @enum Define type of message.
    enum ELogType
    {
        ELog_Message,
        ELog_Warning,
        ELog_Error,
    };

    /// @brief Log callback.
    class ILogCallback
    {
    public:
        /// @brief Called when a message is written.
        /// 
        /// @param _sMessage Message was written.
        virtual void OnWriteMessage(ELogType _eType, const String &_sMessage) = 0;
    };

    /// @brief Log file.
	/// 
	/// @remarks: Log is available in debug and profile.
    class SAM_COMMON_API CLog : public IAllocated
    {
    public:
        /// @brief Constructor.
        CLog();

        /// @brief Destructor.
        ~CLog();

        /// @brief Set filename.
        /// 
        /// @param _sFilename Name of file.
        /// @remarks Close and open new file.
        void SetFilename(const char *_sFilename);

        /// @brief Retrieves current filename.
        /// 
        /// @return Name of file.
        const char *GetFilename(void) const;

        /// @brief Write message.
        /// 
        /// @param _eType Type of log message.
        /// @param _sFormat Message format.
        /// @param ... List of arguments.
        void LogMessage(ELogType _eType, const char *_sFormat, ...);

        /// @brief Write message.
        /// 
        /// @param _eType Type of log message.
        /// @param _sFormat Message format.
        /// @param _pArg List of arguments.
        void LogMessage(ELogType _eType, const char *_sFormat, va_list _pArg);

        /// @brief Add a new callback.
        /// 
        /// @param _pCallback Pointer to a new callback.
        void AddCallback(ILogCallback *pCallback);
        
        /// @brief Remove old callback.
        /// 
        /// @param _pCallback Pointer to the old callback.
        void RemoveCallback(ILogCallback *pCallback);

    private:
        String m_sFilename; ///< Name of file.
        CFile m_File;       ///< File handler.

        typedef std::set<ILogCallback*> LogCallbacks;
        LogCallbacks m_aLogCallbacks; ///< Array of callback.
    };    
}


// Helper method to log
INLINE void SamLog(const char *_sFormat, ...)
{
#if defined(SAM_PROFILING)
    va_list args;
    va_start(args, _sFormat);
    sam::g_Env->pLog->LogMessage(sam::ELog_Message, _sFormat, args);
    va_end(args);
#endif
}

INLINE void SamLogWarning(const char *_sFormat, ...)
{
#if defined(SAM_PROFILING)
    va_list args;
    va_start(args, _sFormat);
    sam::g_Env->pLog->LogMessage(sam::ELog_Warning, _sFormat, args);
    va_end(args);
#endif
}

INLINE void SamLogErrorNoAssert(const char *_sFormat, ...)
{
#if defined(SAM_PROFILING)
    va_list args;
    va_start(args, _sFormat);
    sam::g_Env->pLog->LogMessage(sam::ELog_Error, _sFormat, args);
    va_end(args);
#endif
}

// We want to break when an error occurred.
#define SamLogError(p_sFormat, ...)					\
	SamLogErrorNoAssert(p_sFormat, ##__VA_ARGS__);	\
	SAM_ASSERT(false, p_sFormat, ##__VA_ARGS__)		\

#endif // __CLOG__
