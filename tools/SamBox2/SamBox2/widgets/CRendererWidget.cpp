//===========================================
// Copyright (C) 2013-2014 Stone Age Machine
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
#include "CRendererWidget.h"

#include <QResizeEvent>

#include "SamBox.h"
#include "CEngineThread.h"

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

sam::Matrix44 m_mWorld;


void CEngineThread::run()
{
    while(true)
    {
        if(m_bResolutionChanged)
        {
            //sam::g_Env->pRenderWindow->SetResolution(m_nWidth, m_nHeight);
            sam::g_Env->pRenderWindow->SetViewport(0, 0, m_nWidth, m_nHeight);
            m_bResolutionChanged = false;
        }

        sam::g_Env->m_pComponentManager->Update(0.0f);

        static float rotation = 0.0f;
        rotation += PI * 0.0001f;
                if(rotation > 360.0f)
                {
                    rotation -= 360.0f;
                }

                m_mWorld.m00 = cos(rotation);
                m_mWorld.m02 = -sin(rotation);
                m_mWorld.m20 = sin(rotation);
                m_mWorld.m22 = cos(rotation);

        sam::g_Env->pRenderWindow->SetClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        sam::g_Env->pRenderWindow->BeginScene(sam::e_ClearType_Color | sam::e_ClearType_Depth | sam::e_ClearType_Stencil);

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

        sam::g_Env->pRenderWindow->EndScene();
    }
}


CRendererWidget::CRendererWidget(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_NativeWindow, true);

    CreateDevice();

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
    m_pVertexShader = sam::g_Env->pRenderWindow->CreateVertexShader(&oFile, 0, "VS", "vs_4_0");
    m_pVertexShader->CreateInputLayout(m_pMesh->GetVertexBuffer());

    m_pPixelShader = sam::g_Env->pRenderWindow->CreatePixelShader(&oFile, 0, "PS", "ps_4_0");


    m_pEngineThread->start();
}

void CRendererWidget::resizeEvent(QResizeEvent *p_pEvent)
{
    m_pEngineThread->SetResolution(p_pEvent->size().width(), p_pEvent->size().height());
}

void CRendererWidget::paintEvent(QPaintEvent *p_pEvent)
{

}

void CRendererWidget::CreateDevice()
{
    sam::g_Env->pRenderWindow->Create((sam::SAM_HWND)winId(), 1920, 1080, 24, 24, 8, 1);
    sam::g_Env->pRenderWindow->SetViewport(0, 0, 1920, 1080);

    m_pEngineThread = new CEngineThread();
}
