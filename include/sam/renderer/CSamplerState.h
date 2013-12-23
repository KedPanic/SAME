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
#ifndef __CSAMPLER_STATE__
#define __CSAMPLER_STATE__

#include <renderer/ESamplerState.h>
#include <renderer/EShaderState.h>

namespace sam
{
	struct SAM_RENDERER_API SSamplerStateParams
	{
		ESamplerMagFilter m_eMagFilter;
		ESamplerMinFilter m_eMinFilter;
		ETextureWrap m_eWrapU;
		ETextureWrap m_eWrapV;
		ETextureWrap m_eWrapW;
		f32 m_fMipmapLodBias;
		EComparisonFunc m_eComparisonFunc;
		f32 m_fBorderColor[4];
		uint32 m_nMinLOD;
		uint32 m_nMaxLOD;

		SSamplerStateParams()
			: m_eMagFilter(e_SamplerMagFilter_Linear), 
			m_eMinFilter(e_SamplerMinFilter_Linear),
			m_eWrapU(e_TextureWrap_Clamp),
			m_eWrapV(e_TextureWrap_Clamp),
			m_eWrapW(e_TextureWrap_Clamp),
			m_fMipmapLodBias(0.0f),
			m_eComparisonFunc(e_ComparisonFunc_Never),
			m_nMinLOD(0),
			m_nMaxLOD(0)
		{
			memset(m_fBorderColor, 0, sizeof(m_fBorderColor));
		}
	};
}

#include <renderer/CSamplerStatePlf.h>

#endif // __CSAMPLER_STATE__
