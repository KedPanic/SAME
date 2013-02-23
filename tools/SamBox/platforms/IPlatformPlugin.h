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
#ifndef __SAMBOX_IPLATFORM_PLUGIN__
#define __SAMBOX_IPLATFORM_PLUGIN__

#include "platforms/SSoundMeta.h"

// plugin macro export
#ifdef SAM_PLUGIN_EXPORTS
#   define SAM_PLUGIN_API LIBRARY_EXPORT
#else
#   define SAM_PLUGIN_API LIBRARY_IMPORT
#endif

namespace sam
{
	namespace box
	{
		/// @brief Platform plugin, used to export raw data to specified format.
		class IPlatformPlugin : public tpl::TList<IPlatformPlugin>, public IAllocated
		{
		public:
			/// @brief Describe a format (internal usage).
			struct SDataFormat
			{
				uint32 m_nID;           ///< Unique ID of the data format.
				const char *m_pFormat;  ///< Name of the format.
			};

			IPlatformPlugin() : m_pLibrary(NULL) {}
			virtual ~IPlatformPlugin() {}

			/// @brief Set the library.
			/// 
			/// @param p_pLibrary Shared library.
			void SetLibrary(Library p_pLibrary) {m_pLibrary = p_pLibrary;}

			/// @brief Retrieves the shared library
			/// 
			/// @return Shared library.
			Library GetLibrary() const {return m_pLibrary;}

			/// @brief Retrieves platform name.
			/// 
			/// @return Name of the platform.
			virtual const char *GetName() const = 0;

			/// @brief Retrieves the array of the supported texture formats.
			/// 
			/// @return Array of the supported texture formats.
			/// 
			/// @remarks
			///     Last index is NULL.
			virtual SDataFormat *GetTextureFormats() const = 0; 

			/// @brief Retrieves the array of the supported sound formats.
			/// 
			/// @return Array of the supported texture formats.
			/// 
			/// @remarks
			///     Last index is NULL.
			virtual SDataFormat *GetSoundFormats() const = 0; 

			/// @brief Sound exporter.
			/// 
			/// @param p_pRawData Sound raw data.
			/// @param p_nSize Size of the buffer.
			/// @param p_oSoundMeta Information to export the sound.
			/// 
			/// @return Pointer to the exported data.
			virtual bool ExportSound(void *p_pRawData, uint32 p_nSize, const SSoundMeta &p_oSoundMeta) = 0;

		private:
			Library m_pLibrary; ///< Shared library handle.
		};		
	}
}
#endif // __SAMBOX_IPLATFORM_PLUGIN__
