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
#include <SamCommon.h>
#include <SamRenderer.h>
#include <common/SamModuleInit.h>

using namespace sam;

static bool s_bClose = false;

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
		s_bClose = true;
		break;

	case WM_SIZE:
		if(p_wParam != SIZE_MINIMIZED)
		{
			RECT rect;
			GetClientRect(p_hWnd, &rect);
			g_Env->pRenderWindow->SetResolution(rect.right, rect.bottom);
		}
		break;

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
//////////////////////////////////////////////////////////////////////////

static CVertexBuffer *s_pVertexBuffer = NULL;
static CVertexShader *s_pVertexShader = NULL;
static CPixelShader *s_pPixelShader = NULL;
void Initialize()
{
	// Init common module.
	Env *pEnv = InitCommon();
	ModuleInit(pEnv);

	pEnv->pLog->SetFilename("samengine.log");

	// Create and setup window.
	CRenderWindow *pRenderer = CreateRenderManager(pEnv);

	pRenderer->SetWndProc(& WndProc);
	pRenderer->Create("Sample: basic", 800, 600, 24, 24, 8, 1, false);
	pRenderer->SetClearColor(0.0f, 0.0f, 0.8f, 1.0f);
	pRenderer->ShowMouseCursor(true);

	// Create triangle.
	s_pVertexBuffer = g_Env->pRenderWindow->CreateVertexBuffer();
	SVertexDeclaration oVertexDeclaration;
	oVertexDeclaration.m_eSemantic = e_VertexSemantic_Position;
	oVertexDeclaration.m_eType = e_Type_Float;
	oVertexDeclaration.m_nNbComponents = 3;
	oVertexDeclaration.m_nOffset = 0;
	s_pVertexBuffer->Initialize(&oVertexDeclaration, 1, 3);	

	g_Env->pRenderWindow->SetVertexBuffer(0, s_pVertexBuffer);

	f32 fVector[9] = {
		0.0f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f
	};
	s_pVertexBuffer->MapWrite(0, fVector, sizeof(fVector));

	// Create simple shader.
	CFile oFile("../data/shaders/simple.fx");
	s_pVertexShader = pRenderer->CreateVertexShader(&oFile, 0, "VS", "vs_4_0");
	s_pVertexShader->CreateInputLayout(s_pVertexBuffer);

	s_pPixelShader = pRenderer->CreatePixelShader(&oFile, 0, "PS", "ps_4_0");
}

void Shutdown()
{
	SAM_DELETE s_pVertexBuffer;
	DestroyRenderManager();
	ShutdownCommon();
}

#if defined(SAM_PLATFORM_WIN)
int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
#else
int main()
#endif
{ 
	Initialize();
	
	MSG msg;
	while(!s_bClose)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}
		else
		{
			g_Env->pRenderWindow->BeginScene(EClearType_Color);			
			
			g_Env->pRenderWindow->SetVertexShader(s_pVertexShader);
			g_Env->pRenderWindow->SetPixelShader(s_pPixelShader);
			
			g_Env->pRenderWindow->Draw(3, 0);

			g_Env->pRenderWindow->EndScene();
		}
	}

	Shutdown();

	return 0;
}