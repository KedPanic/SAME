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
#ifndef __COLOR__
#define __COLOR__

namespace sam
{
    /// @brief Color description.
    struct Color : public sam::IAllocated
    {
        float r, g, b, a;

        /// @brief Default constructor.
        Color(void) : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}

        /// @brief Constructor.
        /// 
        /// @param _fRed Red channel.
        /// @param _fGreen Green channel.
        /// @param _fBlue Blue channel.
        /// @param _fAlpha Alpha channel.
        Color(float _fRed, float _fGreen, float _fBlue, float _fAlpha)
            : r(_fRed), g(_fGreen), b(_fBlue), a(_fAlpha) {}
    };
}

#endif // __COLOR__
