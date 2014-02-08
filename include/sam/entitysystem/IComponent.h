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
#ifndef __ICOMPONENT__
#define __ICOMPONENT__

namespace sam
{
	namespace scene
	{
		/// @brief Base struct for all components.
		struct SAM_ENTITYSYSTEM_API IComponent
		{
			uint32 m_nHandle;		///< [ pool index ][ type ]
			CGameObject *m_pOwmer;	///< Host of the component.
		};

		static const uint8 INVALID_REGISTER_INDEX = ~0;

		typedef IComponent *(*ComponentCreate)();
		typedef void (*ComponentUpdate)(f32 p_fDelta);

		/// @brief Register informations.
		struct SComponentRegistry
		{
			ComponentCreate m_pfCreate;	///< Callback used to create an instance of the specific component.
			ComponentUpdate m_pfUpdate; ///< Callback used to update all instances of a specific component.
		};

#define DECLARE_COMPONENT(ComponentClass)									\
		private:															\
			static sam::core::TObjectPool<ComponentClass> s_oObjectPool;	\
			static uint16  s_nRegisterIndex;								\
		public:																\
			static IComponent *Create();									\
			static void Update(f32 p_fDelta);								\
			static void Register(uint32 p_nMaxComponents);					\
			static uint16 GetType() {return s_nRegisterIndex;}

#define IMPLEMENT_COMPONENT(ComponentClass)																	\
		sam::core::TObjectPool<ComponentClass> ComponentClass::s_oObjectPool;								\
		uint16 ComponentClass::s_nRegisterIndex = INVALID_REGISTER_INDEX;									\
		IComponent *ComponentClass::Create()																\
		{																									\
			ComponentClass *pComponent = s_oObjectPool.Alloc();												\
			pComponent->m_nHandle = s_oObjectPool.GetPartitionIndex(pComponent) << 16 | s_nRegisterIndex;	\
			return pComponent;																				\
		}																									\
																											\
		void ComponentClass::Register(uint32 p_nMaxComponents)												\
		{																									\
			SAM_ASSERT(s_nRegisterIndex == INVALID_REGISTER_INDEX, "Component of type "#ComponentClass" is already registered");	\
																											\
			s_oObjectPool.Init(p_nMaxComponents);															\
																											\
			SComponentRegistry oRegister;																	\
			oRegister.m_pfCreate = &ComponentClass::Create;													\
			oRegister.m_pfUpdate = &ComponentClass::Update;													\
			s_nRegisterIndex = sam::g_Env->m_pComponentManager->RegisterComponent(&oRegister);				\
		}

		/// @brief Retrieves the component type from the handle.
		/// 
		/// @param p_nComponentHandle Component handle.
		/// @return Component type id.
		INLINE uint16 GetComponentType(uint32 p_nComponentHandle)
		{
			return p_nComponentHandle & 0xFFFF;
		}
	}
}

#endif // __ICOMPONENT__
