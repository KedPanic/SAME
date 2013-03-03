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
#include "CTextureResource.h"

namespace sam
{
	namespace box
	{
		// Constructor.
		CTextureResource::CTextureResource(const QString &p_sName, const QString &p_sPath, FIBITMAP *p_pBitmap)
			: IResource(p_sName, p_sPath), m_pBitmap(p_pBitmap)
		{
			// set to default metadata.
			m_oMetaData.m_nWidth = FreeImage_GetWidth(m_pBitmap);
			m_oMetaData.m_nHeight = FreeImage_GetHeight(m_pBitmap);
		}

		// Destructor.
		CTextureResource::~CTextureResource()
		{

		}

		// Load resource.
		bool CTextureResource::Load()
		{
			return true;
		}

		// Unload resource.
		bool CTextureResource::Unload()
		{
			return true;
		}

		// Serialize the object
		void CTextureResource::Read(ISerializer *p_pContext)
		{
			IResource::Read(p_pContext);

			p_pContext->BeginElem("meta");
			p_pContext->ReadValue("version", m_oMetaData.m_nVersion);
			p_pContext->ReadValue("inputformat", m_oMetaData.m_nInputFormat);
			p_pContext->ReadValue("outputformat", m_oMetaData.m_nOutputFormat);
			p_pContext->ReadValue("width", m_oMetaData.m_nWidth);
			p_pContext->ReadValue("height", m_oMetaData.m_nHeight);
			p_pContext->ReadValue("generate_mipmap", m_oMetaData.m_bGenerateMipMap);
//			p_pContext->ReadValue("mipmap_filter", m_oMetaData.m_eMipMapFilter);
			p_pContext->EndElem();
		}

		// Serialize the object
		void CTextureResource::Write(ISerializer *p_pContext)
		{
			IResource::Write(p_pContext);

			p_pContext->BeginElem("meta");
			p_pContext->WriteValue("version", (int)m_oMetaData.m_nVersion);
			p_pContext->WriteValue("inputformat", (int)m_oMetaData.m_nInputFormat);
			p_pContext->WriteValue("outputformat", (int)m_oMetaData.m_nOutputFormat);
			p_pContext->WriteValue("width", (int)m_oMetaData.m_nWidth);
			p_pContext->WriteValue("height", (int)m_oMetaData.m_nHeight);
			p_pContext->WriteValue("generate_mipmap", m_oMetaData.m_bGenerateMipMap);
			p_pContext->WriteValue("mipmap_filter", m_oMetaData.m_eMipMapFilter);
			p_pContext->EndElem();
		}
	}	
}
