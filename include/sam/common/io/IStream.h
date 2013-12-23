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
#ifndef __ISTREAM__
#define __ISTREAM__

namespace sam 
{
    /// @brief Interface to manipulate output streams.
    class IStream : public IAllocated
    {
    protected:
        bool m_bFreeOnClose; ///< True to free on close.

    public:
        /// @brief Constructor.
        ///
        /// @param _bFreeOnClose True if we have to delete the memory when the stream is release.
        IStream(bool _bFreeOnClose = false)
            : m_bFreeOnClose(_bFreeOnClose) {}

        virtual ~IStream(void){}

        /// @brief Get true if we have to delete the memory when the stream is release.
        ///
        /// @return true if we have to delete the memory when the stream is release.
        bool FreeOnClose(void) const {return m_bFreeOnClose;}

        /// @brief Close the stream.
        virtual void Close(void) = 0;

        /// @brief Read a block of bytes and store it in the buffer.
        /// 
        /// @param _pBuffer Pointer to an allocated block of memory.
        /// @param _iSize Size of bytes to read.
        /// @return the number of bytes read.
        virtual uint32 Read(void* _pBuffer, uint32 _iSize) = 0;

        /// @brief Set the position in the stream.
        ///
        /// @param _iOffset The new position.
        /// @param _eOrigin Seeking direction.
        /// @return the number of bytes sought.
        virtual uint32 Seek(uint32 _iOffset, ESeekDir _eOrigin) = 0;

        /// @brief Get the current position in the stream.
        /// 
        /// @return the current position in the stream.
        virtual uint32 Tell(void) = 0;

        /// @brief Get the size of the stream.
        /// 
        /// @return the size of the stream.
        virtual uint32 Size(void) = 0;

        /// @brief Get true if the end of the stream is reached.
        ///
        /// @return true if the end of the stream is reached.
        virtual bool Eof(void) const = 0;

        /// @brief Get the data of the stream.
        ///
        /// @return data of the stream.
        virtual uint8* Data(void) = 0;
    };
}

#endif // __ISTREAM__
