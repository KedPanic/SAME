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

#include <set>
#include <map>
#include <list>
#include <vector>
#include <queue>

#include <string>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <fcntl.h>

#include <math.h>
#include <float.h>
#include <xmmintrin.h>
#include <dlfcn.h>
#include <unistd.h>
#include <limits.h>

#define INLINE inline

// define macro platform
#define SAM_PLATFORM_LINUX
#ifdef __x86_64__
#   define SAM_64BITS
#else
#   define SAM_32BITS
#endif

// define inner type
namespace sam
{
    typedef std::string String;
    typedef std::wstring UString;
    typedef unsigned long SAM_HWND;
    typedef FILE File;
    typedef std::list<String> VString;
    typedef time_t Time;
    typedef LONG atomic;
}

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

// SHARED API
#define LIBRARY_EXPORT
#define LIBRARY_IMPORT

// define debug macro
#ifdef DEBUG
#	define SAM_DEBUG
#	define DEBUG_BREAK __builtin_trap()

// Assertion helper method.
static char g_sMessage[256];
static bool SamAssert(bool p_bCondition, const char *p_sFormat, ...)
{
    if(!p_bCondition)
    {
        va_list args;
        va_start(args, p_sFormat);
        vsprintf(g_sMessage, p_sFormat, args);
        va_end(args);

		strcat(g_sMessage, "\nWould you like to break ?");

        printf("%s", g_sMessage);
        // TODO: show a dialog.
		return true;
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

#define SAM_UNIMPLEMENTED SAM_ASSERT(false, "Unimplemented function")

#else
#	define DEBUG_BREAK

#   define SamAssert(_bCondition, _sFormat, _pArg)
#   define SAM_ASSERT(_bCondition, _sMessage, ...)
#	define SAM_TRAP(p_bCondition)
#   define SAM_UNIMPLEMENTED
#endif // _DEBUG

//*******************************************//
//            DYNAMIC LIBRARY                //
//*******************************************//
void SamLogWarning(const char *_sFormat, ...);
void SamLogErrorNoAssert(const char *_sFormat, ...);

typedef void* Library;
typedef void* Symbol;

#if defined SAM_DEBUG
#	define SHARED_LIBRARY_EXT "_D.so"
#else
#	define SHARED_LIBRARY_EXT ".so"
#endif

static void GetLastError(char **_pMsg)
{
    SAM_UNIMPLEMENTED;
}

/// @brief load the dynamic library.
///
/// @param _pLibName Dynamic library name.
static Library SamLoadLibrary(const char *_pLibName);

/// @brief Unload the dynamic library.
///
/// @param _pLibHandle Dynamic library handle to freed.
static bool SamFreeLibrary(Library p_pLibHandle);

/// @brief Retrieves symbol address.
///
/// @param p_pLibHandle Dynamic library handle.
/// @param p_sSymbolName Symbol to find.
///
/// @return Symbol address.
static Symbol SamGetSymbol(Library p_pLibHandle, const char *p_sSymbolName);

#include "FileUtil.h"

#endif // __PLATFORM_PLF__
