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
#ifndef __CRENDER_CONFIG__
#define __CRENDER_CONFIG__

namespace sam
{
    struct CRenderConfig : public ISerializable
    {
        int m_nWidth, m_nHeight;
        bool m_bFullscreen;

        IMPLEMENT_SERIALIZABLE(CRenderConfig, "rendercfg");

        CRenderConfig()
            : m_nWidth(0), m_nHeight(0), m_bFullscreen(false)
        {
        }

        /// @brief Serialize the object
        /// 
        /// @param _pContext Pointer to the context
        void Serialize(ISerializer *_pContext)
        {
            _pContext->Value("width", m_nWidth);
            _pContext->Value("height", m_nHeight);
            _pContext->Value("fullscreen", m_bFullscreen);
        }
    };
}
#endif // __CRENDER_CONFIG__
