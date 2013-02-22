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
#ifndef __CTIMER__
#define __CTIMER__

namespace sam
{
    /// @brief Timer.
    class SAM_COMMON_API CTimer : public IAllocated
    {
    public:
        /// @brief Constructor.
        CTimer(void);

        /// @brief Destructor.
        ~CTimer(void);

        /// @brief Update timer every frame.
        void OnFrameStart(void);

        /// @brief Retrieves current time in seconds.
        /// 
        /// @return Elapsed time since starting application at the last frame.
        float GetCurrTime(void);

        /// @brief Retrieves current time in seconds.
        /// 
        /// @return Elapsed time since starting application at the call.
        float GetAsyncCurrTime(void);

        /// @brief Retrieves current frame time in seconds.
        /// 
        /// @return Elapsed time since last frame.
        float GetFrameTime(void);

        /// @brief Retrieves frame rate in seconds..
        /// 
        /// @return Frame rate.
        float GetFrameRate(void);

    private:
        float m_fCurrTime;  ///< Current time at the last frame.
        float m_fFrameTime; ///< Elapsed time since the last frame.
        float m_fFrameRate; ///< Frame rate.
        float m_fComputeFPS;///< Timer to update FPS value.
    };
}

#endif // __CTIMER__
