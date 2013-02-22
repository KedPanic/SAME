INLINE Vector_T::Normalize()
{
    T fInvLength = inv_sqrt_safe_fast(x * x + y * y + z * z);

    x *= fInvLength;
    y *= fInvLength;
    z *= fInvLength;
}