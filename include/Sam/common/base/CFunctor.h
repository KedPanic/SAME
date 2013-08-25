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
#ifndef __CFUNCTOR__
#define __CFUNCTOR__

namespace sam
{	
	template<class Class, typename Return>
	class CFunctor0
	{
	public:
		typedef Return (Class::*Function)();

		CFunctor0(Class *p_pThis, Function p_pFunction)
			: m_pThis(p_pThis), m_pFunction(p_pFunction) {}

		Return Call()
		{
			return (m_pThis->*m_pFunction)();
		}
	private:
		Class *m_pThis;
		Function m_pFunction;
	};

	template<class Class, typename Return, typename Arg1>
	class CFunctor1
	{
	public:
		typedef Return (Class::*Function)(Arg1);

		CFunctor1(Class *p_pThis, Function p_pFunction)
			: m_pThis(p_pThis), m_pFunction(p_pFunction) {}

		Return Call(Arg1 p_oArg)
		{
			return (m_pThis->*m_pFunction)(p_oArg);
		}

	private:
		Class *m_pThis;
		Function m_pFunction;
	};
}
#endif // __CFUNCTOR__
