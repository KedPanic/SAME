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
#ifndef __CBIT_STREAM__
#define __CBIT_STREAM__

namespace sam
{
	/// @brief Bit stream
	class SAM_COMMON_API CBitStream
	{
	public:
		CBitStream();
		~CBitStream();

		/// @brief Initialize the bit stream for write.
		/// 
		/// @param p_pBuffer Pointer to the buffer for read and write.
		/// @param p_nSize Size of the buffer.
		void Init(uint8 *p_pBuffer, uint32 p_nSize);

		/// @brief Initialize the bit stream for read only.
		/// 
		/// @param p_pBuffer Pointer to the buffer for read.
		/// @param p_nSize Size of the buffer.
		void Init(const uint8 *p_pBuffer, uint32 p_nSize);

		/// @brief Retrieve data.
		/// 
		/// @return Pointer to the write buffer.
		uint8 *GetData();

		/// @brief Retrieve data.
		/// 
		/// @return Pointer to the read buffer.
		const uint8 *GetData() const;

		/// @brief Retrieve the number of byte written.
		/// 
		/// @return The number of byte written.
		uint32 GetSize() const;

		//////////////////////////////////////////////////////////////////////////
		//								WRITE OPERATION							//
		//////////////////////////////////////////////////////////////////////////
		void WriteBits(int32 p_nValue, uint32 p_nNbBits);
		void WriteChar(char p_cValue);
		void WriteByte(int8 p_nValue);		
		void WriteShort(int16 p_nValue);
		void WriteInt(int32 p_nValue);
		void WriteString(const char *p_sBuffer, uint32 p_nSize);
		void WriteData(const uint8 *p_sBuffer, uint32 p_nSize);
		
		//////////////////////////////////////////////////////////////////////////
		//								READ OPERATION							//
		//////////////////////////////////////////////////////////////////////////
		int32 ReadBits(uint32 p_nNbBits);
		char ReadChar();
		int8 ReadByte();
		int16 ReadShort();
		int32 ReadInt();
		uint32 ReadString(char *p_sBuffer, uint32 p_nBufferSize);
		uint32 ReadData(uint8 *p_sBuffer, uint32 p_nBufferSize);

	private:
		uint32 m_nSize;			///< Buffer size.

		uint8 *m_pWriteBuffer;	///< Writable buffer.		
		uint32 m_nWritePos;		///< Number of bytes written.
		uint32 m_nWritePosBit;	///< Position in bit in the current position.

		const uint8 *m_pReadBuffer;	///< Readable buffer.		
		uint32 m_nReadPos;			///< Number of bytes read.
		uint32 m_nReadPosBit;		///< Position in bit in the current position.
	};

#include <common/io/CBitStream.inl>

}

#endif // __CBIT_STREAM__
