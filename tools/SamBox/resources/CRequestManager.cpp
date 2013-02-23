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
#include "CRequestManager.h"
#include "IResourceFactory.h"
#include "CTextureResource.h"

namespace sam
{
	namespace box
	{
		typedef IExporter *(*CreateExporterPlugin)(); 
		typedef void (*ReleaseExporterPlugin)(); 

		CRequestManager *g_pRequestManager = NULL;
		CRequestManager::CRequestManager()
		{

		}

		CRequestManager::~CRequestManager()
		{
			// Unload all exporter plugin.
			Exporters::iterator it = m_aExporters.begin(), it_end = m_aExporters.end();
			for( ; it != it_end; ++it)
			{
				Library pLibrary = it->second->GetLibrary();
				if(pLibrary)
				{

				}
			}
		}

		//////////////////////////////////////////////////////////////////////////
		//							IMPORT & LOAD							    //
		//////////////////////////////////////////////////////////////////////////
		// Import the resource.
		void CRequestManager::RequestImport(const QString &p_sSourcePath, const QString &p_sDestination)
		{
			QStringList sList = p_sSourcePath.split(".");
			QString sExtension = sList.last();

			Factories::iterator it = m_aFactories.begin(), it_end = m_aFactories.end();
			for(; it != it_end; ++it)
			{
				IResourceFactory *pFactory = *it;
				if(pFactory->IsSupported(sExtension))
				{
					sExtension = "." + sExtension;

					QString sDestination = p_sDestination + "/" + QDir(p_sSourcePath).dirName();
					sDestination.resize(sDestination.size() - (sExtension.size()));

					// Create unique name.
					uint32 nIndex = 1;
					QString sUniqueFileName = sDestination + sExtension;
					while(QFile::exists(sUniqueFileName))
					{
						sUniqueFileName = sDestination +  QString::number(nIndex)  + sExtension;
						++nIndex;
					}

					// Copy file to destination.
					if(QFile::copy(p_sSourcePath, sUniqueFileName))
					{
						RequestLoad(pFactory, p_sSourcePath);						
					}								
					break;
				}
			}
		}

		// Load the resource.
		void CRequestManager::RequestLoad(const QString &p_sSourcePath)
		{
			QStringList sList = p_sSourcePath.split(".");
			QString sExtension = sList.last();

			Factories::iterator it = m_aFactories.begin(), it_end = m_aFactories.end();
			for(; it != it_end; ++it)
			{
				IResourceFactory *pFactory = *it;
				if(pFactory->IsSupported(sExtension))
				{
					RequestLoad(pFactory, p_sSourcePath);					
					break;
				}
			}
		}

		void CRequestManager::RequestLoad(IResourceFactory *p_pFactory, const QString &p_sSourcePath)
		{
			IResource *pResource = p_pFactory->Import(p_sSourcePath);
			if(pResource)
			{
				QByteArray sMetaPath = QString(p_sSourcePath + ".meta").toLocal8Bit();
				CBinarySerializer oSerializer(sMetaPath.data());

				// Create default metadata.
				if(QFile::exists(sMetaPath) == false)
				{
					oSerializer.BeginSerialization(false, "meta");
					oSerializer.BeginElem("resource");
					pResource->Write(&oSerializer);
				}
				// Load metadata.
				else
				{
					oSerializer.BeginSerialization(true, "meta");
					oSerializer.BeginElem("resource");
					pResource->Read(&oSerializer);
				}
				oSerializer.EndElem();
				oSerializer.EndSerialization();

				// TODO: check if exported resource is outdated.

// 				CTextureResource *pTexture = (CTextureResource*)pResource;
// 				FIBITMAP *pBitmap = pTexture->GetBitmap();
// 				STextureMeta oMeta;
// 				oMeta.m_bGenerateMipMap = true;
// 				oMeta.m_eMipMapFilter = e_MipMapFilter_Kaiser;
// 				oMeta.m_nInputFormat = 0;
// 				oMeta.m_nOutputFormat = 4;
// 				oMeta.m_nWidth = FreeImage_GetWidth(pBitmap);
// 				oMeta.m_nHeight = FreeImage_GetHeight(pBitmap);
// 
// 				RequestTextureExport((uint8*)FreeImage_GetBits(pBitmap), oMeta.m_nWidth * oMeta.m_nHeight * FreeImage_GetBPP(pBitmap) / 8, "D:/test.dds", oMeta, true);
			}
		}

		void CRequestManager::RequestUnload()
		{

		}

		// Register a factory.
		void CRequestManager::RegisterFactory(IResourceFactory *p_pFactory)
		{
#if defined(SAM_DEBUG)
			Factories::iterator it = m_aFactories.begin(), it_end = m_aFactories.end();
			for(; it != it_end; ++it)
			{
				SAM_ASSERT(*it != p_pFactory, "Factory is already registered.")
			}
#endif

			m_aFactories.push_back(p_pFactory);
		}

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		void CRequestManager::RequestTextureExport(const uint8 *p_pResourceBuffer, const uint32 p_nBufferSize, const char *p_sDestination, const STextureMeta &p_oMeta, bool p_bBigEndian)
		{
			Exporters::iterator it = m_aExporters.find(e_Exporter_Texture);
			if(it == m_aExporters.end())
			{
				SamLogWarning("Unable to exporter texture %s, no exporter registered");
				return;
			}

			// find exporter with supported format.
			ITextureExporter *pExporter = (ITextureExporter*)it->second;
			while(pExporter)
			{
				if(pExporter->IsSupported(p_oMeta.m_nOutputFormat))
				{
					break;
				}
			}

			if(!pExporter)
			{
				SamLogWarning("Unable to exporter texture %s, no exporter registered");
				return;
			}

			// Export.
			pExporter->Export(p_pResourceBuffer, p_nBufferSize, p_sDestination, p_oMeta, p_bBigEndian);
		}

		// Register exporter.
		void CRequestManager::RegisterExporter(const QString &p_sExporterPath)
		{
			QByteArray sPluginPath = p_sExporterPath.toLocal8Bit();

			Library pLibrary = SamLoadLibrary(sPluginPath.data());
			if(pLibrary == NULL)
			{
				SamLogError("Unable to load exporter %s", sPluginPath.data());
				return;
			}

			// Get symbol.
			CreateExporterPlugin pFunc = (CreateExporterPlugin)GetProcAddress(pLibrary, "CreateExporterPlugin");
			if(!pFunc)
			{
				SamLogError("Unable to create exporter %s, unable to find symbol CreateExporterPlugin", sPluginPath.data());
				return;
			}

			IExporter *pExporter = pFunc();
			if(!pExporter)
			{
				SamFreeLibrary(pLibrary);
				SamLogError("Unable to create exporter %s, unable to find symbol CreateExporterPlugin", sPluginPath.data());
				return;
			}

			// Add the created exporter.
			pExporter->SetLibrary(pLibrary);
			Exporters::iterator it = m_aExporters.find(pExporter->GetType());
			if(it != m_aExporters.end())
			{
				IExporter *pCurrentExporter = it->second;
#if defined(SAM_DEBUG)
				while(pCurrentExporter)
				{
					SAM_ASSERT(strcmp(pCurrentExporter->GetName(), pExporter->GetName()) != 0, "Exporter is already registered");

					pCurrentExporter = pCurrentExporter->GetNext();
				}
				pCurrentExporter = it->second;
#endif

				pCurrentExporter->Add(pExporter);
			}
			else
			{
				m_aExporters[pExporter->GetType()] = pExporter;
			}
		}
	}
}
