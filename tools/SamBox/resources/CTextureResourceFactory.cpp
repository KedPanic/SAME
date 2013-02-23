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
#include "SamBoxPCH.h"
#include "CTextureResourceFactory.h"
#include "CTextureResource.h"

#include "resources/IResourceFactory.h"

namespace sam
{
	namespace box
	{
		CTextureResourceFactory::CTextureResourceFactory()
		{
		}

		// Initialize it !
		bool CTextureResourceFactory::Initialize()
		{
			FreeImage_Initialise();

			return true;
		}

		// Shutdown it !
		void CTextureResourceFactory::Shutdown()
		{
			FreeImage_DeInitialise();
		}

		// Import the resource.
		IResource *CTextureResourceFactory::Import(const QString &p_sSourcePath)
		{
			QByteArray sPath = p_sSourcePath.toLocal8Bit();

			// get file format.
			FREE_IMAGE_FORMAT eFIF = FreeImage_GetFileType(sPath.data());
			if(eFIF == FIF_UNKNOWN)
			{
				eFIF = FreeImage_GetFIFFromFilename(sPath.data());
			}

			// texture creation.
			CTextureResource *pTexture = NULL;
			if(eFIF != FIF_UNKNOWN)
			{
				FIBITMAP *pBitmap = FreeImage_Load(eFIF, sPath.data());
				FIBITMAP *pBitmap32bits = FreeImage_ConvertTo32Bits(pBitmap);

				QDir oDir(p_sSourcePath);
				pTexture = SAM_NEW CTextureResource(oDir.dirName(), oDir.absolutePath(), pBitmap32bits);

				// release the unused image.
				FreeImage_Unload(pBitmap);
			}

			return pTexture;
		}

		// Import the resource.
		IResource *CTextureResourceFactory::Create(const String &p_sPath)
		{
			return NULL;
		}

		// Check if the resource is supported.
		bool CTextureResourceFactory::IsSupported(const QString &p_sExtension) const
		{
			QByteArray sPath = p_sExtension.toLocal8Bit();
			return FreeImage_GetFIFFromFilename(sPath.data()) != FIF_UNKNOWN;
		}
	}
}
