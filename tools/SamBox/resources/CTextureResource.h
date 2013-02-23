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
#ifndef __SAMBOX_TEXTURE_RESOURCE_H__
#define __SAMBOX_TEXTURE_RESOURCE_H__

#include "IResource.h"
#include "exports/TextureExporter.h"

namespace sam
{
	namespace box
	{
		/// @brief Texture resource.
		class CTextureResource : public IResource
		{
		public:
			IMPLEMENT_SERIALIZABLE(CTextureResource, "texture");

			/// @brief Constructor.
			/// 
			/// @param p_sName Resource name.
			/// @param p_sPath Absolute path.
			/// @param p_pBitmap Image handle.
			CTextureResource(const QString &p_sName, const QString &p_sPath, FIBITMAP *p_pBitmap);

			/// @brief Destructor.
			~CTextureResource();

			/// @brief Retrieves type of resource.
			/// 
			/// @return Type of resource.
			EResourceType GetType() const {return e_RT_Texture;}

			/// @brief Load resource.
			/// 
			/// @return True if there is no error.
			bool Load();

			/// @brief Unload resource.
			/// 
			/// @return True if there is no error.
			bool Unload();

			/// @brief Retrieves if resource is loaded.
			/// 
			/// @return True if resource is loaded.
			bool IsLoaded() const {return m_pTexture != NULL;}

			/// @brief Serialize the object
			/// 
			/// @param p_pContext Pointer to the context
			void Read(ISerializer *p_pContext);

			/// @brief Serialize the object
			/// 
			/// @param p_pContext Pointer to the context
			void Write(ISerializer *p_pContext);

			/// @brief
			FIBITMAP *GetBitmap() const {return m_pBitmap;}

		private:
			FIBITMAP *m_pBitmap;  ///< Editor handle.
			CTexture *m_pTexture; ///< Engine handle.			

			STextureMeta m_oMetaData;
		};
	}	
}

#endif // __SAMBOX_TEXTURE_RESOURCE_H__
