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
		: IApplication("Sample: texturing"), m_pVertexBuffer(NULL), m_pVertexShader(NULL), m_pPixelShader(NULL)
	{

	}

	~CApplication()
	{
		SAM_DELETE m_pVertexBuffer;
	}

	virtual bool PostInit()
	{
		sam::CRenderWindow *pRenderer = sam::g_Env->pRenderWindow;

		// Create triangle.
		m_pVertexBuffer = pRenderer->CreateVertexBuffer();
		sam::SVertexDeclaration oVertexDeclaration[2] = {
			{
				sam::e_VertexSemantic_Position,
				0,
				3,
				sam::e_Type_Float
			},
			{
				sam::e_VertexSemantic_Texture_Coord0,
				12,
				2,
				sam::e_Type_Float
			},
		};
		m_pVertexBuffer->Initialize(oVertexDeclaration, 2, 3);	

		pRenderer->SetVertexBuffer(0, m_pVertexBuffer);

		f32 fVector[15] = {
			0.0f, 0.5f, 0.5f,
			0.5f, 0.0f,
			0.5f, -0.5f, 0.5f,
			1.0f, 1.0f,
			-0.5f, -0.5f, 0.5f,
			0.0f, 1.0f
		};
		m_pVertexBuffer->MapWrite(0, fVector, sizeof(fVector));

		// Create simple shader.
		sam::CFile oFile("../data/shaders/texture.fx");
		m_pVertexShader = pRenderer->CreateVertexShader(&oFile, 0, "VS", "vs_4_0");
		m_pVertexShader->CreateInputLayout(m_pVertexBuffer);

		m_pPixelShader = pRenderer->CreatePixelShader(&oFile, 0, "PS", "ps_4_0");

		// Load texture
		sam::CFile oTextureFile("../data/textures/heart.dds");
		m_pTexture = sam::g_Env->pTextureManager->LoadTexture(&oTextureFile, sam::e_Texture_2D, sam::e_TextureUsage_Default);

		sam::SSamplerStateParams oSamplerStateParams;
		oSamplerStateParams.m_eMagFilter		= sam::e_SamplerMagFilter_Linear;
		oSamplerStateParams.m_eMinFilter		= sam::e_SamplerMinFilter_Linear;
		oSamplerStateParams.m_eWrapU			= sam::e_TextureWrap_Repeat;
		oSamplerStateParams.m_eWrapV			= sam::e_TextureWrap_Repeat;
		oSamplerStateParams.m_eWrapW			= sam::e_TextureWrap_Repeat;
		oSamplerStateParams.m_eComparisonFunc	= sam::e_ComparisonFunc_Never;
		oSamplerStateParams.m_nMinLOD			= 0;
		oSamplerStateParams.m_nMaxLOD			= 16;

		m_pSamplerLinear = sam::g_Env->pRenderWindow->CreateSamplerState(oSamplerStateParams);

		return true;
	}

	virtual void Render()
	{	
		ID3D11ShaderResourceView *pTexture = m_pTexture->GetTexture();

		sam::g_Env->pRenderWindow->SetVertexShader(m_pVertexShader);
		sam::g_Env->pRenderWindow->SetPixelShader(m_pPixelShader);
		//sam::g_Env->pRenderWindow->SetTexture(0, m_pTexture);
		sam::g_Env->pRenderWindow->GetD3DContext()->PSSetShaderResources(0, 1, &pTexture);
		//sam::g_Env->pRenderWindow->GetD3DContext()->PSSetSamplers(0, 1, &m_pSamplerLinear);

		sam::g_Env->pRenderWindow->Draw(3, 0);
	}	

private:
	sam::CVertexBuffer *m_pVertexBuffer;
	sam::CVertexShader *m_pVertexShader;
	sam::CPixelShader *m_pPixelShader;
	sam::CTexture *m_pTexture;
	sam::CSamplerState *m_pSamplerLinear;
};

IApplication* CreateApplication()
{
	return new CApplication;
}
