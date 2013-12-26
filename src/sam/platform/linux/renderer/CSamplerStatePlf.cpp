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
#include "SamRendererPCH.h"
#include "renderer/CSamplerState.h"
#include "renderer/ShaderUtilsPlf.h"
#include "renderer/CRenderWindow.h"

namespace sam
{
	static D3D11_FILTER s_aSamplerFilter[] = {
		D3D11_FILTER_MIN_MAG_MIP_POINT,					// e_SamplerMagFilter_Point  + e_SamplerMinFilter_Point				= 0
		D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,	// e_SamplerMagFilter_Point  + e_SamplerMinFilter_Linear			= 1
		D3D11_FILTER_MIN_MAG_MIP_POINT,					// e_SamplerMagFilter_Point  + e_SamplerMinFilter_Point_Mip_Point	= 2
		D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT,			// e_SamplerMagFilter_Point  + e_SamplerMinFilter_Linear_Mip_Point	= 3
		D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR,			// e_SamplerMagFilter_Point  + e_SamplerMinFilter_Point_Mip_Linear  = 4		
		D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,	// e_SamplerMagFilter_Point  + e_SamplerMinFilter_Linear_Mip_Linear	= 5

		D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,	// e_SamplerMagFilter_Linear + e_SamplerMinFilter_Point				= 6
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,				// e_SamplerMagFilter_Linear + e_SamplerMinFilter_Linear			= 7
		D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,	// e_SamplerMagFilter_Linear + e_SamplerMinFilter_Point_Mip_Point	= 8				
		D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,			// e_SamplerMagFilter_Linear + e_SamplerMinFilter_Linear_Mip_Point	= 9
		D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR,			// e_SamplerMagFilter_Linear + e_SamplerMinFilter_Point_Mip_Linear	= 10
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,				// e_SamplerMagFilter_Linear + e_SamplerMinFilter_Linear_Mip_Linear	= 11
	};

	static D3D11_TEXTURE_ADDRESS_MODE s_aSamplerWrap[] = {
		D3D11_TEXTURE_ADDRESS_MIRROR,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_CLAMP
	};

	CSamplerState::CSamplerState()
		: m_pSamplerState(NULL)
	{

	}

	CSamplerState::~CSamplerState()
	{
		if(m_pSamplerState)
		{
			m_pSamplerState->Release();
			m_pSamplerState = NULL;
		}
	}

	// Create the sampler state.
	void CSamplerState::Initialize(const SSamplerStateParams &p_oSamplerStateParams)
	{
		D3D11_SAMPLER_DESC oSamplerDesc;
		ZeroMemory(&oSamplerDesc, sizeof(oSamplerDesc));
		uint32 nIndex = (p_oSamplerStateParams.m_eMagFilter * 6) + p_oSamplerStateParams.m_eMinFilter;
		oSamplerDesc.Filter = s_aSamplerFilter[nIndex];
		oSamplerDesc.AddressU = s_aSamplerWrap[p_oSamplerStateParams.m_eWrapU];
		oSamplerDesc.AddressV = s_aSamplerWrap[p_oSamplerStateParams.m_eWrapV];
		oSamplerDesc.AddressW = s_aSamplerWrap[p_oSamplerStateParams.m_eWrapW];
		oSamplerDesc.ComparisonFunc = GetComparaisonFunc(p_oSamplerStateParams.m_eComparisonFunc);
		memcpy(oSamplerDesc.BorderColor, p_oSamplerStateParams.m_fBorderColor, sizeof(f32) * 4);
		oSamplerDesc.MipLODBias = p_oSamplerStateParams.m_fMipmapLodBias;
		oSamplerDesc.MinLOD = (f32)p_oSamplerStateParams.m_nMinLOD;
		oSamplerDesc.MaxLOD = (f32)p_oSamplerStateParams.m_nMaxLOD;
		oSamplerDesc.MaxAnisotropy = 0;

		g_Env->pRenderWindow->GetD3DDevice()->CreateSamplerState(&oSamplerDesc, &m_pSamplerState);
	}
		
	// Retrieves the Dx11 sampler state context.
	ID3D11SamplerState *CSamplerState::GetSamplerState() const
	{
		SAM_ASSERT(m_pSamplerState != NULL, "Sampler state is not initialized");

		return m_pSamplerState;
	}
}
