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
#ifndef __CASSET_MANAGER_H__
#define __CASSET_MANAGER_H__

namespace sam
{
	/// @brief Asset manager is used to create/retrieve assets.
	/// 
	/// @remarks
	///		   The assets are stored in a binary package, a zip file 
	///		   or a folder. Storage name are unique. Asset name are
	///		   unique per storage.
	///
	class SAM_FRAMEWORK_API CAssetManager : public IAllocated
	{
	public:
		CAssetManager();
		~CAssetManager();

		CTexture *GetTexture(const char *p_sStorage, const char *p_sName);
		CVertexShader *GetVertexShader(const char *p_sStorage, const char *p_sName);
		CPixelShader *GetPixelShader(const char *p_sStorage, const char *p_sName);
		CMaterial *GetMaterial(const char *p_sStorage, const char *p_sName);
	};
}
#endif // __CASSET_MANAGER_H__
