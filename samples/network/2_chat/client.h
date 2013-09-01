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
#ifndef __CLIENT__
#define __CLIENT__

enum EClientState
{
	e_ClientState_Disconnected,
	e_ClientState_Connecting,
	e_ClientState_Connected,
};

class Client : public sam::CThread
{
public:
	Client(const char *p_sClientName);

	void Connect(const char* p_sServerAddress);
	void Disconnect();

	void SendMessage(const char* p_sMessage);

	void PrintInfo();

private:
	int32 m_nClientID;
	sam::CUDPSocket m_oSocket;
	sam::CNetAddress m_oServerAddress;
	EClientState m_eClientState;
	char m_sClientName[CLIENT_MAX_SIZE_NAME];

	typedef std::list<Client> Clients;
	Clients m_aClientList; ///< The other clients.

	virtual int32 Run();
};

#endif // __CLIENT__
