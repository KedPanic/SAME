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
#ifndef __CUDP_SOCKET__
#define __CUDP_SOCKET__

namespace sam
{
	static const uint16 MaxDatagramSize = 1400; ///< Smallest MTU limit.

	/// @brief UDP socket.
	class SAM_NETWORK_API CUDPSocket
	{
	public:
		/// @brief Default constructor.
		CUDPSocket();
		~CUDPSocket();

		/// @brief Create socket.
		/// 
		/// @param p_bBlocking I/O mode.
		/// @param p_bBroadcast True to broadcast the data.
		/// 
		/// @return True if no error occurred.
		bool CreateSocket(bool p_bBlocking = false, bool p_bBroadcast = true);

		/// @brief Bind the socket to the specified port.
		///
		/// @param p_nPort Port used to send and receive.
		/// 
		/// @return True if no error occurred.
		bool Bind(int32 p_nPort);

		/// @brief Close the socket.
		void Unbind();

		/// @brief Send data to a specific destination.
		/// 
		/// @param p_sData A buffer of data to send.
		/// @param p_nSize Size in bytes of the buffer.
		/// @param p_oTo Address of the target.
		/// 
		/// @return Number of bytes sent.
		uint32 Send(const char *p_sData, uint32 p_nSize, CNetAddress *p_oTo);
		
		/// @brief Receives a datagram.
		/// 
		/// @param p_sData A buffer for received data.
		/// @param p_nSize Size in bytes of the buffer.
		/// @param p_oFrom Address of the sender.
		/// 
		/// @return Number of bytes received.
		uint32 Receive(char *p_sData, uint32 p_nSize, CNetAddress *p_oFrom);

	private:
		Socket m_hSocket; ///< Socket handle
	};
}

#endif // __CUDP_SOCKET__
