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
#include <common/SamModuleInit.h>

IApplication *g_pApp = NULL; // global used to send close event.

#if defined(SAM_PLATFORM_WIN)
//////////////////////////////////////////////////////////////////////////
// Windows stuff
//////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND p_hWnd, UINT p_nMessage, WPARAM p_wParam, LPARAM p_lParam)
{
	PAINTSTRUCT paintStruct;
	HDC hdc;

	switch(p_nMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(p_hWnd, &paintStruct);
		EndPaint(p_hWnd, &paintStruct);
		break;

	case WM_DESTROY:
	case WM_CLOSE:
		g_pApp->Close();
		break;

#if !defined(CONSOLE_APP)
	case WM_SIZE:
		if(p_wParam != SIZE_MINIMIZED)
		{
			RECT rect;
			GetClientRect(p_hWnd, &rect);
			sam::g_Env->pRenderWindow->SetResolution(rect.right, rect.bottom);
		}
		break;
#endif

	case WM_ACTIVATE:
		if(p_wParam == WA_INACTIVE)
		{

		}
		else
		{

		}

	default:
		return DefWindowProc(p_hWnd, p_nMessage, p_wParam, p_lParam);
	}

	return 0;
}
#endif

IApplication::IApplication(const char* p_sTitle)
	: m_bRun(false)
{
	m_sTitle = new char[strlen(p_sTitle)];
	strcpy(m_sTitle, p_sTitle);

	g_pApp = this;
}

IApplication::~IApplication()
{

}


// Initialize common and renderer module.
// Create the window.
bool IApplication::Initialize()
{
	// Init common module (log, memory tracker)
	sam::Env *pEnv = sam::InitCommon();
	sam::ModuleInit(pEnv);

	sam::g_Env->pLog->SetFilename("samengine.log");

#if defined(CONSOLE_APP)
	return PostInit();
#else
	// Create and setup window.
	sam::CreateRenderManager(pEnv);

	sam::g_Env->pRenderWindow->SetWndProc(& WndProc);
	if(sam::g_Env->pRenderWindow->Create(m_sTitle, 800, 600, 24, 24, 8, 1, false))
	{
		sam::g_Env->pRenderWindow->SetClearColor(0.0f, 0.0f, 0.8f, 1.0f);
		sam::g_Env->pRenderWindow->ShowMouseCursor(true);

		return PostInit();
	}
#endif

	return false;
}

void IApplication::Shutdown()
{
#if !defined(CONSOLE_APP)
	sam::DestroyRenderManager();
#endif
	sam::ShutdownCommon();
}

// Main loop.
// Clean screen, call render method.
void IApplication::Run()
{
	m_bRun = true;

#if defined(SAM_PLATFORM_WIN)
	MSG msg;
#endif

	while(m_bRun)
	{
#if defined(SAM_PLATFORM_WIN)
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}
		else
#endif
		{
			Update(0.0f);

#if !defined(CONSOLE_APP)
			sam::g_Env->pRenderWindow->BeginScene(sam::EClearType_Color | sam::EClearType_Depth | sam::EClearType_Stencil);

			Render();

			sam::g_Env->pRenderWindow->EndScene();
#endif
		}		
	}
}

#if defined(SAM_PLATFORM_WIN) && !defined(CONSOLE_APP)
int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
#else
int main(int argc, char **argv)
#endif
{ 	
	g_pApp = CreateApplication();

	if(g_pApp->Initialize())
	{
		g_pApp->Run();
	}	

	return 0;
}