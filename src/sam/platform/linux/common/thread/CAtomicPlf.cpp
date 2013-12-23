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

#ifdef CONFIG_SMP
#   define LOCK_PREFIX \
                 ".section .smp_locks,\"a\"\n"   \
                 "  .align 8\n"                  \
                 "  .quad 661f\n" /* address */  \
                 ".previous\n"                   \
                 "661:\n\tlock; "

#else /* ! CONFIG_SMP */
#   define LOCK_PREFIX ""
#endif

namespace sam
{
	CAtomicInteger::CAtomicInteger()
		: m_nValue(0)
	{

	}

	int32 CAtomicInteger::Increment()
	{
		asm volatile(LOCK_PREFIX "incl %0"
                       : "+m" (m_nValue));

        return m_nValue;
	}

	int32 CAtomicInteger::Decrement()
	{
		asm volatile(LOCK_PREFIX "decl %0"
                       : "+m" (m_nValue));

        return m_nValue;
	}

	int32 CAtomicInteger::Add(int32 p_nValue)
	{
		asm volatile(LOCK_PREFIX "addl %1,%0"
                       : "+m" (m_nValue)
                       : "ir" (p_nValue));

        return m_nValue;
	}

	int32 CAtomicInteger::Sub(int32 p_nValue)
	{
		asm volatile(LOCK_PREFIX "subl %1,%0"
                       : "+m" (m_nValue)
                       : "ir" (p_nValue));

        return m_nValue;
	}

	int32 CAtomicInteger::GetValue()
	{
		return m_nValue;
	}

	void CAtomicInteger::SetValue(int32 p_nValue)
	{
		m_nValue = p_nValue;
	}
}
