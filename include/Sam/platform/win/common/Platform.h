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
#ifndef __PLATFORM_PLF__
#define __PLATFORM_PLF__

#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <map>
#include <list>
#include <vector>
#include <queue>

#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>

#include <windows.h>

#include <math.h>
#include <float.h>
#include <xmmintrin.h>

#include <shlobj.h>

// undef some windows stuffs.
#ifdef CopyFile
#   undef CopyFile
#endif

#ifdef Yield
#	undef Yield
#endif

#define INLINE __forceinline

#pragma warning(disable: 4251)
#pragma warning(disable: 4275) // non DLL interface
#pragma warning(disable: 4001) // nonstandard extension (single-line comments)

// define macro platform
#define SAM_PLATFORM_WIN
#ifdef _WIN32
#   define SAM_32BITS
#elif defined _WIN64
#   define SAM_64BITS
#endif

// define inner type
typedef std::string String;
typedef std::wstring UString;
typedef HWND SAM_HWND;
typedef FILE File;
typedef std::list<String> VString;

#ifdef SAM_32BITS
	typedef char int8;
	typedef short int16;
	typedef int int32;
	typedef long long int64;
	
    typedef unsigned char uint8;
    typedef unsigned short uint16;
    typedef unsigned int uint32;
    typedef unsigned long long uint64;

    typedef float f32;
    typedef double f64;
#else
	typedef char int8;
	typedef short int16;
	typedef int int32;
	typedef long long int64;

    typedef unsigned char uint8;
    typedef unsigned short uint16;
    typedef unsigned int uint32;
    typedef unsigned long long uint64;
    typedef float f32;
    typedef double f64;
#endif // SAM_32BITS

// DLL API
#define LIBRARY_EXPORT __declspec(dllexport)
#define LIBRARY_IMPORT __declspec(dllimport)

// define debug macro
#ifdef _DEBUG
#	define SAM_DEBUG
#	define DEBUG_BREAK __debugbreak()

// Assertion helper method.
static char g_sMessage[MAX_PATH];
static bool SamAssert(bool p_bCondition, const char *_sFormat, ...)
{
    if(!p_bCondition)
    {
        va_list args;
        va_start(args, _sFormat);
        vsprintf_s(g_sMessage, MAX_PATH * sizeof(char), _sFormat, args);
        va_end(args);

		strcat(g_sMessage, "\nWould you like to break ?");

		return MessageBoxA(NULL, g_sMessage, "Assertion",  MB_YESNO | MB_ICONEXCLAMATION) == IDYES;
    }

	return false;
}

#   define SAM_ASSERT(_bCondition, _sMessage, ...) \
	{	\
		if(SamAssert(_bCondition, "File %s - Line %d\n"#_sMessage, __FILE__, __LINE__, ##__VA_ARGS__)) \
			DEBUG_BREAK;	\
	}

#define SAM_TRAP(p_bCondition)	\
	while(!(p_bCondition)) {DEBUG_BREAK;}

#else
#	define DEBUG_BREAK

#   define SamAssert(_bCondition, _sFormat, _pArg)
#   define SAM_ASSERT(_bCondition, _sMessage, ...)
#	define SAM_TRAP(p_bCondition)
#endif // _DEBUG

//*******************************************//
//            DYNAMIC LIBRARY                //
//*******************************************//
void SamLogWarning(const char *_sFormat, ...);
void SamLogError(const char *_sFormat, ...);

typedef HMODULE Library;
typedef FARPROC Symbol;

#if defined SAM_DEBUG
#	define SHARED_LIBRARY_EXT "_D.dll"
#else
#	define SHARED_LIBRARY_EXT ".dll"
#endif

static void GetLastError(char **_pMsg)
{
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)_pMsg,
        0, NULL );
}

/// @brief load the dynamic library.
/// 
/// @param _pLibName Dynamic library name.
static Library SamLoadLibrary(const char *_pLibName)
{
    Library pHandle = LoadLibraryA(_pLibName);
    if(!pHandle)
    {
        char *sErrorMsg = NULL;
        GetLastError(&sErrorMsg);

        SamLogError("Unable to load the dynamic library '%s' - error message : '%s'", _pLibName, sErrorMsg);
        return NULL;
    }

    return pHandle;
}

/// @brief Unload the dynamic library.
/// 
/// @param _pLibHandle Dynamic library handle to freed.
static bool SamFreeLibrary(Library p_pLibHandle)
{
    if(!FreeLibrary(p_pLibHandle))
    {
        char *sErrorMsg = NULL;
        GetLastError(&sErrorMsg);

        SamLogWarning("Unable to unload the dynamic library - error message : '%s'", sErrorMsg);
        return false;
    }

    return true;
}

/// @brief Retrieves symbol address.
/// 
/// @param p_pLibHandle Dynamic library handle.
/// @param p_sSymbolName Symbol to find.
///
/// @return Symbol address.
static INLINE Symbol SamGetSymbol(Library p_pLibHandle, const char *p_sSymbolName)
{
	return GetProcAddress(p_pLibHandle, p_sSymbolName);
}

#include "FileUtil.h"

#endif // __PLATFORM_PLF__
