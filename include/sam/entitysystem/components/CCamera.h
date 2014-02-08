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
#ifndef __CCAMERA_COMPONENT__
#define __CCAMERA_COMPONENT__

#include <entitysystem/IComponent.h>

namespace sam
{
	namespace scene
	{
		/// @brief
		class SAM_ENTITYSYSTEM_API CCamera : public IComponent
		{
			DECLARE_COMPONENT(CCamera);

		public:
			/// @brief Default constructor.
			CCamera();

			/// @brief Sets clip plane distances.
			/// 
			/// @param p_fNearDist Near clipping plane distance.
			/// @param p_fFarDist Far clipping plane distance.
			void SetClipPlaneDistance(f32 p_fNearDist, f32 p_fFarDist);

			/// @brief Sets orthographic size.
			/// 
			/// @param p_fOrthoSize Orthographic size.
			void SetOrthographicSize(f32 p_fOrthoSize);

			/// @brief Sets camera to perspective mode.
			/// 
			/// @param p_bIsPerspective True to set the camera to perspective mode.
			void SetPerspective(bool p_bIsPerspective);

			/// @brief Retrieves view matrix
			/// 
			/// @return The view matrix.
			const Matrix44 &GetViewMatrix() const {return m_mViewMatrix;}

			/// @brief Retrieves projection matrix.
			/// 
			/// @return The projection matrix.
			const Matrix44 GetProjectionMatrix() const {return m_mProjMatrix;}

		private:
			bool m_bPerspective;	///< Type of projection. Perspective per default.
			f32  m_fFieldOfView;	///< Field of view in radian.
			f32	 m_fNearClipDist;	///< Near clipping plane distance. 0.1 per default.
			f32	 m_fFarClipDist;	///< Far clipping plane distance. 1000 per default.			
			f32  m_fAspectRatio;	///< Aspect ratio. 16/9 per default.

			f32	 m_fOrthoSize;		///< Orthographic size.
			int32 m_nWidth;			///< Viewport width.
			int32 m_nHeight;		///< Viewport height.

			Matrix44 m_mViewMatrix;	///< Computed view matrix.
			Matrix44 m_mProjMatrix;	///< Computed projection matrix.
		};
	}	
}

#endif // __CCAMERA_COMPONENT__