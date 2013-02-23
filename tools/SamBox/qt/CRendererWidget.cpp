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
#include "qt/CRendererWidget.h"

namespace sam
{
	namespace box
	{
		namespace qt
		{
			CPixelShader *pPixelFX = NULL;
			CVertexShader *pVertexFX = NULL;
			CVertexBuffer *pBuffer = NULL;
			CRendererWidget::CRendererWidget(QWidget* p_pParent /*= NULL*/)
				: QWidget(p_pParent)
			{
				setAttribute(Qt::WA_PaintOnScreen, true);
				setAttribute(Qt::WA_NativeWindow, true);
			}

			CRendererWidget::~CRendererWidget()
			{
			}

			void CRendererWidget::Initialize()
			{
				g_Env->pRenderWindow->Create((SAM_HWND)winId(), 1920, 1080, 24, 24, 8, 1);
				g_Env->pRenderWindow->SetClearColor(1.0f, 0.0f, 0.0f, 1.0f);
				g_Env->pRenderWindow->SetViewport(0, 0, width(), height());

				CFile oFile("test.fx");
				ID nID = CreateID("test.fx", 7);
				pPixelFX = g_Env->pRenderWindow->CreatePixelShader(&oFile, nID, "PS", "ps_4_0");
				pVertexFX = g_Env->pRenderWindow->CreateVertexShader(&oFile, nID, "VS", "vs_4_0");

				pBuffer = g_Env->pRenderWindow->CreateVertexBuffer();

				SVertexDeclaration oVertexDeclaration = {
					VS_Position,
					0,
					3,
					TI_Float
				};
				pBuffer->Initialize(&oVertexDeclaration, 1, 3);

				float fVector[9] = {
					0.0f, 0.5f, 0.5f,
					0.5f, -0.5f, 0.5f,
					-0.5f, -0.5f, 0.5f
				};
				pBuffer->MapWrite(0, fVector, sizeof(fVector));
			}

			void CRendererWidget::resizeEvent(QResizeEvent*)
			{
				g_Env->pRenderWindow->SetResolution(width(), height());
				g_Env->pRenderWindow->SetViewport(0, 0, width(), height());
			}

			void CRendererWidget::paintEvent(QPaintEvent*)
			{
				g_Env->pRenderWindow->BeginScene(EClearType_Color);

				g_Env->pRenderWindow->SetVertexShader(pVertexFX);
				g_Env->pRenderWindow->SetPixelShader(pPixelFX);
				g_Env->pRenderWindow->SetVertexBuffer(0, pBuffer);
				g_Env->pRenderWindow->Draw(3, 0);

				g_Env->pRenderWindow->EndScene();
			}
		}
	}
}
