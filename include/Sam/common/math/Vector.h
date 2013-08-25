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
#ifndef __VECTOR__
#define __VECTOR__

namespace sam
{
    /// @brief Vector in 3 dimensions space.
    template<typename T>
    struct Vector3_T : public IAllocated
    {
        T x, y, z; ///< Coordinate 

        /// @brief Default constructor.
        Vector3_T(void) : x(0.0f), y(0.0f), z(0.0f) {}

        /// @brief Constructor.
        Vector3_T(T _fX, T _fY, T _fZ)
            : x(_fX), y(_fY), z(_fZ) {}

        /// @brief Retrieves the value by index.
        /// 
        /// @param _iIndex Index to get the value.
        /// 
        /// @return The value.
        T operator[](int _iIndex) const {SAM_ASSERT(_iIndex >= 0 && _iIndex <= 2, "bad value"); return ((T*)this)[_iIndex];}
        T &operator[](int _iIndex) {SAM_ASSERT(_iIndex >= 0 && _iIndex <= 2, "bad value"); return ((T*)this)[_iIndex];}

        /// @brief Normalize.
        INLINE void Normalize(void)
        {
            T fInvLength = sam::inv_sqrt_safe_fast(x * x + y * y + z * z);

            x *= fInvLength;
            y *= fInvLength;
            z *= fInvLength;
        }    
    };

    //==================================//
    //              TYPEDEF             //
    //==================================//
    typedef Vector3_T<f32> Vector3;
    typedef Vector3_T<f64> Vector3_f64; // double-precision


    //==================================//
    //              OPERATION           //
    //==================================//

    /// @brief Subtraction.
    template<typename T1, typename T2>
    INLINE Vector3_T<T1> operator - (const Vector3_T<T1> &_v0, const Vector3_T<T2> &_v1)
    {
        return Vector3_T<T1>(_v0.x - _v1.x, _v0.x - _v1.x, _v0.x - _v1.x);
    }

    /// @brief Cross-product.
    template<typename T1, typename T2>
    INLINE Vector3_T<T1> cross(const Vector3_T<T1> &_v0, const Vector3_T<T2> &_v1)
    {
        return Vector3_T<T1>
            (
            _v0.y * _v1.z - _v0.z * _v1.y,
            _v0.z * _v1.x - _v0.x * _v1.z,
            _v0.x * _v1.y - _v0.y * _v1.x
            );
    }

    /// @brief Dot-product.
    template<typename T1, typename T2>
    INLINE T1 dot(const Vector3_T<T1> &_v0, const Vector3_T<T2> &_v1)
    {
        return _v0.x * _v1.x + _v0.y * _v1.y + _v0.z * _v1.z;
    }
}

#endif // __VECTOR__
