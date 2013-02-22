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
#ifndef __GUIDUTIL__
#define __GUIDUTIL__

namespace sam
{
	/// @brief GUID is used to save and load game objects.
	namespace guid
	{
		/// @brief Redefine GUID windows api
		struct GUID
		{
			unsigned long  Data1;
			unsigned short Data2;
			unsigned short Data3;
			unsigned char  Data4[8];
		};

		/// @brief Generate a GUID.
		/// 
		/// @return a new GUID.
		extern GUID Generate(void);

		/// @brief Generate a GUID from string.
		/// 
		/// @param _sGUID GUID string
		extern GUID FromString(const String &_sGUID);

		/// @brief Generate a GUID from uint64.
		/// 
		/// @param _iGUID GUID uint64
		extern String ToString(uint64 _iGUID);
	}
}

#endif
