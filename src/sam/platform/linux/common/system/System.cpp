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
#include <common/system/System.h>

#include <time.h>
#include <cpuid.h>

namespace sam
{
	void SetCPUInfo(SCPU &cpu)
	{
		// Local enum for more readable.
		enum Register
		{
			EAX,
			EBX,
			ECX,
			EDX,
		};

		// Retrieves CPU info.
		int32 nCPUInfo[4];

		/* vendor */
		__cpuid(0, nCPUInfo[EAX], nCPUInfo[EBX], nCPUInfo[ECX], nCPUInfo[EDX]);

		((int32 *)cpu.m_sProcessor)[0] = nCPUInfo[EBX];
		((int32 *)cpu.m_sProcessor)[1] = nCPUInfo[EDX];
		((int32 *)cpu.m_sProcessor)[2] = nCPUInfo[ECX];

		/* cpu count */
		__cpuid(1, nCPUInfo[EAX], nCPUInfo[EBX], nCPUInfo[ECX], nCPUInfo[EDX]);
		cpu.m_nNbCores = nCPUInfo[EBX] >> 16 & 0xFF;

		/* features */
		if(nCPUInfo[EDX] & 1 << 26)
		{
			cpu.m_nInfos |= e_CPUID_SS2;
		}

		if(nCPUInfo[ECX] & 1 << 0)
		{
			cpu.m_nInfos |= e_CPUID_SS3;
		}

#if defined(SAM_32BITS)
		cpu.m_nInfos |= e_CPUID_x86;
#elif defined(SAM_64BITS)
		cpu.m_nInfos |= e_CPUID_x64;
#endif
	}

	void SetMemoryInfo(uint32 &p_nSystemMemory, uint32 &p_nVideoMemory)
	{
		p_nSystemMemory = sysconf( _SC_PHYS_PAGES ) * sysconf( _SC_PAGESIZE );
	}

	// Initialize CPU and memory informations.
	void SSystem::Initialize()
	{
		SetCPUInfo(m_oCPU);

		SetMemoryInfo(m_nSystemMemory, m_nVideoMemory);
	}

	// Convert a timestamp to string.
	void TimeStampToStr(Time p_oTimestamp, char *p_sTimeString)
	{
		SAM_TRAP(p_sTimeString != NULL && strlen(p_sTimeString) >= 19);

		tm *pTime = localtime(&p_oTimestamp);

		int32 nHour = pTime->tm_hour;
		if(nHour > 12)
		{
			nHour = nHour - 12;
		}

		// convert the time stamp to string.
		sprintf(p_sTimeString, "%d-%02d-%02dT%02d:%02d:%02d", pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday, nHour, pTime->tm_min, pTime->tm_sec);
	}
}

