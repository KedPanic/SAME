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
#include "SamNetworkPCH.h"

namespace sam
{
	// Retrieves last error as string.	
	char *GetNetworkError()
	{
		int nErrorCode = WSAGetLastError();
		switch(nErrorCode)
		{
		case WSANOTINITIALISED:
			return "Either the application has not called WSAStartup, or WSAStartup failed.";
		
		case WSAEADDRINUSE:
			return "Only one usage of each socket address (protocol/network address/port) is normally permitted.";

		case WSAEFAULT:
			return "The system detected an invalid pointer address in attempting to use a pointer argument in a call.";

		case WSAEWOULDBLOCK:
			return "A non-blocking socket operation could not be completed immediately.";

		case WSAECONNRESET:
			return "An existing connection was forcibly closed by the remote host.";

		default:
			SAM_TRAP(false);
			return "Unknow error";
		}
	}

	namespace priv
	{
		static bool s_bWinsockInitialized = false;

		bool InitNetwork()
		{
			WSADATA oWSAData;
			int nResult = WSAStartup(MAKEWORD(2, 2), &oWSAData);
			if(nResult != 0)
			{
				SamLogErrorNoAssert("Unable to initialize winsock, error: %d", nResult);
				return false;
			}

			s_bWinsockInitialized = true;
			return true;
		}

		void ShutdownNetwork()
		{
			if(s_bWinsockInitialized)
			{
				WSACleanup();
			}
		}
	}	
}