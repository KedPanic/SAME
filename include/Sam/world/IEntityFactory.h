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
#ifndef __IENTITYFACTORY__
#define __IENTITYFACTORY__

#include "math/Vector.h"

namespace sam
{
    /// @brief Parameters to spawn a specified entities.
    struct SEntitySpawnParams : public IAllocated
    {
        char *m_pFactoryName;		///< Name of the creator.
		char *m_pName;				///< Name of the entity.

        Vector3 m_vPosition;        ///< Initial position.

		uint32 m_nContextFlags;		///< Flags.
    };

    /// @brief This class is used to create a specified type of entity 
    /// 
    /// @remarks 
    ///     This class is shared by several entities. We can use the pointer
    ///     of the factory to compare two entities if it is the same type.
    class IEntityFactory :  public IAllocated
    {
    public:
        /// @brief Retrieves the name of the entity class (have to be unique).
        /// 
        /// @return The name of the entity class.
        virtual const char *GetName(void) const = 0;

		/// @brief Create a new entity.
		/// 
		/// @return The new entity or null.
		virtual IEntity *CreateEntity(SEntitySpawnParams &_sParams) const = 0;
    };

    /// @brief This interface is to register all spawnable entities.
    /// 
    /// @remarks
    ///     Every spawnable entities have to be registered.
    class IEntityFactoryRegistry : public IAllocated
    {
    public:
        /// @brief Register a new entity factory.
        /// 
        /// @param _pFactory The factory used to spawn the entities.
        virtual void RegisterFactory(IEntityFactory *_pFactory) = 0;

        /// @brief Unregister an entity factory.
        /// 
        /// @param _pFactory The factory to removed.
        virtual void UnregisterFactory(IEntityFactory *_pFactory) = 0;

        /// @brief Retrieves an entity factory by name.
        /// 
        /// @param _sName Name of the factory.
        /// 
        /// @return The factory or null if class not found.
        virtual IEntityFactory *GetFactory(const char *_sName) const = 0;

        /// @brief Retrieves the number of registered entity factory.
        /// 
        /// @return The number of registered entity factory.
        virtual int GetFactoryCount(void) const = 0;
    };
}

#endif // __IENTITYFACTORY__
