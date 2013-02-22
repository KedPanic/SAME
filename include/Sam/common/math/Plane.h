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
#ifndef __PLANE__
#define __PLANE__

#include <math/Vector.h>

/// @brief Plane.
template<typename T>
struct Plane_T
{
    Vector3_T<T> m_vNormal; ///< Normal vector (A, B, C).
    T m_Distance;           ///< Distance (D).

    /// @brief Copy constructor.
    /// 
    /// @param _Plane Plane to copy.
    INLINE Plane_T(const Plane_T<T> &_Plane)
    {
        m_vNormal = _Plane.m_Distance;
        m_Distance = _Plane.m_Distance;
    }

    /// @brief Default constructor.
    /// 
    /// @param _vNormal Normal.
    /// @param _Distance Distance.
    INLINE Plane_T(const Vector3_T<T> &_vNormal, const T &_Distance)
    {
        m_vNormal = _vNormal;
        m_Distance = _Distance;
    }

    /// @brief Sets normal vector and distance.
    /// 
    /// @param _vNormal Normal vector.
    /// @param _Distance Distance.
    INLINE void Set(const Vector3_T<T> &_vNormal, const T &_Distance)
    {
        m_vNormal = _vNormal;
        m_Distance = _Distance;
    }

    /// @brief Sets normal vector and distance.
    /// 
    /// @param _vNormal Normal vector.
    /// @param _vPoint Point.
    INLINE void Set(const Vector3_T<T> &_vNormal, Vector3_T<T> &_vPoint)
    {
        m_vNormal = _vNormal;
        m_Distance = -dot(_vNormal, _vPoint);
    }
};

//==================================//
//              TYPEDEF             //
//==================================//
typedef Plane_T<f32> Plane;
typedef Plane_T<f32> Plane_f64;

#endif // __PLANE__
