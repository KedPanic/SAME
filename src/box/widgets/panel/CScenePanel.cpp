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
#include "SamBoxPCH.h"
#include "widgets/panel/CScenePanel.h"

CScenePanel::CScenePanel(wxWindow *p_pParent)
{
	wxXmlResource::Get()->LoadObject(this, p_pParent, wxT("CScenePanel"), wxT("wxPanel"));

	Initialize();

	Bind(wxEVT_PAINT, &CScenePanel::OnPaint, this);
}

void CScenePanel::Initialize()
{
	wxPanel *pRenderer = (wxPanel*)FindWindowById(XRCID("ID_PANEL_RENDERER"));
	
	int nWidth, nHeight;
	GetSize(&nWidth, &nHeight);

	sam::g_Env->pRenderWindow = sam::CreateRenderManager(sam::g_Env);

	sam::g_Env->pRenderWindow->Create(pRenderer->GetHWND(), 1920, 1080, 24, 24, 8, 1);
	sam::g_Env->pRenderWindow->SetClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	sam::g_Env->pRenderWindow->SetViewport(0, 0, nWidth, nHeight);
}

void CScenePanel::OnPaint(wxPaintEvent &p_oEvent)
{
	sam::g_Env->pRenderWindow->BeginScene(sam::e_ClearType_Color);
	sam::g_Env->pRenderWindow->EndScene();
}