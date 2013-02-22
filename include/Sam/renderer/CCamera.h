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
#ifndef __CCAMERA__
#define __CCAMERA__

#include "common/SamConfig.h"
#include "common/math/Math.h"
#include "common/math/Vector.h"
#include "common/math/Matrix.h"

namespace sam
{
    /// @enum Frustum plane.
    enum EFrustumPlane
    {
        FP_Near,
        FP_Far,
        FP_Left,
        FP_Right,
        FP_Top,
        FP_Bottom,
        FP_NbPlanes,
    };

	/// @brief Camera.
    /// 
    /// @remarks
    ///     Right-handed system. X-Axis right, Y-Axis up, Z-Axis out of the screen.
    ///
    ///     y-axis
    ///       ^
    ///       |
    ///       |
    ///       |
    ///       + ---------> x-axis
    ///      /
    ///     /
    ///    /
    /// z-axis
    class CCamera : public IAllocated
    {
	public:
        /// @enum Type of projection.
        enum EProjectionType
        {
            PT_Orthographic,
            PT_Perspective,
        };

		/// @brief Constructor.
        CCamera(void) 
            : m_eType(PT_Perspective), m_nWidth(800), m_nHeight(600), m_fNear(1.0f), m_fFar(1000.0f)
        {}

		/// @brief Destructor.
		~CCamera(void) {}

		/// @brief Set position.
		/// 
		/// @param _vPosition New position.
		INLINE void SetPosition(const Vector3 &_vPosition)
        {
            m_vOrigin = _vPosition;
        }

		/// @brief Retrieves current position.
		/// 
		/// @return Current position.
		INLINE Vector3 GetPosition(void) const
        {
            return m_vOrigin;
        }

        /// @brief Look at.
        /// 
        /// @param _vPoint Point to look.
        INLINE void LookAt(const Vector3 &_vPoint);

        /// @brief Look at.
        /// 
        /// @param _vEye Eye vector.
        /// @param _vAt At vector.
        /// @param _vUp Up vector.
        INLINE void LookAt(const Vector3 &_vEye, const Vector3 &_vAt, const Vector3 &_vUp);

        /// @brief Retrieves projection matrix.
        /// 
        /// @param _mMatrix Matrix to set.
        INLINE void GetModelViewMatrix(Matrix44 &_mMatrix) const;

        //==========================================//
        //                  FRUSTUM                 //
        //==========================================//

        /// @brief Retrieves projection matrix.
        /// 
        /// @return Projection matrix.
        INLINE const Matrix44 &GetProjectionMatrix(void) const;

        /// @brief Sets camera to orthographic mode.
        /// 
        /// @param _nWidth Width of frustum.
        /// @param _nHeight height of frustum.
        /// @param _fNear Near plane.
        /// @param _fFar Far plane.
        void SetOrthographic(uint32 _nWidth, uint32 _nHeight, f32 _fNear = 0.5f, f32 _fFar = 1000.0f);

        /// @brief Sets camera to perspective mode.
        /// 
        /// @param _nWidth Width of frustum.
        /// @param _nHeight height of frustum.
        /// @param _fFOV Field of view on Y-Axis in degree (converted in radian internally).
        /// @param _fNear Near plane.
        /// @param _fFar Far plane.
        void SetPerspective(uint32 _nWidth, uint32 _nHeight, f32 _fFOV = 75.0f, f32 _fNear = 0.5f, f32 _fFar = 1000.0f);

	private:
        EProjectionType m_eType; ///< Perspective per default.

        // Model View.
        Vector3 m_vRight, m_vUp, m_vAt;
        Vector3 m_vOrigin;

        //==========================================//
        //                  FRUSTUM                 //
        //==========================================//
        f32 m_fFov;
        int m_nWidth;
        int m_nHeight;
        f32 m_fProjectionRatio;
//        Plane m_aPlanes[FP_NbPlanes];
        f32 m_fNear;
        f32 m_fFar;

        f32 m_fTop;
        f32 m_fBottom;
        f32 m_fRight;
        f32 m_fLeft;
        Matrix44 m_mProjectionMatrix;  

        /// @brief Update projection matrix.
        INLINE void UpdateOrthographic(void);
        INLINE void UpdatePerspective(void);
    };

#include "renderer/CCamera.inl"
}

#endif // __CCAMERA__
