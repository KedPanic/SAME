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
#ifndef __CIP_ADDRESS__
#define __CIP_ADDRESS__

namespace sam
{
	/// @brief Network address.
	class SAM_NETWORK_API CNetAddress
	{
	public:
		/// @brief Default constructor.
		CNetAddress();

		/// @brief Create an ip address from integer.
		/// 
		/// @param p_nIp Integer representation in host byte order.
		/// @param p_nPort Port.
		CNetAddress(uint32 p_nIp, uint16 p_nPort);

		/// @brief Create an ip address from string.
		/// 
		/// @param p_sIp String representation.
		/// @param p_nPort Port.
		CNetAddress(const char *p_sIp, uint16 p_nPort);

		/// @brief Create an ip address from 4 bytes.
		/// 
		/// @param p_nIpByte1 First byte representation.
		/// @param p_nIpByte2 Second byte representation.
		/// @param p_nIpByte3 Third byte representation.
		/// @param p_nIpByte4 Fourth byte representation.
		/// @param p_nPort Port.
		CNetAddress(uint8 p_nIpByte1, uint8 p_nIpByte2, uint8 p_nIpByte3, uint8 p_nIpByte4, uint16 p_nPort);

		/// @brief Retrieve the string representation of the ip address.
		/// 
		/// @return The string representation of the ip address.
		const char *ToString();

		/// @brief Retrieve the integer representation of the ip address in network byte order.
		/// 
		/// @return The integer representation of the ip address.
		uint32 GetIp();

		/// @brief Set the ip address from string
		/// 
		/// @param p_sIp Ip address.
		void SetIp(const char *p_sIp);

		/// @brief Set the ip address in network byte order.
		/// 
		/// @param p_nIp Ip address.
		void SetIp(uint32 p_nIp);

		/// @brief Retrieve the port in host byte order.
		/// 
		/// @return The port.
		uint16 GetPort();

		/// @brief Set the port number in host byte order.
		/// 
		/// @param p_nPort Port number
		void SetPort(uint16 p_nPort);

	private:
		uint8  m_nIp[4];
		uint16 m_nPort;
	};
}

#endif // __CIP_ADDRESS__
