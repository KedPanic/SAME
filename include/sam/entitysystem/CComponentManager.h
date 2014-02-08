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
#ifndef __CENTITY_MANAGER__
#define __CENTITY_MANAGER__

namespace sam
{
	namespace scene
	{
		class SAM_ENTITYSYSTEM_API CComponentManager : public IAllocated
		{
		public:
			/// @brief Default constructor.
			CComponentManager();
			~CComponentManager();

			/// @brief Create a game object.
			/// 
			/// @return Created game object.
			CGameObject *CreateGameObject();

			/// @brief Register a new component.
			/// 
			/// @param p_pRegister Information about the component.
			/// 
			/// @return Register index.
			uint16 RegisterComponent(SComponentRegistry *p_pRegister);

			/// @brief Create component specified by type.
			/// 
			/// @param p_nType Type of component.
			/// 
			/// @return Created component.
			IComponent *CreateComponent(uint16 p_nType);

			/// @brief Create component specified by type.
			///
			/// @return Created component.
			template<typename Component>
			Component *CreateComponent()
			{
				return (Component*)CreateComponent(Component::GetType());
			}

			/// @brief Prepare jobs
			void Update(f32 p_fDelta);

		private:
			typedef sam::tpl::Vector<SComponentRegistry> Components;
			Components m_aComponents;			

			typedef std::list<CGameObject*> GameObjects;
			GameObjects m_aGameObjects; ///< Array of created game objects.
		};
	}	
}

#endif // __CENTITY_MANAGER__