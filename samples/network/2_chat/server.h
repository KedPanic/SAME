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
#ifndef __SERVER__
#define __SERVER__

enum EServerState
{
	e_ServerState_Down,
	e_ServerState_Up,
};

class Server : public sam::CThread
{
public:
	Server();

	void Up();
	void Down();
	void PrintStats();

private:
	sam::CUDPSocket m_oSocket;
	
	struct SClient
	{
		sam::CNetAddress address;
	};
	typedef std::map<uint32, SClient> Clients;
	Clients m_aClients;

	virtual int32 Run();

	void SendToClients(const char *p_sMessage, uint32 p_nSize, uint32 p_nFrom);
};

#endif // __SERVER__
