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
#ifndef __CSCENE__
#define __CSCENE__

namespace sam
{
	namespace scene
	{
		/// @brief A scene graph.
		class SAM_ENTITYSYSTEM_API CScene : public IAllocated
		{
		public:
			/// @brief Default constructor.
			CScene();
			~CScene();

			/// @brief Initialize the scene with a specific scene manager.
			/// 
			/// @param p_sSceneManagerName Name of the scene manager to use.
			/// @param p_nMaxGameObject Maximum of instantiable game object.
			/// 
			/// @remarks
			///		The name correspond to the plugin DLL name.
			void Initialize(const char *p_sSceneManagerName = "GenericSceneManager", uint32 p_nMaxGameObject = 10000);

			/// @brief Create an empty game object.
			/// 
			/// @return Created game object.
			CGameObject *CreateGameObject();

			/// @brief Create a game object with a camera component.
			/// 
			/// @return Created game object.
			CGameObject *CreateCamera();

			/// @brief Create a game object with a mesh component.
			/// 
			/// @return Created game object.
			CGameObject *CreateMesh();

			/// @brief Render the scene from the current camera.
			/// 
			/// @param p_pCamera Point of view.
			void Render(CCamera *p_pCamera);

		private:
			typedef core::TObjectPool<CGameObject> GameObjects;
			GameObjects m_aGameObjects; ///< Array of game object.

			Library m_pSceneManagerLibrary; ///< loaded library.
			struct SceneManager;
			SceneManager *m_pSceneManager; ///< Opaque structure of the scene manager.
		};
	}
}

#endif // __CSCENE__
