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
#ifndef __SAM_NETWORK_PCH__
#define __SAM_NETWORK_PCH__

#include <SamCommon.h>

// sam engine common subsystem macro export
#ifdef SAM_NETWORK_EXPORTS
#   define SAM_NETWORK_API LIBRARY_EXPORT
#else
#   define SAM_NETWORK_API LIBRARY_IMPORT
#endif

// platform specific configuration
#if defined( SAM_PLATFORM_LINUX )
    typedef int Socket;
#elif defined( SAM_PLATFORM_WIN )
	typedef SOCKET Socket;
#else
#	error "Unsupported platform"
#endif

namespace sam
{
	static const uint32 PortAny = -1;
	static const uint32 InvalidSocket = ~0;

	class CNetAddress;

	/// @brief Retrieves last error as string.
	///
	/// @return Last error message.
	char *GetNetworkError();

	/// @brief Initialize the network module.
	bool SAM_NETWORK_API InitNetwork(sam::Env *p_pEnv);

	/// @brief Shutdown the network module.
	void SAM_NETWORK_API ShutdownNetwork();
}

#endif // __SAM_NETWORK_PCH__
