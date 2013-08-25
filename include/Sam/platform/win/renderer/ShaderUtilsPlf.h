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
#ifndef __SHADER_UTIL_PLF__
#define __SHADER_UTIL_PLF__

namespace sam
{
    extern bool CompileShader(void *p_pData, uint32 p_nSize, const char *p_sFuncName, const char *p_sProfile, ID3DBlob **p_ppBlob);

	/// @brief Retrieves dx11 comparison function.
	/// 
	/// @param p_eComparisonFunc Sam Engine comparison function.
	/// 
	/// @return Dx11 comparison function.
	extern D3D11_COMPARISON_FUNC GetComparaisonFunc(EComparisonFunc p_eComparisonFunc);
}

#endif // __SHADER_UTIL_PLF__
