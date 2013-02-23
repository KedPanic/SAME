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
#ifndef __SAMBOX_CREQUEST_MANAGER_H__
#define __SAMBOX_CREQUEST_MANAGER_H__

#include "exports/IExporter.h"
#include "exports/TextureExporter.h"

namespace sam
{
	namespace box
	{
		/// @brief Loader/Unloader manager. Used to load/unload asynchronously.
		class CRequestManager : public IAllocated
		{
		public:
			CRequestManager();
			~CRequestManager();

			//////////////////////////////////////////////////////////////////////////
			//							IMPORT & LOAD							    //
			//////////////////////////////////////////////////////////////////////////
			/// @brief Import the resource.
			/// 
			/// @param p_sSourcePath Path of the source file.
			/// @param p_sDestination Folder where the file will be copied.
			void RequestImport(const QString &p_sSourcePath, const QString &p_sDestination);

			/// @brief Load the resource.
			/// 
			/// @param p_sSourcePath Path of the source file.
			void RequestLoad(const QString &p_sSourcePath);

			void RequestUnload();

			/// @brief Register a factory.
			/// 
			/// @param p_pFactory Factory to add.
			void RegisterFactory(IResourceFactory *p_pFactory);



			//////////////////////////////////////////////////////////////////////////
			//									EXPORT							    //
			//////////////////////////////////////////////////////////////////////////
			void RequestTextureExport(const uint8 *p_pResourceBuffer, const uint32 p_nBufferSize, const char *p_sDestination, const STextureMeta &p_oMeta, bool p_bBigEndian);

			/// @brief Register exporter.
			/// 
			/// @param p_sExporterPath Exporter to add.
			void RegisterExporter(const QString &p_sExporterPath);

		private:
			typedef std::vector<IResourceFactory*> Factories;
			Factories m_aFactories;

			typedef std::map<EExporterResourceType, IExporter*> Exporters;
			Exporters m_aExporters;

			void RequestLoad(IResourceFactory *p_pFactory, const QString &p_sSourcePath);
		};
	}
}

#endif // __SAMBOX_CREQUEST_MANAGER_H__
