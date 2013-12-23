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
#include "CUDPSocket.h"
#include "CNetAddress.h"

namespace sam
{
	// Default constructor.
	CUDPSocket::CUDPSocket()
		: m_hSocket(InvalidSocket)
	{

	}

	CUDPSocket::~CUDPSocket()
	{
		if(m_hSocket != InvalidSocket)
		{
			Unbind();
		}
	}

	// Create socket.
	bool CUDPSocket::CreateSocket(bool p_bBlocking /*= false*/, bool p_bBroadcast /*= true*/)
	{
		SAM_ASSERT(m_hSocket == InvalidSocket, "the socket is already created.");

		m_hSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if(m_hSocket == InvalidSocket)
		{
			SamLogErrorNoAssert("Unable to create udp socket: %s\n", GetNetworkError());
			return false;
		}
		
		// set I/O mode.
		if(ioctlsocket(m_hSocket, FIONBIO, (u_long*)&p_bBlocking) == SOCKET_ERROR)
		{
			SamLogErrorNoAssert("Unable to set I/O mode of the socket: %s\n", GetNetworkError());
			return false;
		}

		// set the broadcast mode.
		if(p_bBroadcast)
		{
			if(setsockopt(m_hSocket, SOL_SOCKET, SO_BROADCAST, (char*)&p_bBlocking, sizeof(bool)) == SOCKET_ERROR)
			{
				SamLogErrorNoAssert("Unable to make the socket broadcast capable: %s\n", GetNetworkError());
				return false;
			}
		}

		return true;
	}

	// Bind the socket to the specified port.
	bool CUDPSocket::Bind(int32 p_nPort)
	{
		SAM_ASSERT(m_hSocket != InvalidSocket, "Socket is not created");

		sockaddr_in oSockAddr;
		oSockAddr.sin_addr.s_addr = INADDR_ANY;
		oSockAddr.sin_family	  = AF_INET;
		if(p_nPort == PortAny)
		{
			oSockAddr.sin_port = 0;
		}
		else
		{
			oSockAddr.sin_port = htons(p_nPort);
		}

		if(bind(m_hSocket, (sockaddr*)&oSockAddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
		{
			SamLogErrorNoAssert("Unable to bind the socket on the port %d : %s\n", p_nPort, GetNetworkError());
			return false;
		}

		return true;
	}

	// Close the socket.
	void CUDPSocket::Unbind()
	{
		SAM_ASSERT(m_hSocket != InvalidSocket, "Socket is not created");

		closesocket(m_hSocket);
		m_hSocket = InvalidSocket;
	}

	// Send data to a specific destination.
	uint32 CUDPSocket::Send(const char *p_sData, uint32 p_nSize, CNetAddress *p_oTo)
	{
		SAM_ASSERT(m_hSocket != InvalidSocket, "Socket is not created");

		sockaddr_in oSockAddr;
		oSockAddr.sin_addr.s_addr = p_oTo->GetIp();
		oSockAddr.sin_family = AF_INET;		
		oSockAddr.sin_port = htons(p_oTo->GetPort());
		uint32 nBytesSent = sendto(m_hSocket, p_sData, p_nSize, 0, (sockaddr*)&oSockAddr, sizeof(sockaddr_in));
		if(nBytesSent == SOCKET_ERROR)
		{
			SamLogWarning("Unable to send datagram: %s\n", GetNetworkError());
			return 0;
		}

		return nBytesSent;
	}

	// Receives a datagram.
	uint32 CUDPSocket::Receive(char *p_sData, uint32 p_nSize, CNetAddress *p_oFrom)
	{
		SAM_ASSERT(m_hSocket != InvalidSocket, "Socket is not created");

		sockaddr oFrom;
		int32 nFromLen = sizeof(sockaddr);

		int32 nBytesReceived = recvfrom(m_hSocket, p_sData, p_nSize, 0, &oFrom, &nFromLen);
		if(nBytesReceived == SOCKET_ERROR)
		{
			SamLogWarning("Unable to receive datagram: %s\n", GetNetworkError());
			return 0;
		}

		if(oFrom.sa_family == AF_INET)
		{
			sockaddr_in *pFromIn = (sockaddr_in*)&oFrom;
			p_oFrom->SetIp(pFromIn->sin_addr.s_addr);
			p_oFrom->SetPort(htons(pFromIn->sin_port));
		}

		return nBytesReceived;
	}
}
