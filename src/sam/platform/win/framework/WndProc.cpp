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
#include "SamFrameworkPCH.h"
#include "WndProc.h"
#include "framework/IFramework.h"

/// @brief Window events callback.
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
		sam::g_Env->pFramework->OnClose();
		break;

	case WM_SIZE:
		if(p_wParam != SIZE_MINIMIZED)
		{
			RECT rect;
			GetClientRect(p_hWnd, &rect);
            sam::g_Env->pFramework->OnSize(rect.right, rect.bottom);
            sam::g_Env->pRenderWindow->SetResolution(rect.right, rect.bottom);
		}
		break;

	case WM_ACTIVATE:
		if(p_wParam == WA_INACTIVE)
		{
			sam::g_Env->pFramework->OnLoseFocus();
		}
		else
		{
			sam::g_Env->pFramework->OnGainFocus();
		}

	default:
		return DefWindowProc(p_hWnd, p_nMessage, p_wParam, p_lParam);
	}

	return 0;
}
