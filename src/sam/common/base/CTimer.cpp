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
#include "SamCommonPCH.h"
#include "common/base/CTimer.h"
#include <ctime>

namespace sam
{
    /// @brief Constructor.
    CTimer::CTimer()
        : m_fCurrTime(0.f), m_fFrameTime(0.f), m_fFrameRate(0.f), m_fComputeFPS(0.f)
    {
        m_fCurrTime = GetAsyncCurrTime();
    }

    /// @brief Destructor.
    CTimer::~CTimer()        
    {
    }

    /// @brief Update timer every frame.
    void CTimer::OnFrameStart()
    {
        // memorize current time.
        f32 fCurrentTime = GetAsyncCurrTime();

        // compute frame time.
        m_fFrameTime = fCurrentTime - m_fCurrTime;
        m_fComputeFPS -= m_fFrameTime;

        // Compute frame rate every second.
        if(m_fComputeFPS <= 0.f)
        {
            m_fComputeFPS = 1.f;
            m_fFrameRate = 1.f / m_fFrameTime;
        }

        m_fCurrTime = fCurrentTime;
    }

    /// @brief Retrieves current time in seconds.
    /// 
    /// @return Elapsed time since starting application.
    float CTimer::GetCurrTime()
    {
        return m_fCurrTime;
    }

    /// @brief Retrieves current frame time in seconds.
    /// 
    /// @return Elapsed time since last frame.
    float CTimer::GetFrameTime()
    {
        return m_fFrameTime;
    }

    /// @brief Retrieves frame rate in seconds..
    /// 
    /// @return Frame rate.
    float CTimer::GetFrameRate()
    {
        return m_fFrameRate;
    }
}
