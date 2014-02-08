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
#ifndef __MATRIX__
#define __MATRIX__

#include "common/math/Vector.h"

namespace sam
{
    /// @brief Matrix 3x3
    template<typename T>
    struct Matrix33_T
    {
        T m00, m01, m02;
        T m10, m11, m12;
        T m20, m21, m22;

        /// @brief Default constructor.
        Matrix33_T() 
        {
            SetIdentity();
        }

		Matrix33_T(
			T m00, T m01, T m02,
			T m10, T m11, T m12,
			T m20, T m21, T m22
			)
			: m00(m00), m01(m01), m02(m02),
		   	  m10(m10), m11(m11), m12(m12),
			  m20(m20), m21(m21), m22(m22)
		{

		}

        /// @brief Identity.
        INLINE void SetIdentity(void)
        {
            m00 = 1.0f; m01 = 0.0f; m02 = 0.0f;
            m10 = 0.0f; m11 = 1.0f; m12 = 0.0f;
            m20 = 0.0f; m21 = 0.0f; m22 = 1.0f;
        }    
    };

    //==================================//
    //              TYPEDEF             //
    //==================================//
    typedef Matrix33_T<f32> Matrix33;
    typedef Matrix33_T<f64> Matrix33_f64; // double-precision

    /// @brief Matrix 3x4
    template <typename T>
    struct Matrix34_T
    {
        T m00, m01, m02, m03;
        T m10, m11, m12, m13;
        T m20, m21, m22, m23;

        /// @brief Default constructor.
        Matrix34_T(void)
        {
            SetIdentity();
        }

        /// @brief Identity.
        INLINE void SetIdentity(void)
        {
            m00 = 1.0f; m01 = 0.0f; m02 = 0.0f; m03 = 0.0f;
            m10 = 0.0f; m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
            m20 = 0.0f; m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
        }

        /// @brief Set translation vector.
        /// 
        /// @param _vPosition Position vector.
        INLINE void SetTranslation(const Vector3_T<T> &_vPosition)
        {
            m03 = _vPosition.x;
            m13 = _vPosition.y;
            m23 = _vPosition.z;
        }

        /// @brief Retrieves current translation vector.
        /// 
        /// @return Current translation vector.
        INLINE Vector3_T<T> GetTranslation(void) const 
        {
            return Vector3_T<T>(m03, m13, m23);
        }
    };

    //==================================//
    //              TYPEDEF             //
    //==================================//
    typedef Matrix34_T<f32> Matrix34;
    typedef Matrix34_T<f64> Matrix34_f64; // double-precision



    /// @brief Matrix 4x4
    template<typename T>
    struct Matrix44_T
    {
        T m00, m01, m02, m03;
        T m10, m11, m12, m13;
        T m20, m21, m22, m23;
        T m30, m31, m32, m33;

        /// @brief Default constructor.
        Matrix44_T(void) 
        {
            SetIdentity();
        }

		Matrix44_T(
			T m00, T m01, T m02, T m03,
			T m10, T m11, T m12, T m13,
			T m20, T m21, T m22, T m23,
			T m30, T m31, T m32, T m33
			)
			: m00(m00), m01(m01), m02(m02), m03(m03), m10(m10), m11(m11), m12(m12), m13(m13), m20(m20), m21(m21), m22(m22), m23(m23), m30(m30), m31(m31), m32(m32), m33(m33)
		{

		}

        /// @brief Identity.
        INLINE void SetIdentity(void)
        {
            m00 = 1.0f; m01 = 0.0f; m02 = 0.0f; m03 = 0.0f;
            m10 = 0.0f; m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
            m20 = 0.0f; m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
            m30 = 0.0f; m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
        }

		/// @brief Transpose.
		INLINE Matrix44_T<T> Transpose() const
		{
			return Matrix44_T<T>(
				m00, m10, m20, m30,
				m01, m11, m21, m31,
				m02, m12, m22, m32,
				m03, m13, m23, m33
				);
		}
    };

    //==================================//
    //              TYPEDEF             //
    //==================================//
    typedef Matrix44_T<f32> Matrix44;
    typedef Matrix44_T<f64> Matrix44_f64; // double-precision
}

#endif // __MATRIX__
