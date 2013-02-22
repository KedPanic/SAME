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
#ifndef __IENTITY__
#define __IENTITY__

#include "SamConfig.h"
#include "io/ISerializable.h"

namespace sam
{
	/// @brief Interface for entity
	class IEntity : public ISerializable
	{
	public:
		/// @brief Retrieves the factory, could be used to compare two entities
		/// 
		/// @return Pointer to the factory.
		virtual IEntityFactory *GetFactory(void) const = 0;

		/// @brief Retrieves the runtime unique Id.
		/// 
		/// @return The runtime unique Id.
		/// 
		/// @remarks
		///		Runtime unique Id is assigned by the entity system.
		virtual uint32 GetId(void) const = 0;

        /// @brief Retrieves the name of the entity (not unique).
        /// 
        /// @return The name of the entity.
        virtual const char *GetName(void) const = 0;

        /// @brief Flag the entity have to be removed to the next frame.
        virtual void Release(void) = 0;

        /// @brief Retrieves if this entity was marked for deletation.
        /// 
        /// @return True if the entity was marked for deletation.
        virtual bool IsGarbage(void) const = 0;

		/// @brief Serialize the object
		/// 
		/// @param _pContext Pointer to the context
		virtual void Serialize(ISerializer *_pContext) = 0;

		/// @brief Update the entity.
		/// 
		/// @param _fElapsedTime Elapsed time.
		virtual void Update(float _fElapsedTime) = 0;

		/// @brief Create context entity.
		/// 
		/// @param _eType Type of context.
		virtual void CreateRelay(EEntityRelay _eType) = 0;
	};
}

#endif
