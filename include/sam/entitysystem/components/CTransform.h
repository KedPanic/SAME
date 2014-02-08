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
#ifndef __CTRANSFORM__
#define __CTRANSFORM__

#include <entitysystem/IComponent.h>

namespace sam
{
	namespace scene
	{
		/// @brief 
		class SAM_ENTITYSYSTEM_API CTransform : public IComponent
		{
			DECLARE_COMPONENT(CTransform);

		public:
			/// @brief Default constructor.
			CTransform();

			/// @brief Set position.
			/// 
			/// @param p_vPosition Position in the world space.
			void SetPosition(const Vector3 &p_vPosition);

			/// @brief Retrieves world space position.
			/// 
			/// @return World space position.
			Vector3 GetPosition() const {return m_vPosition;}

			/// @brief Set rotation.
			/// 
			/// @param p_qRotation Rotation.
			void SetRotation(const Quaternion &p_qRotation);

			/// @brief Retrieves world space rotation.
			/// 
			/// @return World space rotation.
			Quaternion GetRotation() const {return m_qRotation;}

			/// @brief Retrieve right vector (x-axis).
			/// 
			/// @return x-axis vector.
			const Vector3 &GetRight() const {return m_vRight;}

			/// @brief Retrieve up vector (y-axis).
			/// 
			/// @return y-axis vector.
			const Vector3 &GetUp() const {return m_vUp;}

			/// @brief Retrieve forward vector (z-axis).
			/// 
			/// @return z-axis vector.
			const Vector3 &GetForward() const {return m_vForward;}

			/// @brief Look at.
			/// 
			/// @param p_pTransform Object to loot at.
			/// @param p_vUp Upward direction.
			void LookAt(const CTransform *p_pTransform, const Vector3 &p_vUp = Vector3::up);

			/// @brief Look at.
			/// 
			/// @param p_vAt Point to look at.
			/// @param p_vUp Upward direction.
			void LookAt(const Vector3 &p_vAt, const Vector3 &p_vUp = Vector3::up);

			/// @brief Applies a rotation of euler angles degrees.
			/// 
			/// @param p_vAngles Vector of angles.
			void Rotate(const Vector3 &p_vAngles);

			/// @brief Applies a rotation of euler angles degrees.
			/// 
			/// @param p_fXAngle Angle around the x axis.
			/// @param p_fYAngle Angle around the y axis.
			/// @param p_fZAngle Angle around the z axis.
			void Rotate(const f32 &p_fXAngle, const f32 &p_fYAngle, const f32 &p_fZAngle);

			/// @brief Applies a rotation around axis by angle degrees.
			/// 
			/// @param p_vAxis Vector of angles.
			/// @param p_fAngle Angle to applies.
			void Rotate(const Vector3 &p_vAxis, const f32 p_fAngle);

		private:
			Quaternion	m_qRotation; ///< Rotation in world space.
			Vector3		m_vPosition; ///< Position in world space.

			Vector3		m_vRight;	///< x-axis.
			Vector3		m_vUp;		///< y-axis.
			Vector3		m_vForward;	///< z-axis.
		};
	}	
}

#endif // __CTRANSFORM__