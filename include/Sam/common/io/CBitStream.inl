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
// Retrieve data.
INLINE uint8 *CBitStream::GetData()
{
	return m_pWriteBuffer;
}

// Retrieve data.
INLINE const uint8 *CBitStream::GetData() const
{
	return m_pReadBuffer;
}

// Retrieve the number of byte written.
INLINE uint32 CBitStream::GetSize() const
{
	return m_nWritePos;
}

INLINE void CBitStream::WriteChar(char p_cValue)
{
	WriteBits(p_cValue, 8);
}

INLINE void CBitStream::WriteByte(int8 p_nValue)
{
	WriteBits(p_nValue, 8);
}

INLINE void CBitStream::WriteShort(int16 p_nValue)
{
	WriteBits(p_nValue, 16);
}

INLINE void CBitStream::WriteInt(int32 p_nValue)
{
	WriteBits(p_nValue, 32);
}

INLINE char CBitStream::ReadChar()
{
	return ReadBits(8);
}

INLINE int8 CBitStream::ReadByte()
{
	return ReadBits(8);
}

INLINE int16 CBitStream::ReadShort()
{
	return ReadBits(16);
}

INLINE int32 CBitStream::ReadInt()
{
	return ReadBits(32);
}
