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
		m_pVertexShader(NULL), m_pPixelShader(NULL),
		m_pScene(NULL),
		m_pCameraNode(NULL),
		m_pMeshNode(NULL),
		m_pMesh(NULL)
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

		// Create scene.
		m_pScene = SAM_NEW sam::scene::CScene;
		m_pScene->Initialize();

		// Create camera.
		m_pCameraNode = m_pScene->CreateCamera();
		m_pCameraNode->m_pTransform->SetPosition(sam::Vector3(0.0f, 0.0f, 10.0f));
		m_pCameraNode->m_pTransform->LookAt(sam::Vector3::zero);

		// Create mesh.
		sam::CFile oMeshFile;
		oMeshFile.Open("../data/meshs/monkey.mesh");

		m_pMeshNode = m_pScene->CreateMesh();
		m_pMeshNode->m_pTransform->SetPosition(sam::Vector3(0.0f, 0.0f, 0.0f));
		sam::scene::CMesh *pMeshComponent = m_pMeshNode->GetComponent<sam::scene::CMesh>();
		pMeshComponent->LoadMesh(oMeshFile.Data(), oMeshFile.Size());
		m_pMesh = pMeshComponent->GetMesh();
		sam::g_Env->pRenderWindow->SetVertexBuffer(0, m_pMesh->GetVertexBuffer());
		sam::g_Env->pRenderWindow->SetIndexBuffer(m_pMesh->GetIndexBuffer());

		// Create constant buffer.
		m_pConstantBuffer = SAM_NEW sam::CConstantBuffer;
		m_pConstantBuffer->Initialize(sizeof(SConstantBuffer));

		// Create simple shader.
		sam::CFile oFile("../data/shaders/mesh.fx");
		m_pVertexShader = pRenderer->CreateVertexShader(&oFile, 0, "VS", "vs_4_0");
		m_pVertexShader->CreateInputLayout(m_pMesh->GetVertexBuffer());

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
		sam::scene::CCamera *pCamera = m_pCameraNode->GetComponent<sam::scene::CCamera>();

		// write constant buffer.
		SConstantBuffer oConstantBuffer;
		oConstantBuffer.m_mWorld = m_mWorld;	
		oConstantBuffer.m_mView = pCamera->GetViewMatrix();
		oConstantBuffer.m_mProjection = pCamera->GetProjectionMatrix();
		m_pConstantBuffer->MapWrite(&oConstantBuffer, sizeof(SConstantBuffer));
		
		sam::g_Env->pRenderWindow->SetVertexShader(m_pVertexShader);
		sam::g_Env->pRenderWindow->SetConstantBuffer(m_pConstantBuffer);
		sam::g_Env->pRenderWindow->SetPixelShader(m_pPixelShader);

		sam::g_Env->pRenderWindow->DrawIndexed(m_pMesh->GetIndexBuffer()->GetNbIndices());
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

	sam::scene::CScene *m_pScene;
	sam::scene::CGameObject *m_pCameraNode;
	sam::scene::CGameObject *m_pMeshNode;
	sam::CMesh *m_pMesh;
};

IApplication* CreateApplication()
{
	return new CApplication;
}
