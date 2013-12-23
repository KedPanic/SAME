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
#include "network/CNetAddress.h"

namespace sam
{
	// Default constructor.
	CNetAddress::CNetAddress()
		: m_nPort((uint16)PortAny)
	{
		*(uint32*)&m_nIp = 0xFFFFFFFF; // broadcast address. 255.255.255.255
	}

	// Create an ip address from integer.
	CNetAddress::CNetAddress(uint32 p_nIp, uint16 p_nPort)
		: m_nPort(p_nPort)
	{
		*(uint32*)&m_nIp = htonl(p_nIp);
	}

	// Create an ip address from string.
	CNetAddress::CNetAddress(const char *p_sIp, uint16 p_nPort)
		: m_nPort(p_nPort)
	{
		*(uint32*)&m_nIp = inet_addr(p_sIp);
	}

	// Create an ip address from 4 bytes.
	CNetAddress::CNetAddress(uint8 p_nIpByte1, uint8 p_nIpByte2, uint8 p_nIpByte3, uint8 p_nIpByte4, uint16 p_nPort)
		: m_nPort(p_nPort)
	{
		*(uint32*)&m_nIp = htonl((p_nIpByte1 << 24) | (p_nIpByte2 << 16) | (p_nIpByte3 << 8) | p_nIpByte4);
	}

	// Retrieve the string representation of the ip address.
	const char *CNetAddress::ToString()
	{
		static char s_sBuffer[16];
		sprintf(s_sBuffer, "%d.%d.%d.%d", m_nIp[0], m_nIp[1], m_nIp[2], m_nIp[3]);
		return s_sBuffer;
	}

	// Retrieve the integer representation of the ip address in network byte order.
	uint32 CNetAddress::GetIp()
	{
		return *(uint32*)&m_nIp;
	}

	// Set the ip address from string
	void CNetAddress::SetIp(const char *p_sIp)
	{
		*(uint32*)&m_nIp = inet_addr(p_sIp);
	}

	// Set the ip address in network byte order.
	void CNetAddress::SetIp(uint32 p_nIp)
	{
		*(uint32*)&m_nIp = p_nIp;
	}

	// Retrieve the port in network byte order.
	uint16 CNetAddress::GetPort()
	{
		return m_nPort;
	}

	// Set the port number in host byte order.
	void CNetAddress::SetPort(uint16 p_nPort)
	{
		m_nPort = p_nPort;
	}
}
