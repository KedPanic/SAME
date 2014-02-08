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

// Sample application.
class CApplication : public IApplication
{
public:
	CApplication()
		: IApplication("Sample: Triangle"), m_pConstantBuffer(NULL), m_pVertexBuffer(NULL), m_pVertexShader(NULL), m_pPixelShader(NULL)
	{

	}

	~CApplication()
	{
		SAM_DELETE m_pConstantBuffer;
		SAM_DELETE m_pVertexBuffer;
	}

	virtual bool PostInit()
	{		
		sam::CRenderWindow *pRenderer = sam::g_Env->pRenderWindow;

		// set perspective view.		
		m_oCamera.LookAt(sam::Vector3(0.0f, 0.0f, 10.0f), sam::Vector3(0.0f, 0.0f, 0.0f), sam::Vector3(0.0f, 1.0f, 0.0f));
		m_oCamera.SetPerspective(pRenderer->GetWidth(), pRenderer->GetHeight(), 45.0f, 0.1f, 1000.0f);

		// Create constant buffer.
		m_pConstantBuffer = SAM_NEW sam::CConstantBuffer;
		m_pConstantBuffer->Initialize(sizeof(SConstantBuffer));

		// Create triangle.
		m_pVertexBuffer = pRenderer->CreateVertexBuffer();
		sam::SVertexDeclaration oVertexDeclaration;
		oVertexDeclaration.m_eSemantic = sam::e_VertexSemantic_Position;
		oVertexDeclaration.m_eType = sam::e_Type_Float;
		oVertexDeclaration.m_nNbComponents = 3;
		oVertexDeclaration.m_nOffset = 0;
		m_pVertexBuffer->Initialize(&oVertexDeclaration, 1, 3);	

		pRenderer->SetVertexBuffer(0, m_pVertexBuffer);

		f32 fVector[] = {
			0.0f, 1.0f, 0.f,
			-1.0f, -1.0f, 0.f,			
			1.0f, -1.0f, 0.f,
		};
		m_pVertexBuffer->MapWrite(0, fVector, sizeof(fVector));

		// Create simple shader.
		sam::CFile oFile("../data/shaders/simple.fx");
		m_pVertexShader = pRenderer->CreateVertexShader(&oFile, 0, "VS", "vs_4_0");
		m_pVertexShader->CreateInputLayout(m_pVertexBuffer);

		m_pPixelShader = pRenderer->CreatePixelShader(&oFile, 0, "PS", "ps_4_0");

		return true;
	}

	virtual void Render()
	{
		// write constant buffer.
		sam::Matrix44 mView;
		m_oCamera.GetViewMatrix(mView);

		SConstantBuffer oConstantBuffer;
		oConstantBuffer.m_mWorld = m_mWorld;	
		oConstantBuffer.m_mView = mView;
		oConstantBuffer.m_mProjection = m_oCamera.GetProjectionMatrix();
		m_pConstantBuffer->MapWrite(&oConstantBuffer, sizeof(SConstantBuffer));

		// draw triangle.
		sam::g_Env->pRenderWindow->SetVertexShader(m_pVertexShader);
		sam::g_Env->pRenderWindow->SetConstantBuffer(m_pConstantBuffer);
		sam::g_Env->pRenderWindow->SetPixelShader(m_pPixelShader);

		sam::g_Env->pRenderWindow->Draw(3, 0);
	}	

private:
	sam::CConstantBuffer *m_pConstantBuffer;
	sam::CVertexBuffer *m_pVertexBuffer;
	sam::CVertexShader *m_pVertexShader;
	sam::CPixelShader *m_pPixelShader;

	struct SConstantBuffer
	{
		sam::Matrix44 m_mWorld;
		sam::Matrix44 m_mView;
		sam::Matrix44 m_mProjection;
	};	
};

IApplication* CreateApplication()
{
	return new CApplication;
}
