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
#ifndef __ISOUND_BANK__
#define __ISOUND_BANK__

#include <SamConfig.h>

namespace sam
{
    /// @brief Sound bank interface.
    class ISoundBank : public IAllocated
    {
    public:
        /// @brief Retrieves name of the bank.
        /// 
        /// @return Name of the bank.
        virtual const String &GetName() const = 0;

        /// @brief Retrieves path of the bank.
        /// 
        /// @return Path of the bank.
        virtual const String &GetPath() const = 0;

        /// @brief Load the bank.
        /// 
        /// @return True if no error occurred.
        virtual bool Load() = 0;

        /// @brief Unload the bank.
        virtual void Unload() = 0;
    };
}

#endif // __ISOUND_BANK__
