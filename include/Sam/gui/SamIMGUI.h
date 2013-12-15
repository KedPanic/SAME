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
#ifndef __SAM_IMGUI__
#define __SAM_IMGUI__

namespace sam
{
	namespace gui
	{
		struct Rectangle
		{
			uint32 x;
			uint32 y;
			uint32 width;
			uint32 height;
		};

		/// @brief Begin the UI processing.
		extern SAM_GUI_API void Begin();

		/// @brief End of the UI processing.
		extern SAM_GUI_API void End();

		/// @brief Draw a label at the specified position.
		/// 
		/// @param p_oSurface Where we will draw the label (position and size).
		/// @param p_sText Text to display.
		extern SAM_GUI_API void DrawLabel(const Rectangle &p_oSurface, const char *p_sText);

		/// @brief Draw a button at the specified position.
		/// 
		/// @param p_oSurface Where we will draw the button (position and size).
		/// @param p_sText Text to display.
		extern SAM_GUI_API void DrawButton(const Rectangle &p_oSurface, const char *p_sText);
	}	
}

#endif // __SAM_IMGUI__
