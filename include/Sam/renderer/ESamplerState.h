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
#ifndef __ESAMPLER_STATE__
#define __ESAMPLER_STATE__

namespace sam
{
	/// @enum Texture sampler wrapping modes.
	enum ESamplerWrap
	{
		e_SamplerWrap_Mirror,
		e_SamplerWrap_Repeat,
		e_SamplerWrap_Clamp,
	};

	/// @enum Texture sampler magnification filter.
	enum ESamplerMagFilter
	{
		e_SamplerMagFilter_Point,
		e_SamplerMagFilter_Linear
	};

	/// @enum Texture sampler minification filter.
	enum ESamplerMinFilter
	{	
		e_SamplerMinFilter_Point,
		e_SamplerMinFilter_Linear,
		e_SamplerMinFilter_Point_Mip_Point,
		e_SamplerMinFilter_Linear_Mip_Point,
		e_SamplerMinFilter_Point_Mip_Linear,
		e_SamplerMinFilter_Linear_Mip_Linear,
	};

	/// @enum Texture sampler type of filtering.
	enum ESamplerFilterType
	{
		e_SamplerFilterType_Point,
		e_SamplerFilterType_Linear,
	};
}

#endif // __ESAMPLER_STATE__
