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
#ifndef __CSIGNAL_MANAGER__
#define __CSIGNAL_MANAGER__

namespace sam
{
	/// @brief A signal is an message to send to the connected slot.
	///
	/// @see sam::CSignalDispatcher
	class ISignal
	{
	public:
		/// @brief Default constructor.
		ISignal() {}
		virtual ~ISignal() {}

		/// @brief Retrieves the type of the signal.
		///
		/// @return Type of the signal.
		virtual uint32 GetType() const = 0;
	};	

	class SAM_COMMON_API CSignalManager : public IAllocated
	{
	public:
		CSignalManager();
		~CSignalManager();

		template<class Slot, typename Func>
		void Connect(uint32 p_nSignalType, Slot *p_pSlot, Func p_pFunc);

		template<class Slot>
		void Disconnect(uint32 p_nSignalType, Slot *p_pSlot);

		/// @brief Add a signal in the queue.
		/// 
		/// @param p_pSignal Signal to add in the queue.
		void QueueSignal(ISignal *p_pSignal);

		/// @brief Dispatch all pending signal.
		void Dispatch();

	private:
		struct Hidden
		{
			virtual ~Hidden() {}
			virtual void Call(ISignal *) = 0;
		};

		template<class Slot>
		struct Connection : public Hidden
		{			
			Slot *m_pSlot;

			typedef void (Slot::*OnSignal)(ISignal *);
			OnSignal m_pFunction;

			Connection(Slot *p_pSlot, OnSignal p_pFunction)
				: m_pSlot(p_pSlot), m_pFunction(p_pFunction) {}

			void Call(ISignal *p_pSignal)
			{
				return (m_pSlot->*m_pFunction)(p_pSignal);
			}			
		};

		typedef std::list<Hidden *> Slots;
		typedef std::map<uint32, Slots> Connections;
		Connections m_aConnections; ///< Array of connection per signal.

		typedef std::queue<ISignal *> Signals;
		Signals m_aSignals; ///< Array of signal to propagate.		
	};

	#include <common/thread/CSignalManager.inl>
}

#endif // __CSIGNAL_MANAGER__
