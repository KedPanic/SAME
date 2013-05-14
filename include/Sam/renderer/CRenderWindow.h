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
#ifndef __CRENDER_WINDOW__
#define __CRENDER_WINDOW__

namespace sam
{
    /// @enum Type of renderer.
    enum ERenderType
    {
        ERenderType_Undefined,
        ERenderType_DX11,
    };

    /// @enum Clear mask flags.
    enum EClearType
    {
        EClearType_Color    = 1 << 0,   ///< Flag to clear the color buffer.
        EClearType_Depth    = 1 << 1,   ///< Flag to clear the depth buffer.
        EClearType_Stencil  = 1 << 2,   ///< Flag to clear the stencil buffer.
        EClearType_Accum    = 1 << 3,   ///< Flag to clear the accumulation buffer.
    };

    /// @brief Supported display format.
    struct SDisplayFormat
    {

    };

	/// @brief Window event listener.
	class IWindowEventListener
	{
	public:
		/// @brief On size event.
		/// 
		/// @param p_iWidth Width of the window.
		/// @param p_iHeight Height of the window.
		virtual void OnSize(int p_iWidth, int p_iHeight) = 0;

		/// @brief On close event.
		virtual void OnClose() = 0;
		
		/// @brief On gain focus.
		virtual void OnGainFocus() = 0;

		/// @brief On lose focus.
		virtual void OnLoseFocus() = 0;
	};
}

#include "renderer/CRenderWindowPlf.h"

#endif // __CRENDER_WINDOW__
