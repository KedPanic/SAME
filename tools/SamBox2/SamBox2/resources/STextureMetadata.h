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
#ifndef __SAMBOX_TEXTURE_METADATA__
#define __SAMBOX_TEXTURE_METADATA__

/// @enum Mipmap generation filter.
enum EMipMapFilter
{
	e_MipMapFilter_Box,
	e_MipMapFilter_Triangle,
	e_MipMapFilter_Kaiser,
};

/// @enum Internal input format.
enum ETextureInputFormat
{
	e_TextureInputFormat_RGBA_U8,	///< 8 bit per canal.
};

/// @enum Texture filtering
enum ETextureFilter
{
	e_TextureFilter_Point,		///< min=point mag=point mip=none
	e_TextureFilter_Bilinear,	///< min=linear mag=linear mip=point
	e_TextureFilter_Trilinear,	///< min=linear mag=linear mip=linear
};

/// @brief Texture metadata. Data used for the export.
struct STextureMetadata
{
	// COMMON SETTINGS
	sam::ETextureWrap m_eTextureWrap;	///< Texture wrap mode.
	ETextureFilter	  m_eTextureFilter; ///< Texture filtering.

	ETextureInputFormat m_eInputFormat;	///< The internal format. Depen

	// MIPMAP SETTINGS
	bool m_bGenerateMipMap;				///< True to generate the mipmap.
	EMipMapFilter m_eMipMapFilter;		///< Filter used to generate the mipmap.
	

	// TARGET SETTINGS
	struct STargetSettings
	{
		uint32 m_nTargetId;	///< Target Id.
		uint32 m_nFormat;	///< Format to export.
		uint32 m_nMaxSize;	///< Max texture size.
	};

	typedef std::vector<STargetSettings> TargetSettings;
	TargetSettings m_aTargetSettings; ///< Array of specific target settings.

	// copy operator.
	void operator=(const STextureMetadata &p_oMetadata)
	{
		m_eTextureWrap		= p_oMetadata.m_eTextureWrap;
		m_eTextureFilter	= p_oMetadata.m_eTextureFilter;

		m_bGenerateMipMap	= p_oMetadata.m_bGenerateMipMap;
		m_eMipMapFilter		= p_oMetadata.m_eMipMapFilter;

		m_aTargetSettings.clear();
		m_aTargetSettings.resize(p_oMetadata.m_aTargetSettings.size());
		for(uint32 nIndex = 0; nIndex < p_oMetadata.m_aTargetSettings.size(); ++nIndex)
		{
			m_aTargetSettings[nIndex] = p_oMetadata.m_aTargetSettings[nIndex];
		}
	}
};

#endif // __SAMBOX_TEXTURE_METADATA__
