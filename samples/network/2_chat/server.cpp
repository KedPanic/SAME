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
#include "server.h"
#include <conio.h>

static int32 NextClientID = 0;

Server::Server()
{	
}

void Server::Up()
{
	m_oSocket.CreateSocket(true);
	m_oSocket.Bind(SERVER_PORT);
}

void Server::Down()
{
	m_oSocket.Unbind();	
}

int32 Server::Run()
{	
	char sBuffer[sam::MaxDatagramSize];

	sam::CNetAddress oFrom;	
	sam::CBitStream oBitStream;

	char sClientName[CLIENT_MAX_SIZE_NAME];
	//char sClientMessage[CLIENT_MAX_SIZE_MESSAGE];

	while(IsRunning())
	{
		uint32 nBytesReceived = m_oSocket.Receive(sBuffer, sam::MaxDatagramSize, &oFrom);
		if(nBytesReceived)
		{
			oBitStream.Init((uint8*)sBuffer, sam::MaxDatagramSize);

			// retrieves the code.
			uint8 cmdid = oBitStream.ReadByte();
			switch(cmdid)
			{
			case CMD_LOGIN:
				{
					// retrieves client name.
					oBitStream.ReadString(sClientName, CLIENT_MAX_SIZE_NAME);

					// Send a connection message.
					oBitStream.Init((uint8*)sBuffer, sam::MaxDatagramSize);
					oBitStream.WriteByte(CMD_SERVER_MSG);

					char sMessage[CLIENT_MAX_SIZE_NAME + 16];
					memset(sMessage, 0, CLIENT_MAX_SIZE_NAME + 16);
					sprintf(sMessage, "%s is connected", sClientName);
					oBitStream.WriteString(sMessage, CLIENT_MAX_SIZE_NAME + 16);
					SendToClients((char*)oBitStream.GetData(), oBitStream.GetSize(), -1);

					// add the client to the list.
					SClient newClient;
					newClient.address = oFrom;
					m_aClients[NextClientID] = newClient;					

					oBitStream.Init((uint8*)sBuffer, sam::MaxDatagramSize);
					oBitStream.WriteByte(CMD_SERVER_LOGIN);
					oBitStream.WriteInt(NextClientID);
					m_oSocket.Send((char*)oBitStream.GetData(), oBitStream.GetSize(), &oFrom);

					NextClientID++;
				}
				break;

			case CMD_LOGOUT:
				{
					// send a disconnection message.
					int32 nClientID = oBitStream.ReadInt();
					oBitStream.ReadString(sClientName, CLIENT_MAX_SIZE_NAME);

					oBitStream.Init((uint8*)sBuffer, sam::MaxDatagramSize);
					oBitStream.WriteByte(CMD_SERVER_MSG);

					char sMessage[CLIENT_MAX_SIZE_NAME + 16];
					sprintf(sMessage, "%s is disconnected", sClientName);
					oBitStream.WriteString(sMessage, strlen(sMessage));
					SendToClients((char*)oBitStream.GetData(), oBitStream.GetSize(), nClientID);
				}
				break;

			case CMD_MSG:
				{
					int32 nClientID = oBitStream.ReadInt();

					SendToClients((char*)oBitStream.GetData(), nBytesReceived, nClientID);
				}
				break;

			default:
				printf("unknow command %s\n", cmdid);
			}
		}
	}

	return 0;
}

void Server::SendToClients(const char *p_sMessage, uint32 p_nSize, uint32 p_nFrom)
{
	Clients::iterator it = m_aClients.begin(), it_end = m_aClients.end();
	while(it != it_end)
	{
		if(it->first != p_nFrom)
		{
			m_oSocket.Send(p_sMessage, p_nSize, &it->second.address);
		}

		++it;
	}
}
