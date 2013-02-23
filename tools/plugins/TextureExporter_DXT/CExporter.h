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
#ifndef __SAMBOX_CEXPORTER_DXT__
#define __SAMBOX_CEXPORTER_DXT__

namespace sam
{
	namespace box
	{
		/// @brief Interface of the exporter.
		class CExporter : public ITextureExporter
		{
		public:
			/// @brief Constructor.
			CExporter();			

			/// @brief Retrieves the name of the exporter.
			/// 
			/// @return Name of the exporter.
			const char *GetName() const {return "DXT";}

			/// @brief Retrieves supported export format.
			/// 
			/// @return Supported export format.
			const SFormat *GetFormat() const {return m_aFormat;}

			/// @brief Retrieves how many format are supported.
			/// 
			/// @return How many format are supported.
			virtual uint32 GetNbSupportedFormats() const {return e_Format_Nb;}

			bool Export(const uint8 *p_pResourceBuffer, const uint32 p_nBufferSize, const char *p_sDestination, const STextureMeta &p_oMeta, bool p_bBigEndian);

		private:
			enum ETextureFormat
			{
				e_Format_BC1 = nvtt::Format_BC1,
				e_Format_BC2 = nvtt::Format_BC2,
				e_Format_BC3 = nvtt::Format_BC3,

				e_Format_Nb = 3,
			};

			SFormat m_aFormat[e_Format_Nb];
		};
	}
}

#endif // __SAMBOX_CEXPORTER_DXT__
