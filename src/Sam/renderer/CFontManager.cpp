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
#include "SamRendererPCH.h"
#include "renderer/CFontManager.h"


namespace sam
{
    /// @brief Constructor.
    CFontManager::CFontManager()
        : m_pFirstFont(NULL)
    {
    }

    /// @brief Destructor.
    CFontManager::~CFontManager()
    {
    }

    /// @brief Create font.
    ///
    /// @param p_sName Font name.
    /// @param p_nSize Height of the font.
    /// 
    /// @return Generated font ID or 0.
    FontID CFontManager::CreateFont(const char *p_sName, uint32 p_nSize)
    {     
        return 1;
    }

    /// @brief Delete font.
    /// 
    /// @param p_nFontID ID.
    /// 
    /// @return True if succeed.
    bool CFontManager::DeleteFont(FontID p_nFontID)
    {
        return true;
    }

    /// @brief Retrieves font by name.
    /// 
    /// @param p_sFontID ID.
    /// 
    /// @return Pointer to the font or NULL if not found.
    CFont *CFontManager::GetFont(FontID p_nFontID) const
    {
        return NULL;
    }
}