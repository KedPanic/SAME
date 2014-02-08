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
#include "exporter/ITextureExporter.h"
#include "resources/CTextureResource.h"

namespace texture
{
	//////////////////////////////////////////////////////////////////////////
	//						NAME OF THE PARAMETERS							//
	//////////////////////////////////////////////////////////////////////////
	namespace params
	{
		const sam::ID InputFormat = sam::CreateID("inputformat", 11);
		const sam::ID OutputFormat = sam::CreateID("outputformat", 12);
		const sam::ID Width = sam::CreateID("width", 5);
		const sam::ID Height = sam::CreateID("height", 6);
		const sam::ID GenerateMipMap = sam::CreateID("generatemipmap", 14);
		const sam::ID MipMapFilter = sam::CreateID("mipmapfilter", 12);
	}
}

//////////////////////////////////////////////////////////////////////////
//									JOB									//
//////////////////////////////////////////////////////////////////////////
struct STextureJobData
{
	ITextureExporter *m_pExporter;
	CTextureResource *m_pTexture;
	sam::String m_sDestination;
	sam::ID m_nPlatformId;
};

void TextureExportCallback(void *p_pData)
{
	STextureJobData *pTextureJobData = (STextureJobData*)p_pData;

	const char *sTextureFilename = pTextureJobData->m_pTexture->GetPath().c_str();

	// get file format.
	FREE_IMAGE_FORMAT eImageFormat = FreeImage_GetFileType(sTextureFilename);
	if(eImageFormat == FIF_UNKNOWN)
	{
		eImageFormat = FreeImage_GetFIFFromFilename(sTextureFilename);
	}

	// image conversion.
	if(eImageFormat != FIF_UNKNOWN)
	{
		FIBITMAP *pBitmap = FreeImage_Load(eImageFormat, sTextureFilename);
		
		// convert the image to a proper format.
		FIBITMAP *pConvertedBitmap = FreeImage_ConvertTo32Bits(pBitmap);
		FreeImage_Save(FIF_PNG, pConvertedBitmap, "test32bits.png");

		// create the image informations.
		SImage oImage;				
		oImage.m_nWidth = FreeImage_GetWidth(pConvertedBitmap);
		oImage.m_nHeight = FreeImage_GetHeight(pConvertedBitmap);
		oImage.m_nPitch = FreeImage_GetPitch(pConvertedBitmap);
		oImage.m_pPixelData = FreeImage_GetBits(pConvertedBitmap);
		oImage.m_nInputFormat = e_TextureInputFormat_RGBA_U8;

		// export the image.
		pTextureJobData->m_pExporter->Export(oImage, pTextureJobData->m_sDestination + pTextureJobData->m_pTexture->GetName(), pTextureJobData->m_pTexture->GetMetadata(), pTextureJobData->m_nPlatformId);

		// release the memory.
		FreeImage_Unload(pBitmap);
	}

	SAM_FREE(pTextureJobData);
}


//////////////////////////////////////////////////////////////////////////
//								TEXTURE EXPORTER						//
//////////////////////////////////////////////////////////////////////////
// Request an export.
sam::SJob ITextureExporter::CreateJob(IResource *p_pResource, const sam::String &p_sDestination, sam::ID p_nPlatformId)
{
	SAM_ASSERT(p_pResource != NULL, "Resource can't be null.");

	CTextureResource *pTextureResource = (CTextureResource*)p_pResource;

	// create job data.
	STextureJobData *pTextureJobData = SAM_ALLOC(STextureJobData);
	pTextureJobData->m_pExporter = this;
	pTextureJobData->m_pTexture = pTextureResource;
	pTextureJobData->m_sDestination = p_sDestination;
	pTextureJobData->m_nPlatformId = p_nPlatformId;

// 	set meta data from params.		
// 	memset(&pTextureJobData->m_oMeta, 0, sizeof(STextureMetadata));
// 
// 	for(uint32 index = 0; index < p_aParams.size(); ++index)
// 	{
// 		sam::ETypeID eType = p_aParams[index].m_eType;
// 		if(p_aParams[index].m_nID == params::InputFormat)
// 		{
// 			SAM_ASSERT(eType == sam::e_Type_UInt, "Bad type of parameter %d", eType);
// 			pTextureJobData->m_oMeta.m_eInputFormat = static_cast<EInputFormat>(p_aParams[index].m_oValue.ui);
// 		}
// 		else if(p_aParams[index].m_nID == params::OutputFormat)
// 		{
// 			SAM_ASSERT(eType == sam::e_Type_UInt, "Bad type of parameter %d", eType);
// 			pTextureJobData->m_oMeta.m_nOutputFormat = p_aParams[index].m_oValue.ui;
// 		}
// 		else if(p_aParams[index].m_nID == params::Width)
// 		{
// 			SAM_ASSERT(eType == sam::e_Type_UInt, "Bad type of parameter %d", eType);
// 			pTextureJobData->m_oMeta.m_nWidth = p_aParams[index].m_oValue.ui;
// 		}
// 		else if(p_aParams[index].m_nID == params::Height)
// 		{
// 			SAM_ASSERT(eType == sam::e_Type_UInt, "Bad type of parameter %d", eType);
// 			pTextureJobData->m_oMeta.m_nHeight = p_aParams[index].m_oValue.ui;
// 		}
// 		else if(p_aParams[index].m_nID == params::GenerateMipMap)
// 		{
// 			SAM_ASSERT(eType == sam::e_Type_Bool, "Bad type of parameter %d", eType);
// 			pTextureJobData->m_oMeta.m_bGenerateMipMap = p_aParams[index].m_oValue.b;
// 		}
// 		else if(p_aParams[index].m_nID == params::MipMapFilter)
// 		{
// 			SAM_ASSERT(eType == sam::e_Type_UInt, "Bad type of parameter %d", eType);
// 			pTextureJobData->m_oMeta.m_eMipMapFilter = static_cast<EMipMapFilter>(p_aParams[index].m_oValue.ui);
// 		}
// 		else
// 		{
// #if defined(SAM_DEBUG)
// 			SamLogError("Unknow parameters %s\n", p_aParams[index].m_nID.GetReadableID());
// #else
// 			SamLogError("Unknow parameters %d\n", p_aParams[index].m_nID);
// #endif
// 		}
// 	}

	// Create the job.
	sam::SJob oJob =  {&TextureExportCallback, pTextureJobData};
	return oJob;
}
