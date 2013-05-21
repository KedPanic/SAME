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
#ifndef __SAM_CPU_H__
#define __SAM_CPU_H__

namespace sam
{
	/// @enum CPU features and informations.
	enum CPUID
	{
		e_CPUID_x86	= 1,
		e_CPUID_x64 = 2,
		e_CPUID_ARM = 4,
		e_CPUID_SS2 = 8,
		e_CPUID_SS3 = 16,
	};

	/// @brief CPU informations.
	struct SCPU
	{
		char m_sProcessor[13];	///< Vendor.
		uint16 m_nNbCores;		///< Core per processor.
		uint32 m_nInfos;		///< Bitmask of informations and features.
	};
}

#endif // __SAM_CPU_H__
