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
#include "config.h"
#include "server.h"
#include "client.h"

// Sample application.
class CApplication : public IApplication
{
public:
	CApplication()
		: IApplication("Sample: hello world"), m_pClient(NULL)
	{
	}

	~CApplication()
	{
		m_pClient->Wait();
		delete m_pClient;
	}

	virtual bool PostInit()
	{
		sam::InitNetwork(sam::g_Env);

		bool bIsHost = false;
		char answer[CLIENT_MAX_SIZE_NAME];
		do
		{
			printf("do you want to host (y/n):");
			fgets(answer, CLIENT_MAX_SIZE_NAME, stdin);
			if(answer[0] == 'y')
			{
				printf("***** start the server\n");
				m_oServer.Up();
				m_oServer.Create(4 *1024);
				m_oServer.Start();
				bIsHost = true;
				break;
			}
			else if(answer[0] == 'n')
			{
				break;
			}
		} while (true);
		
				
		printf("what is your name:");
		fgets(answer, CLIENT_MAX_SIZE_NAME, stdin);

		printf("your name is %s\n", answer);
		answer[strlen(answer) - 1] = '\0';
		m_pClient= new Client(answer);
		if(bIsHost)
		{
			m_pClient->Connect("127.0.0.1");
		}
		else
		{
			printf("enter the ip address:");
			fgets(answer, CLIENT_MAX_SIZE_NAME, stdin);

			m_pClient->Connect(answer);
		}
		m_pClient->Create(4 *1024);
		m_pClient->Start();

		return true;
	}

	virtual void Update(f32 p_fDelta)
	{
		m_pClient->PrintInfo();

		if(!m_oServer.IsRunning() && !m_pClient->IsRunning())
		{
			Close();
		}
	}

private:
	Client *m_pClient;
	Server m_oServer;
};

IApplication* CreateApplication()
{
	return new CApplication;
}
