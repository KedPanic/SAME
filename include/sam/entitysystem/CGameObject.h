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
#ifndef __CGAME_OBJECT__
#define __CGAME_OBJECT__

namespace sam
{
	namespace scene
	{
		/// @brief 
		class SAM_ENTITYSYSTEM_API CGameObject : public IAllocated
		{
		public:
			CTransform *m_pTransform; ///< Fast access of the transform component.

			/// @brief Constructor.
			CGameObject();
			~CGameObject();

			/// @brief Retrieves the instance id.
			/// 
			/// @return The instance id.
			uint32 GetInstanceId() const;

			/// @brief Retrieves the attached component by type.
			/// 
			/// @param p_nType Type of component.
			/// 
			/// @return the component or null if not found.
			IComponent *GetComponent(uint32 p_nType);

			/// @brief Retrieves the attached component.
			/// 
			/// @return the component or null if not found.
			template<typename Component>
			Component *GetComponent() {return (Component*)GetComponent(Component::GetType());}

			/// @brief Add a new component of the specified type.
			/// 
			/// @param p_nType Type of component to add.
			/// 
			/// @return Added component.
			IComponent *AddComponent(uint16 p_nType);

			/// @brief Add a new component of the specified type.
			/// 
			/// @return Added component.
			template<typename Component>
			Component *AddComponent() {return (Component*)AddComponent(Component::GetType());}

		private:
			typedef std::vector<IComponent*> Components;
			Components m_aComponents; ///< Array of attached components.
		};
	}	
}

#endif // __CGAME_OBJECT__