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
		: IApplication("Sample: cube"),
		m_pConstantBuffer(NULL),
		m_pVertexBuffer(NULL), m_pIndexBuffer(NULL),
		m_pVertexShader(NULL), m_pPixelShader(NULL)
	{

	}

	~CApplication()
	{
		SAM_DELETE m_pConstantBuffer;
		SAM_DELETE m_pVertexBuffer;
		SAM_DELETE m_pIndexBuffer;
	}

	virtual bool PostInit()
	{
		sam::CRenderWindow *pRenderer = sam::g_Env->pRenderWindow;

		// set perspective view.
		m_oCamera.SetPosition(sam::Vector3(0.0f, 0.0f, 10.0f));
		m_oCamera.LookAt(sam::Vector3(0.0f, 0.0f, 0.0f));
		m_oCamera.SetPerspective(pRenderer->GetWidth(), pRenderer->GetHeight(), 75.0f, 0.1f, 1000.0f);

		// Create constant buffer.
		m_pConstantBuffer = SAM_NEW sam::CConstantBuffer;
		m_pConstantBuffer->Initialize(sizeof(SConstantBuffer));

		// Create cube.
		m_pVertexBuffer = pRenderer->CreateVertexBuffer();
		sam::SVertexDeclaration oVertexDeclaration[2] = {
			{
				sam::e_VertexSemantic_Position,
					0,
					3,
					sam::e_Type_Float
			},
			{
				sam::e_VertexSemantic_Color0,
					12,
					4,
					sam::e_Type_Float
			},
		};

		f32 fVector[] = {
			-1.0f, 1.0f, 1.0f,			// 0
			0.0f, 0.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f,			// 1
			0.0f, 1.0f, 0.0f, 1.0f,

			1.0f, 1.0f, -1.0f,			// 2
			0.0f, 1.0f, 1.0f, 1.0f,

			-1.0f, 1.0f, -1.0f,			// 3
			1.0f, 0.0f, 0.0f, 1.0f,

			-1.0f, -1.0f, 1.0f,		// 4
			1.0f, 0.0f, 1.0f, 1.0f,

			1.0f, -1.0f, 1.0f,			// 5
			1.0f, 1.0f, 0.0f, 1.0f,

			1.0f, -1.0f, -1.0f,			// 6
			1.0f, 1.0f, 1.0f, 1.0f,

			-1.0f, -1.0f, -1.0f,			// 7
			0.0f, 0.0f, 0.0f, 1.0f,
		};
		m_pVertexBuffer->Initialize(oVertexDeclaration, sizeof(oVertexDeclaration) / sizeof(sam::SVertexDeclaration), 8);			
		m_pVertexBuffer->MapWrite(0, fVector, sizeof(fVector));
		sam::g_Env->pRenderWindow->SetVertexBuffer(0, m_pVertexBuffer);

		uint16 indices[] =
		{
			3,1,0,
			2,1,3,

			0,5,4,
			1,5,0,

			3,4,7,
			0,4,3,

			1,6,5,
			2,6,1,

			2,7,6,
			3,7,2,

			6,4,5,
			7,4,6,
		};
		m_pIndexBuffer = SAM_NEW sam::CIndexBuffer;
		m_pIndexBuffer->Initialize(indices, sizeof(indices) / sizeof(uint16));
		sam::g_Env->pRenderWindow->SetIndexBuffer(m_pIndexBuffer);

		// Create simple shader.
		sam::CFile oFile("../data/shaders/cube.fx");
		m_pVertexShader = pRenderer->CreateVertexShader(&oFile, 0, "VS", "vs_4_0");
		m_pVertexShader->CreateInputLayout(m_pVertexBuffer);

		m_pPixelShader = pRenderer->CreatePixelShader(&oFile, 0, "PS", "ps_4_0");

		return true;
	}

	virtual void Update(f32 p_fDelta)
	{
		static float rotation = 0.0f;

		// Update the rotation variable each frame.
		rotation += PI * p_fDelta;
		if(rotation > 360.0f)
		{
			rotation -= 360.0f;
		}

		m_mWorld.m00 = cos(rotation);
		m_mWorld.m02 = -sin(rotation);
		m_mWorld.m20 = sin(rotation);
		m_mWorld.m22 = cos(rotation);
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
		
		sam::g_Env->pRenderWindow->SetVertexShader(m_pVertexShader);
		sam::g_Env->pRenderWindow->SetConstantBuffer(m_pConstantBuffer);
		sam::g_Env->pRenderWindow->SetPixelShader(m_pPixelShader);

		sam::g_Env->pRenderWindow->DrawIndexed(36);
	}

private:
	sam::CConstantBuffer *m_pConstantBuffer;
	sam::CVertexShader *m_pVertexShader;
	sam::CPixelShader *m_pPixelShader;
	sam::CTexture *m_pTexture;
	sam::CSamplerState *m_pSamplerLinear;
	sam::CVertexBuffer *m_pVertexBuffer;
	sam::CIndexBuffer *m_pIndexBuffer;

	struct SConstantBuffer
	{
		sam::Matrix44 m_mWorld;
		sam::Matrix44 m_mView;
		sam::Matrix44 m_mProjection;
	};

	sam::CCamera m_oCamera;
};

IApplication* CreateApplication()
{
	return new CApplication;
}
