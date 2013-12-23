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
#ifndef __IPHYSICAL_WORLD__
#define __IPHYSICAL_WORLD__

#include <SamConfig.h>

namespace sam
{
    /// @brief Physical world parameters.
    struct SPhysicalWorldParams
    {
        Vector3 m_vGravity;
    };

    /// @brief Interface for physical world.
    class IPhysicalWorld : public IAllocated
    {
    public:
        /// @brief Initialize.        
        virtual void Initialize(void) = 0;

        /// @brief Shutdown it!
        virtual void Shutdown(void) = 0;

		/// @brief Create a new scene.
		/// 
		/// @param _Params Parameters to initialize it.
		/// 
		/// @remarks: Delete previous created scene.
		virtual void CreateScene(const SPhysicalWorldParams &_Params) = 0;

		/// @brief Destroy current scene.
		virtual void DestroyScene(void) = 0;

        /// @brief Create a physical body.
        /// 
        /// @param _BodyParams Parameters to create the physical body.
        /// 
        /// @return Pointer to the physical body or null if an error occurred.
        virtual IPhysicalBody *CreateBody(const SPhysicalBodyParams &_BodyParams) = 0;

		/// @brief Destroy the specified physical body.
		/// 
		/// @param _pBody Pointer to the physical body.
		virtual void ReleaseBody(IPhysicalBody *_pBody) = 0;

		/// @brief Update all bodies.
		/// 
		/// @param _fElapsedTime Elapsed time since the last frame.
		virtual void OnUpdate(float _fElapsedTime) = 0;

		/// @brief Draw.
		virtual void OnDraw(void) = 0;

    private:
    };
}

extern "C"
{
	/// @brief Create physical world.
	/// 
	/// @param _pEnv Global environment variable.
	/// @remarks Should be implemented.
	SAM_PHYSICS_API sam::IPhysicalWorld *CreatePhysicalWorld(sam::Env *_pEnv);

	/// @brief Destroy physical world.
	/// 
	/// @remarks Should be implemented.
	SAM_PHYSICS_API void DestroyPhysicalWorld();
};


#endif // __IPHYSICAL_WORLD__
