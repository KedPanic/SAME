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
#ifndef __CMEMORY_STREAM__
#define __CMEMORY_STREAM__

namespace sam
{
	/// @brief Memory data stream.
	/// 
	/// @see Stream.
	class SAM_COMMON_API CMemoryStream : public IStream
	{  
	public:
		/// @brief Constructor.
		///
		/// @param _pBuffer Pointer to an allocated block of memory.
		/// @param _iSize Size of the buffer.
		/// @param _bFreeOnClose true if we must to delete the memory when the stream is destroyed.
		CMemoryStream(void *_pBuffer, uint32 _iSize, bool _bFreeOnClose = false);

		/// @brief Destructor.
		~CMemoryStream(void);

		/// @brief Close the stream.
		void Close(void);

		/// @brief Read a block of bytes and store it in the buffer.
		/// 
		/// @param _pBuffer Pointer to an allocated block of memory.
		/// @param _iSize Size of bytes to read.
		/// @return the number of bytes read.
		uint32 Read(void* _pBuffer, uint32 _iSize);

		/// @brief Set the position in the stream.
		///
		/// @param _iOffset The new position.
		/// @param _eOrigin Seeking direction.
		/// @return the number of bytes sought.
		uint32 Seek(uint32 _iOffset, sam::ESeekDir _eOrigin);

		/// @brief Get the current position in the stream.
		/// 
		/// @return the current position in the stream.
		uint32 Tell(void);

		/// @brief Get the size of the stream.
		/// 
		/// @return the size of the stream.
		uint32 Size(void);

		/// @brief Get true if the end of the stream is reached.
		///
		/// @return true if the end of the stream is reached.
		bool Eof(void) const;

		/// @brief Get the data of the stream.
		///
		/// @return data of the stream.
		uint8 *Data(void);

	private:
		uint8 *m_pBuffer;   ///< Block of memory.
		uint32 m_iPosition; ///< Current position.
		uint32 m_iLength;   ///< Size of the memory block.
	};
}

#endif // __CMEMORY_STREAM__
