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
#ifndef __SAMBOX_TEXTURE_RESOURCE__
#define __SAMBOX_TEXTURE_RESOURCE__

#include <resources/IResource.h>

/// @brief A texture resource.
/// 
/// @remarks
///		format supported: PSD, PNG, JPEG, GIF
///		raw format: PNG
class CTextureResource : public IResource
{
public:	
	DEFINE_RESOURCE(CTextureResource, "texture_resource", e_ResourceType_Texture);

	/// @brief Constructor.
	/// 
	/// @param p_sName Resource name.
	/// @param p_sPath Absolute path.
	CTextureResource(const String &p_sName, const String &p_sPath);
	~CTextureResource();
	
	/// @brief Load resource.
	/// 
	/// @return True if there is no error.
	virtual bool Load() override;

	/// @brief Unload resource.
	/// 
	/// @return True if there is no error.
	virtual bool Unload() override;

	/// @brief Serialize the object
	/// 
	/// @param p_pContext Pointer to the context
	virtual void Read(sam::ISerializer *p_pContext) override;

	/// @brief Serialize the object
	/// 
	/// @param p_pContext Pointer to the context
	virtual void Write(sam::ISerializer *p_pContext) override;

	/// @brief Retrieve pointer to the engine texture.
	/// 
	/// @return Pointer to the engine texture or null if not loaded.
	sam::CTexture *GetEngineTexture() const {return m_pEngineTexture;}

	/// @brief Retrieve the metadata.
	/// 
	/// @return The metadata.
	const STextureMetadata &GetMetadata() const {return m_oMetadata;}

	/// @brief Update the metadata.
	/// 
	/// @param p_oMetadata Metadata to copy.
	void SetMetadata(STextureMetadata &p_oMetadata);

private:
	sam::CTexture *m_pEngineTexture; ///< Engine texture resource.

	 STextureMetadata m_oMetadata;
};

#endif // __SAMBOX_TEXTURE_RESOURCE__
