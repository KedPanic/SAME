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
#include "thread/CAtomic.h"
#include <Windows.h>
#include <Winnt.h>
namespace sam
{
	CAtomicInteger::CAtomicInteger()
		: m_nValue(0)
	{

	}

	int32 CAtomicInteger::Increment()
	{
		return InterlockedIncrement(&m_nValue);
	}

	int32 CAtomicInteger::Decrement()
	{
		return InterlockedDecrement(&m_nValue);
	}

	int32 CAtomicInteger::Add(int32 p_nValue)
	{
		InterlockedExchangeAdd(&m_nValue, p_nValue);
		return m_nValue;
	}

	int32 CAtomicInteger::Sub(int32 p_nValue)
	{
		InterlockedExchangeAdd(&m_nValue, -p_nValue);
		return m_nValue;
	}

	int32 CAtomicInteger::GetValue()
	{
		return m_nValue;
	}

	void CAtomicInteger::SetValue(int32 p_nValue)
	{
		InterlockedExchange(&m_nValue, p_nValue);
	}
}