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
#ifndef __QUATERNION__
#define __QUATERNION__

#include "common/math/Vector.h"

namespace sam
{
	/// @brief Matrix 3x3
	template<typename T>
	struct Quaternion_T
	{
		T x, y, z, w;

		/// @brief Default constructor.
		Quaternion_T() 
			: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
		{
		}

		Quaternion_T(T x, T y, T z, T w) 
			: x(x), y(y), z(z), w(w)
		{
		}

		/// @brief Transform quaternion to rotation matrix.
		/// 
		/// @return Rotation matrix.
		INLINE Matrix33 ToMatrix()
		{
			T xx = x * x;
			T xy = x * y;
			T xz = x * z;
			T xw = x * w;

			T yy = y * y;
			T yz = y * z;
			T yw = y * w;

			T zz = z * z;		
			T zw = z * w;

			return Matrix33(
				1 - 2 * (yy + zz),	2 * (xy - zw),		2 * (xz + yw),
				2 * (xy + zw),		1 - 2 * (xx + zz),	2 * (yz - xw),
				2 * (xz - yw),		2 * (yz + xw),		1 - 2 * (xx + yy)
				);
		}
	};

	//==================================//
	//              TYPEDEF             //
	//==================================//
	typedef Quaternion_T<f32> Quaternion;
	typedef Quaternion_T<f64> Quaternion_f64; // double-precision
}

#endif // __QUATERNION__
