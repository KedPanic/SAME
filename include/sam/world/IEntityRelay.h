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
#ifndef __IEntityRelay__
#define __IEntityRelay__

#include <SamConfig.h>

namespace sam
{
	/// @enum Type of "part" of entity.
	enum EEntityRelay
	{
		ER_Render  = 1 << 0,
		ER_Sound   = 1 << 1,
		ER_Physics = 1 << 2,
		ER_User	   = 1 << 3,

		ER_Number  = 1 << 4,
	};

	/// @brief Interface for specialized entity which is delegated for specialized task.
	class IEntityRelay : public IAllocated
	{
	public:
		/// @brief Retrieves the type of entity.
		/// 
		/// @return The type of entity.
		virtual EEntityRelay GetType(void) const = 0;

		/// @brief Initialize the entity.
		/// 
		/// @param _Params Parameter to initialize.
		virtual void Initialize(SEntitySpawnParams &_Params) = 0;

		/// @brief Update the entity context.
		virtual void Update(void) = 0;
	};
}

#endif // __IEntityRelay__
