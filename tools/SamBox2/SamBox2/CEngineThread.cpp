//===========================================
// Copyright (C) 2013-2014 Stone Age Machine
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
#include "CEngineThread.h"

#include "SamBox.h"

CEngineThread::CEngineThread() :
    m_bResolutionChanged(false), m_nWidth(0), m_nHeight(0)
{

}

void CEngineThread::SetResolution(int p_nWidth, int p_nHeight)
{
    if( (p_nWidth > 0 && p_nHeight > 0) && (p_nWidth != m_nWidth || p_nHeight != m_nHeight) )
    {
        m_nWidth = p_nWidth;
        m_nHeight = p_nHeight;

        m_bResolutionChanged = true;
    }
}
