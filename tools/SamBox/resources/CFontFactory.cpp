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
#include "resources/CFontFactory.h"
#include "resources/CFont.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace sam
{
	namespace box
	{
		FT_Library g_oFreetypeLibrary;

		CFontFactory::CFontFactory()
			: m_sExtension("ttf")
		{
		}

		// Initialize it !.
		bool CFontFactory::Initialize()
		{
			if(FT_Init_FreeType(&g_oFreetypeLibrary)) 
			{
				SamLogError("Unable to initialize freetype");
				return false;
			}

			return true;
		}

		// Create the resource.
		IResource *CFontFactory::Create(const String &p_sName, const String &p_sPath)
		{
			CFile oFile;
			if(oFile.Open(p_sPath.c_str()))
			{
				// load font from memory and get the first style (face).
				FT_Face oFace;
				FT_Error nError = FT_New_Memory_Face(g_oFreetypeLibrary, oFile.Data(), oFile.Size(), 0, &oFace);
				if(nError != 0)
				{
					SamLogError("Unable to load font '%s'", p_sName);
					return 0;
				}

				nError = FT_Set_Pixel_Sizes(oFace, 0, 12 /* todo configurable */);
				if(nError != 0)
				{
					SamLogError("Unable to set size of the font '%s'", p_sName);
					return 0;
				}

				char *sTextureData = SAM_ALLOC_ARRAY(char, oFace->glyph->metrics.width * oFace->glyph->metrics.height);
				// create 
				for(char c = 32; c < 128; ++c)
				{
					FT_Load_Char(oFace, c, FT_LOAD_RENDER);
				}
			}

			return NULL;
		}

		// Import the resource.
		bool CFontFactory::Import(const String &p_sPath)
		{
			return true;
		}

		// Check if the resource is supported.
		bool CFontFactory::IsSupported(const String &p_sExtension) const
		{
			return m_sExtension == p_sExtension;
		}
	}
}
