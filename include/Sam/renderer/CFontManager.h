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
#ifndef __CFONT_MANAGER__
#define __CFONT_MANAGER__

namespace sam
{
    /// @brief Font manager. Managing font.
    /// 
    /// @remarks
    ///     All font will be loaded from "fonts" data directory.
    ///     We have to create a stream location "fonts".
    class SAM_RENDERER_API CFontManager : public IAllocated
    {
    public:
        /// @brief Constructor.
        CFontManager();

        /// @brief Destructor.
        ~CFontManager();

        /// @brief Create font.
        ///
        /// @param p_sName Font name.
        /// @param p_nSize Height of the font.
        /// 
        /// @return Generated font ID or 0.
        FontID CreateFont(const char *p_sName, uint32 p_nSize);

        /// @brief Delete font.
        /// 
        /// @param p_nFontID ID.
        /// 
        /// @return True if succeed.
        bool DeleteFont(FontID p_nFontID);

        /// @brief Retrieves font by name.
        /// 
        /// @param p_sFontID ID.
        /// 
        /// @return Pointer to the font or NULL if not found.
        CFont *GetFont(FontID p_nFontID) const;

    private:
        CFont *m_pFirstFont; ///< First font of the linked list.
    };
}

#endif // __CFONT_MANAGER__
