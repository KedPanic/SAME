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
#include "config.h"
#include "client.h"

#if defined(SAM_PLATFORM_WIN)
inline void gotoxy(short p_nX, short p_nY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD oCoord;
	oCoord.X = p_nX;
	oCoord.Y = p_nY;
	SetConsoleCursorPosition(hStdout, oCoord);
}
#endif

//////////////////////////////////////////////////////////////////////////
class Messenger: public sam::CThread
{
public:
	Messenger(Client *p_pClient)
		: m_pClient(p_pClient)
	{

	}

private:
	Client *m_pClient;

	virtual int32 Run()
	{
		while(IsRunning())
		{
			printf("you:");
			char message[CLIENT_MAX_SIZE_MESSAGE];
			fgets(message, CLIENT_MAX_SIZE_MESSAGE, stdin);
			m_pClient->SendMessage(message);
		}

		return 0;
	}
};
Messenger *g_pMessage;

static char s_sBuffer[sam::MaxDatagramSize];

Client::Client(const char *p_sClientName)
	: m_nClientID(-1)
{
	SAM_ASSERT(strlen(p_sClientName) < CLIENT_MAX_SIZE_NAME, "Client name is too long");
	strcpy(m_sClientName, p_sClientName);

	m_oSocket.CreateSocket(true);
	m_oSocket.Bind(CLIENT_PORT);

	g_pMessage = NULL;
}

void Client::Connect(const char* p_sServerAddress)
{
	m_oServerAddress.SetIp(p_sServerAddress);
	m_oServerAddress.SetPort(SERVER_PORT);

	sam::CBitStream oMessage;
	oMessage.Init((uint8*)s_sBuffer, sam::MaxDatagramSize);
	oMessage.WriteByte(CMD_LOGIN);
	oMessage.WriteString(m_sClientName, CLIENT_MAX_SIZE_NAME);

	m_oSocket.Send((const char*)oMessage.GetData(), oMessage.GetSize(), &m_oServerAddress);

	g_pMessage = new Messenger(this);
	g_pMessage->Create(4 * 1024);
	g_pMessage->Start();
}

void Client::Disconnect()
{
	g_pMessage->Stop();
	g_pMessage->Wait();
	delete g_pMessage;

	sam::CBitStream oMessage;
	oMessage.Init((uint8*)s_sBuffer, sam::MaxDatagramSize);
	oMessage.WriteByte(CMD_LOGOUT);
	oMessage.WriteInt(m_nClientID);

	m_oSocket.Send((const char*)oMessage.GetData(), oMessage.GetSize(), &m_oServerAddress);
}

void Client::SendMessage(const char* p_sMessage)
{	
	SAM_ASSERT(strlen(p_sMessage) < CLIENT_MAX_SIZE_MESSAGE, "Client message is too long");
	static char s_sMessage[CLIENT_MAX_SIZE_MESSAGE];
	strcpy(s_sMessage, p_sMessage);

	sam::CBitStream oMessage;
	oMessage.Init((uint8*)s_sBuffer, sam::MaxDatagramSize);
	oMessage.WriteByte(CMD_MSG);
	oMessage.WriteInt(m_nClientID);
	oMessage.WriteString(m_sClientName, CLIENT_MAX_SIZE_NAME);
	oMessage.WriteString(s_sMessage,    CLIENT_MAX_SIZE_MESSAGE);

	m_oSocket.Send((const char*)oMessage.GetData(), oMessage.GetSize(), &m_oServerAddress);
}

void Client::PrintInfo()
{
	//gotoxy(50, 5);
	//printf("Server:%s\n", m_oServerAddress.ToString());
}

int32 Client::Run()
{
	char sClientName[CLIENT_MAX_SIZE_NAME];
	char sClientMessage[CLIENT_MAX_SIZE_MESSAGE];
	char sBuffer[sam::MaxDatagramSize];

	sam::CNetAddress oFrom;	
	sam::CBitStream oBitStream;	

	while(IsRunning())
	{
		uint32 nBytesReceived = m_oSocket.Receive(sBuffer, sam::MaxDatagramSize, &oFrom);
		if(nBytesReceived)
		{
			if(oFrom.GetIp() != m_oServerAddress.GetIp())
			{
				printf("Received a message from bad peer\n");
			}
			else
			{
				oBitStream.Init((uint8*)sBuffer, sam::MaxDatagramSize);

				// retrieves the code.
				uint8 cmdid = oBitStream.ReadByte();
				switch(cmdid)
				{
				case CMD_SERVER_LOGIN:
					{
						m_nClientID = oBitStream.ReadInt();
					}
					break;

				case CMD_SERVER_LOGOUT:
					{

					}
					break;

				case CMD_SERVER_MSG:
					{
						oBitStream.ReadString(sClientMessage, CLIENT_MAX_SIZE_MESSAGE);
						printf("%s\n", sClientMessage);
					}
					break;

				case CMD_MSG:
					{
						oBitStream.ReadInt();
						oBitStream.ReadString(sClientName, CLIENT_MAX_SIZE_NAME);
						oBitStream.ReadString(sClientMessage, CLIENT_MAX_SIZE_MESSAGE);

						printf("%s: %s\n", sClientName, sClientMessage);
					}
					break;

				default:
					printf("unknow command %s\n", cmdid);
				}
			}
		}
	}

	return 0;
}
