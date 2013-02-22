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
#include <common/SamPCH.h>
#include <common/system/System.h>

#include <intrin.h>
#include <Wbemidl.h>

#pragma comment (lib, "wbemuuid.lib")

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
		__cpuid(nCPUInfo, 0);

		((int32 *)cpu.m_sProcessor)[0] = nCPUInfo[EBX];
		((int32 *)cpu.m_sProcessor)[1] = nCPUInfo[EDX];
		((int32 *)cpu.m_sProcessor)[2] = nCPUInfo[ECX];

		/* cpu count */
		__cpuid(nCPUInfo, 1);
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
		/* system memory */
		MEMORYSTATUSEX oMemoryStatus;
		oMemoryStatus.dwLength = sizeof ( oMemoryStatus );
		GlobalMemoryStatusEx(&oMemoryStatus);
		p_nSystemMemory = (uint32)oMemoryStatus.ullTotalPhys / ( 1024 * 1024 );

		/* video memory */
		IWbemLocator *pLocator = NULL;
		HRESULT result = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_SERVER, IID_IWbemLocator, (LPVOID *) &pLocator);
		if(result != S_OK)
		{
			return;
		}

		IWbemServices *pService = NULL;
		result = pLocator->ConnectServer(
			L"ROOT\\CIMV2",			 // Object path of WMI namespace
			NULL,                    // User name. NULL = current user
			NULL,                    // User password. NULL = current
			0,                       // Locale. NULL indicates current
			NULL,                    // Security flags.
			0,                       // Authority (for example, Kerberos)
			0,                       // Context object 
			&pService                // pointer to IWbemServices proxy
			);
		if(result != S_OK)
		{
			pLocator->Release();     
			return;
		}

		result = CoSetProxyBlanket(
			pService,                    // Indicates the proxy to set
			RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
			RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
			NULL,                        // Server principal name 
			RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
			RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
			NULL,                        // client identity
			EOAC_NONE                    // proxy capabilities 
			);
		if(result != S_OK)
		{
			pService->Release();
			pLocator->Release();     
			return;
		}

		IEnumWbemClassObject* pEnumerator = NULL;
		result = pService->CreateInstanceEnum(L"Win32_VideoController", WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
		if(result != S_OK)
		{
			pService->Release();
			pLocator->Release();
			return;
		}

		ULONG uReturn = 0;
		IWbemClassObject *pclsObject = NULL;
		result = pEnumerator->Next(5000, 1, &pclsObject, &uReturn);
		if(result == S_OK) 
		{
			VARIANT oVideoMemory;
			result = pclsObject->Get(L"AdapterRAM", 0, &oVideoMemory, 0, 0);
			if( result == S_OK) 
			{
				p_nVideoMemory = oVideoMemory.intVal / ( 1024 * 1024 );
			}

			pclsObject->Release();
		}

		pEnumerator->Release();
		pService->Release();
		pLocator->Release();
	}

	// Initialize CPU and memory informations.
	void SSystem::Initialize()
	{	
		SetCPUInfo(m_oCPU);

		SetMemoryInfo(m_nSystemMemory, m_nVideoMemory);
	}
}

