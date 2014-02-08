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
#include "SamEntitySystemPCH.h"
#include "CComponentManager.h"
#include "components/CTransform.h"

namespace sam
{
	namespace scene
	{
		IMPLEMENT_COMPONENT(CTransform);

		//////////////////////////////////////////////////////////////////////////
		//					TRANSFORM SYSTEM IMPLEMENTATION						//
		//////////////////////////////////////////////////////////////////////////
		void CTransform::Update(f32 p_fDelta)
		{
			for(uint32 nIndex = 0; nIndex < s_oObjectPool.GetCount(); ++nIndex)
			{
				CTransform *pTransform = s_oObjectPool[nIndex];
			}
		}
		//////////////////////////////////////////////////////////////////////////

		/// @brief Default constructor.
		CTransform::CTransform()
			: m_vPosition(Vector3::zero),
			m_vRight(Vector3::right),
			m_vUp(Vector3::up),
			m_vForward(Vector3::forward)
		{

		}

		// Set position.
		void CTransform::SetPosition(const Vector3 &p_vPosition)
		{
			m_vPosition = p_vPosition;
		}

		// Set rotation.
		void CTransform::SetRotation(const Quaternion &p_qRotation)
		{
			m_qRotation = p_qRotation;
		}

		// Look at.
		void CTransform::LookAt(const CTransform *p_pTransform, const Vector3 &p_vUp /*= Vector3::up*/)
		{
			LookAt(p_pTransform->GetPosition(), p_vUp);
		}

		// Look at.
		void CTransform::LookAt(const Vector3 &p_vAt, const Vector3 &p_vUp /*= Vector3::up*/)
		{
			m_vForward = m_vPosition - p_vAt;		m_vForward.Normalize();
			m_vRight = cross(p_vUp, m_vForward);	m_vRight.Normalize();
			m_vUp = cross(m_vForward, m_vRight);	m_vUp.Normalize();
		}

		// Applies a rotation of euler angles degrees.
		void CTransform::Rotate(const Vector3 &p_vAngles)
		{

		}

		// Applies a rotation of euler angles degrees.
		void CTransform::Rotate(const f32 &p_fXAngle, const f32 &p_fYAngle, const f32 &p_fZAngle)
		{

		}

		// Applies a rotation around axis by angle degrees.
		void CTransform::Rotate(const Vector3 &p_vAxis, const f32 p_fAngle)
		{

		}
	}	
}
