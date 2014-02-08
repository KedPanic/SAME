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
#ifndef __MATH_PLF__
#define __MATH_PLF__

namespace sam
{
    //==========================================//
    //              SIMPLE PRECISION            //
    //==========================================//

    INLINE f32 sqrt_fast(f32 _f)
    {
        __m128 r0 = _mm_sqrt_ss(_mm_set_ss(_f));

        f32 fResult;
        _mm_store_ss(&fResult, r0);

        return fResult;
    }

    INLINE f32 sqrt_safe_fast(f32 _f)
    {
        __m128 r0 = _mm_sqrt_ss(_mm_set_ss(_f + FLT_MIN));

        f32 fResult;
        _mm_store_ss(&fResult, r0);

        return fResult;
    }

    INLINE f32 inv_sqrt_fast(f32 _f)
    {
        __m128 r0 = _mm_rsqrt_ss(_mm_set_ss(_f));

        f32 fResult;
        _mm_store_ss(&fResult, r0);

        return fResult;
    }

    INLINE f32 inv_sqrt_safe_fast(f32 _f)
    {
        __m128 r0 = _mm_rsqrt_ss(_mm_set_ss(_f + FLT_MIN));

        f32 fResult;
        _mm_store_ss(&fResult, r0);

        return fResult;
    }

    INLINE f32 tan(f32 _f)
    {
        return tanf(_f);
    }

    //==========================================//
    //              DOUBLE PRECISION            //
    //==========================================//

    INLINE f64 sqrt_fast(f64 _f)
    {
        return sqrt(_f);
    }

    INLINE f64 sqrt_safe_fast(f64 _f)
    {
        return sqrt(_f + DBL_MIN);
    }

    INLINE f64 inv_sqrt_fast(f64 _f)
    {
        return 1.0 / sqrt(_f);
    }

    INLINE f64 inv_sqrt_safe_fast(f64 _f)
    {
        return 1.0 / sqrt(_f + DBL_MIN);
    }

    INLINE f64 tan(f64 _f)
    {
        return ::tan(_f);
    }
}

#endif // __MATH_PLF__
