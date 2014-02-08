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
#include "components/CCamera.h"

#include "CComponentManager.h"
#include "components/CTransform.h"
#include "CGameObject.h"

namespace sam
{
	namespace scene
	{
		IMPLEMENT_COMPONENT(CCamera);

		//////////////////////////////////////////////////////////////////////////
		//					TRANSFORM SYSTEM IMPLEMENTATION						//
		//////////////////////////////////////////////////////////////////////////
		void CCamera::Update(f32 p_fDelta)
		{
			for(uint32 nIndex = 0; nIndex < s_oObjectPool.GetCount(); ++nIndex)
			{
				CCamera *pCamera = s_oObjectPool[nIndex];
				CTransform *pTransform = pCamera->m_pOwmer->m_pTransform;

				Vector3 vPosition = pTransform->GetPosition();

				// update view matrix.
				{
					Matrix44 &mViewMatrix = pCamera->m_mViewMatrix;
					const Vector3 &vRight = pTransform->GetRight();
					const Vector3 &vUp = pTransform->GetUp();
					const Vector3 &vForward = pTransform->GetForward();

					mViewMatrix.m00 = vRight.x,		mViewMatrix.m01 = vRight.y,		mViewMatrix.m02 = vRight.z,		mViewMatrix.m03 = -dot<f32, f32>(vRight, vPosition);
					mViewMatrix.m10 = vUp.x,		mViewMatrix.m11 = vUp.y,		mViewMatrix.m12 = vUp.z,		mViewMatrix.m13 = -dot<f32, f32>(vUp, vPosition);
					mViewMatrix.m20 = vForward.x,	mViewMatrix.m21 = vForward.y,	mViewMatrix.m22 = vForward.z,	mViewMatrix.m23 = -dot<f32, f32>(vForward, vPosition);
					mViewMatrix.m30 = 0.0f,			mViewMatrix.m31 = 0.0f,			mViewMatrix.m32 = 0.0f,			mViewMatrix.m33 = 1.0f;
				}

				// update projection matrix.
				if(pCamera->m_bPerspective)
				{
					Matrix44 &mProjMatrix = pCamera->m_mProjMatrix;

					f32 fTop = pCamera->m_fNearClipDist * tan(pCamera->m_fFieldOfView * 0.5f);
					f32 fBottom = -fTop;
					f32 fRight = fTop * pCamera->m_fAspectRatio;
					f32 fLeft = -fRight;

					mProjMatrix.m00 = (2.0f * pCamera->m_fNearClipDist) / (fRight - fLeft);
					mProjMatrix.m01 = 0.0f;
					mProjMatrix.m02 = (fRight + fLeft) / (fRight - fLeft); // position on x-axis
					mProjMatrix.m03 = 0.0f;

					mProjMatrix.m10 = 0.0f;
					mProjMatrix.m11 = (2.0f * pCamera->m_fNearClipDist) / (fTop - fBottom);
					mProjMatrix.m12 = (fTop + fBottom) / (fTop - fBottom); // position on y-axis
					mProjMatrix.m13 = 0.0f;

					mProjMatrix.m20 = 0.0f;
					mProjMatrix.m21 = 0.0f;
					mProjMatrix.m22 = -(pCamera->m_fFarClipDist + pCamera->m_fNearClipDist) / (pCamera->m_fFarClipDist - pCamera->m_fNearClipDist);
					mProjMatrix.m23 = 2.0f * (pCamera->m_fFarClipDist * pCamera->m_fNearClipDist) / (pCamera->m_fNearClipDist - pCamera->m_fFarClipDist);

					mProjMatrix.m30 = 0.0f;
					mProjMatrix.m31 = 0.0f;
					mProjMatrix.m32 = -1.0f;
					mProjMatrix.m33 = 0.0f;
				}
				else
				{
					Matrix44 &mProjMatrix = pCamera->m_mProjMatrix;

					f32 fRight = pCamera->m_fAspectRatio * pCamera->m_fOrthoSize;
					f32 fLeft = -fRight;
					f32 fTop = pCamera->m_fOrthoSize;
					f32 fBottom = -fTop;

					mProjMatrix.m00 = 2.0f / (fRight - fLeft);
					mProjMatrix.m01 = 0.0f;
					mProjMatrix.m02 = (fRight + fLeft) / (fRight - fLeft);
					mProjMatrix.m03 = 0.0f;

					mProjMatrix.m10 = 0.0f;
					mProjMatrix.m11 = 2.0f / (fTop - fBottom);
					mProjMatrix.m12 = 0.0f;
					mProjMatrix.m13 = (fTop + fBottom) / (fTop - fBottom);

					mProjMatrix.m20 = 0.0f;
					mProjMatrix.m21 = 0.0f;
					mProjMatrix.m22 = -2.0f / (pCamera->m_fFarClipDist - pCamera->m_fNearClipDist);
					mProjMatrix.m23 = (pCamera->m_fFarClipDist * pCamera->m_fNearClipDist) / (pCamera->m_fFarClipDist - pCamera->m_fNearClipDist);

					mProjMatrix.m30 = 0.0f;
					mProjMatrix.m31 = 0.0f;
					mProjMatrix.m32 = 0.0f;
					mProjMatrix.m33 = 1.0f;
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////

		// Default constructor.
		CCamera::CCamera() : 
			m_bPerspective(true),
			m_fFieldOfView(45.0f * DEG2RAD),
			m_fNearClipDist(0.1f),
			m_fFarClipDist(1000.f),
			m_fAspectRatio((f32)sam::g_Env->pRenderWindow->GetWidth() /sam::g_Env->pRenderWindow->GetHeight()),
			m_fOrthoSize(5.0f),
			m_nWidth(sam::g_Env->pRenderWindow->GetWidth()),
			m_nHeight(sam::g_Env->pRenderWindow->GetHeight())
		{			
		}

		// Sets clip plane distances.
		void CCamera::SetClipPlaneDistance(f32 p_fNearDist, f32 p_fFarDist)
		{
			m_fNearClipDist = p_fNearDist;
			m_fFarClipDist = p_fFarDist;
		}

		// Sets orthographic size.
		void CCamera::SetOrthographicSize(f32 p_fOrthoSize)
		{
			m_fOrthoSize = p_fOrthoSize;
		}

		// Sets camera to perspective mode.
		void CCamera::SetPerspective(bool p_bIsPerspective)
		{
			m_bPerspective = p_bIsPerspective;
		}
	}	
}
