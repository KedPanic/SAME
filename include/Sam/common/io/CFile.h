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
#ifndef __CFILE__
#define __CFILE__

#include <common/io/IStream.h>

namespace sam
{
    /// @brief File data stream.
    ///
    /// @see Stream.
    class SAM_COMMON_API CFile : public IStream
    {
    public:
        /// @brief Constructor.
		/// 
		/// @param p_bFreeOnClose True to free cached buffer.
		CFile(bool p_bFreeOnClose = true);

        /// @brief Constructor.
        /// 		
        /// @param p_sFile Name of the file.
		/// @param p_bFreeOnClose True to free cached buffer.
        CFile(const char *p_sFile, bool p_bFreeOnClose = true);

        /// @brief Destructor.
        ~CFile();

        /// @brief Open the stream.
        /// 
        /// @param p_sFilename name of the file.
        /// @param p_nOpenFlags Open mode.
        /// 
        /// @return True if there is no error.
        bool Open(const char *p_sFilename, int p_nOpenFlags = e_OM_Read | e_OM_Binary);

        /// @brief Close the stream.
        void Close(void);

        /// @brief Reads a block of bytes and store it in the buffer.
        /// 
        /// @param p_pBuffer Pointer to an allocated block of memory.
        /// @param p_nSize Size of bytes to read.
		///
        /// @return the number of bytes read.
        uint32 Read(void* p_pBuffer, uint32 p_nSize);

        /// @brief Writes data in the file to the current position.
        /// 
        /// @param p_pData Data to write.
        /// @param p_nSize Size of bytes to write.
		///
        /// @return the number of written bytes.
        uint32 Write(const void *p_pData, uint32 p_nSize);

        /// @brief Set the position in the stream.
        ///
        /// @param p_nOffset The new position.
        /// @param p_eOrigin Seeking direction.
		///
        /// @return the number of bytes sought.
        uint32 Seek(uint32 p_nOffset, ESeekDir p_eOrigin);

        /// @brief Get the current position in the stream.
        /// 
        /// @return the current position in the stream.
        uint32 Tell();

        /// @brief Get the size of the stream.
        /// 
        /// @return the size of the stream.
        uint32 Size();

        /// @brief Get true if the end of the stream is reached.
        ///
        /// @return true if the end of the stream is reached.
        bool Eof() const;

        /// @brief Get the data of the stream.
        ///
        /// @return data of the stream.
        uint8 *Data();

		/// @brief Flush current content.
		void Flush();

    private:
        File *m_pFile;   ///< Handle of the file.
		uint8 *m_pCache;
    };
}

#endif // __CFILE__
