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
#ifndef __SAMBOX_IEXPORTER__
#define __SAMBOX_IEXPORTER__

namespace sam
{
	namespace box
	{
		/// @enum Type of exported resource.
		enum EExporterResourceType
		{
			e_Exporter_Texture,
			e_Exporter_Sound,
			e_Exporter_Mesh,

			e_Exporter_Nb,
		};

		struct SFormat
		{
			const char *m_sReadableName; ///< Used by the editor.
			uint32 m_nFormat;			 ///< ID of the format (internal usage).
		};

		/// @brief Interface of the exporter.
		class IExporter : public tpl::TList<IExporter>, public IAllocated
		{
		public:
			typedef  std::vector<SParam> Params;

			IExporter() : m_pLibrary(NULL) {}			

			/// @brief Set library.
			/// 
			/// @param p_pLibrary Handle of the shared library.
			void SetLibrary(Library p_pLibrary) {m_pLibrary = p_pLibrary;}

			/// @brief Retrieves handle of the shared library.
			/// 
			/// @return Handle of the shared library.
			Library GetLibrary() const {return m_pLibrary;}

			/// @brief Check if format is supported.
			/// 
			/// @param p_nFormat Format ID.
			/// 
			/// @return True if supported.
			INLINE bool IsSupported(uint32 p_nFormat) const
			{
				const SFormat *pFormats = GetFormat();
				for(uint32 nIndex = 0; nIndex < GetNbSupportedFormats(); ++nIndex)
				{
					if(pFormats[nIndex].m_nFormat == p_nFormat)
					{
						return true;
					}
				}
				
				return false;
			}

			/// @brief Retrieves type of exported resource.
			/// 
			/// @return Type of exported resource.
			virtual EExporterResourceType GetType() const = 0;

			/// @brief Retrieves the name of the exporter.
			/// 
			/// @return Name of the exporter.
			virtual const char *GetName() const = 0;

			/// @brief Retrieves supported export format.
			/// 
			/// @return Supported export format.
			virtual const SFormat *GetFormat() const = 0;

			/// @brief Retrieves how many format are supported.
			/// 
			/// @return How many format are supported.
			virtual uint32 GetNbSupportedFormats() const = 0;			

		private:
			EExporterResourceType m_eResourceType; ///< Type of exporter.
			Library m_pLibrary;
		};
	}
}

#endif // __SAMBOX_IEXPORTER__
