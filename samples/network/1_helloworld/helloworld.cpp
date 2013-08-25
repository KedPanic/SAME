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
#include "IApplication.h"
#include <SamNetwork.h>

#include <iostream>

//////////////////////////////////////////////////////////////////////////
//								SERVER									//
//////////////////////////////////////////////////////////////////////////
class Server : public sam::CThread
{
public:
	Server() {}

	void Init()
	{
		m_oSocket.CreateSocket(true);
		m_oSocket.Bind(54321);
	}

private:
	sam::CUDPSocket m_oSocket;

	int32 Run()
	{
		printf("** Starting server **\n");

		sam::CNetAddress oAddress;
		char sBuffer[sam::MaxDatagramSize];
		while(IsRunning())
		{
			uint32 nBytesReceives = m_oSocket.Receive(sBuffer, sam::MaxDatagramSize, &oAddress);
			if(nBytesReceives)
			{
				printf("server received: %s\n", sBuffer);
				if(strcmp(sBuffer, "Hello") == 0)
				{
					printf("Client connected\n");
					m_oSocket.Send("Welcome", 8, &oAddress);
				}
				else if(strcmp(sBuffer, "Bye") == 0)
				{
					printf("Client disconnected\n");
					m_oSocket.Send("Bye", 4, &oAddress);

					Stop();
				}
			}
		}

		return 0;
	}
};

//////////////////////////////////////////////////////////////////////////
//								CLIENT									//
//////////////////////////////////////////////////////////////////////////
class Client : public sam::CThread
{
public:
	Client(const char *p_sServerAddress) 
		: m_oServerAddress(p_sServerAddress, 54321), m_bConnected(false) 
	{
	}

	void Init()
	{
		m_oSocket.CreateSocket(true);
		m_oSocket.Bind(12345);
	}

private:
	sam::CUDPSocket m_oSocket;
	sam::CNetAddress m_oServerAddress;
	bool m_bConnected;

	int32 Run()
	{
		printf("** Starting client **\n");

		// send a connection request.
		m_oSocket.Send("Hello", 6, &m_oServerAddress);

		sam::CNetAddress oAddress;

		char sBuffer[sam::MaxDatagramSize];
		while(IsRunning())
		{
			uint32 nBytesReceives = m_oSocket.Receive(sBuffer, sam::MaxDatagramSize, &oAddress);
			if(nBytesReceives)
			{
				printf("client received: %s\n", sBuffer);
				if(strcmp(sBuffer, "Welcome") == 0)
				{
					m_bConnected = true;
				}
				else if(strcmp(sBuffer, "Bye") == 0)
				{
					Stop();
				}
			}

			// send a message to the server. Quit to exit.
			if(m_bConnected)
			{
				printf("Say:");
				char clientMsg[100];
				fgets(clientMsg, 99, stdin);
				clientMsg[strlen(clientMsg) - 1] = '\0';
				m_oSocket.Send(clientMsg, strlen(clientMsg) + 1, &m_oServerAddress);

				if(strcmp(clientMsg, "Bye") == 0)
				{
					m_bConnected = false;
				}
			}
		}

		return 0;
	}
};

// Sample application.
class CApplication : public IApplication
{
public:
	CApplication()
		: IApplication("Sample: hello world"), m_oClient("127.0.0.1")
	{
	}

	virtual bool PostInit()
	{
		sam::InitNetwork(sam::g_Env);

		m_oServer.Init();
		m_oServer.Create(4 *1024);
		m_oServer.Start();

		m_oClient.Init();
		m_oClient.Create(4 *1024);
		m_oClient.Start();

		return true;
	}

	virtual void Update(f32 p_fDelta)
	{
		if(!m_oServer.IsRunning() && !m_oClient.IsRunning())
		{
			Close();
		}
	}

private:
	Client m_oClient;
	Server m_oServer;
};

IApplication* CreateApplication()
{
	return new CApplication;
}
