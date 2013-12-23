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
#ifndef __CENTITYSYSTEM__
#define __CENTITYSYSTEM__

#include <SamConfig.h>
#include "io/ISerializable.h"

namespace sam
{
	/// @brief Entity system class, manage all entities of the game
	class IEntitySystem : public ISerializable
	{
		friend class CWorld;

	public:
		IMPLEMENT_SERIALIZABLE(entities);

		/// @brief Retrieves the entity factory registry.
		// 
		/// @return Pointer to the entity factory registry.
		virtual IEntityFactoryRegistry *GetFactoryRegistry(void) const = 0;

		/// @brief Initialize.
		virtual void Initialize() = 0;

		/// @brief Shutdown.
		virtual void Shutdown() = 0;

		/// @brief Update once every frame
		virtual void Update(float _fElapsedTime) = 0;

		/// @brief Spawn a new entity.
		///
		/// @param _Params Parameters to spawn a specified entities.
		///  
		/// @return The spawned entity or null if an error occurred.
		virtual IEntity *SpawnEntity(SEntitySpawnParams &_Params) = 0;

        /// @brief Retrieves entity by Id.
        /// 
        /// @param _Id Runtime unique id.
        /// 
        /// @return The entity or null if is not found.
        virtual IEntity *GetEntity(uint32 _Id) const = 0;

        /// @brief Retrieves the first entity with given name.
        /// 
        /// @param _sName Name of the entity.
        /// 
        /// @return The first entity with given name or null if is not found.
        virtual IEntity *GetEntityByName(const char *_sName) const = 0;

        /// @brief Remove entity by Id.
        /// 
        /// @param _Id Runtime unique Id.
        virtual void RemoveEntity(uint32 _Id) = 0;

        /// @brief Retrieves the number of entities.
        /// 
        /// @return Number of entities.
        virtual uint32 GetNumEntities(void) const = 0;
	};
}

extern "C"
{
	/// @brief Create entity system.
	/// 
	/// @param _pEnv Global environment variable.
	/// @remarks Should be implemented.
	SAM_ENTITY_API sam::IEntitySystem *CreateEntitySystem(sam::Env *_pEnv);

	/// @brief Destroy entity system.
	/// 
	/// @remarks Should be implemented.
	SAM_ENTITY_API void DestroyEntitySystem();
};

#endif  // __CENTITYSYSTEM__
