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
#ifndef __IWORLD__
#define __IWORLD__

#include "io/ISerializable.h"

namespace sam
{
	/// @brief World interface, manage all objects of the game
	class IWorld : public ISerializable
	{
	public:		
		IMPLEMENT_SERIALIZABLE(world);

		/// @brief Load level.
		/// 
		/// @param _sLevelName Name of the level to load.
		virtual void LoadLevel(const String &_sLevelName) = 0;

		/// @brief Unload current level.
		virtual void UnloadLevel() = 0;

		/// @brief Initialize.
		virtual void Initialize() = 0;

		/// @brief Shutdown.
		virtual void Shutdown() = 0;

		/// @brief Update once every frame
		virtual void Update(float _fElapsedTime) = 0;
	};
}

#endif  // __IWORLD__
