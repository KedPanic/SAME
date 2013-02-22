//==========================================//
//                   Eye                    //
//==========================================//

/// @brief Look at.
/// 
/// @param _vPoint Point to look.
INLINE void CCamera::LookAt(const Vector3 &_vPoint)
{
    m_vAt = _vPoint - m_vOrigin;
    m_vAt.Normalize();

    m_vRight = cross(Vector3(0.0f, 1.0f, 0.0f), m_vAt);  
    m_vRight.Normalize();

    m_vUp = cross(m_vAt, m_vRight);    
    m_vUp.Normalize();
}

/// @brief Look at.
/// 
/// @param _vEye Eye vector.
/// @param _vAt At vector.
/// @param _vUp Up vector.
INLINE void CCamera::LookAt(const Vector3 &_vEye, const Vector3 &_vAt, const Vector3 &_vUp)
{
    m_vAt = _vAt - _vEye;           m_vAt.Normalize();
    m_vRight = cross(_vUp, m_vAt);  m_vRight.Normalize();
    m_vUp = cross(m_vAt, m_vRight); m_vUp.Normalize();

    m_vOrigin = _vEye;
}

/// @brief Retrieves projection matrix.
/// 
/// @param _mMatrix Matrix to set.
INLINE void CCamera::GetModelViewMatrix(Matrix44 &_mMatrix) const
{
    Vector3 vNegPos(-m_vOrigin.x, -m_vOrigin.y, -m_vOrigin.z);

    _mMatrix.m00 = m_vRight.x, _mMatrix.m01 = m_vRight.y, _mMatrix.m02 = m_vRight.z, _mMatrix.m03 = dot<f32, f32>(vNegPos, m_vRight);
    _mMatrix.m10 = m_vUp.x,    _mMatrix.m11 = m_vUp.y,    _mMatrix.m12 = m_vUp.z,    _mMatrix.m13 = dot<f32, f32>(vNegPos, m_vUp);
    _mMatrix.m20 = m_vAt.x,    _mMatrix.m21 = m_vAt.y,    _mMatrix.m22 = m_vAt.z,    _mMatrix.m23 = dot<f32, f32>(vNegPos, m_vAt);
    _mMatrix.m30 = 0.0f,       _mMatrix.m31 = 0.0f,       _mMatrix.m32 = 0.0f,       _mMatrix.m33 = 1.0f;
}


//==========================================//
//                  FRUSTUM                 //
//==========================================//

/// @brief Retrieves projection matrix.
/// 
/// @return Projection matrix.
INLINE const Matrix44 &CCamera::GetProjectionMatrix(void) const
{
    return m_mProjectionMatrix;
}

/// @brief Sets camera to orthographic mode.
/// 
/// @param _nWidth Width of frustum.
/// @param _nHeight height of frustum.
/// @param _fNear Near plane.
/// @param _fFar Far plane.
INLINE void CCamera::SetOrthographic(uint32 _nWidth, uint32 _nHeight, f32 _fNear /*= 0.5f*/, f32 _fFar /*= 1000.0f*/)
{
    SAM_ASSERT(_fNear < _fFar, "Near plane have to be lower than far plane");

    m_eType = PT_Orthographic;

    m_nWidth = _nWidth;
    m_nHeight = _nHeight;
    m_fProjectionRatio = (f32)m_nWidth /(f32)m_nHeight;
    m_fNear = _fNear;
    m_fFar = _fFar;

    UpdateOrthographic();
}

/// @brief Sets camera to perspective mode.
/// 
/// @param _nWidth Width of frustum.
/// @param _nHeight height of frustum.
/// @param _fFOV Field of view on Y-Axis.
/// @param _fNear Near plane.
/// @param _fFar Far plane.
INLINE void CCamera::SetPerspective(uint32 _nWidth, uint32 _nHeight, f32 _fFOV /*= 75.0f */, f32 _fNear /*= 0.5f*/, f32 _fFar /*= 1000.0f*/)
{
    SAM_ASSERT(_fNear < _fFar, "Near plane have to be lower than far plane");

    m_eType = PT_Perspective;

    m_fFov = _fFOV * DEG2RAD;
    m_nWidth = _nWidth;
    m_nHeight = _nHeight;
    m_fProjectionRatio = (f32)m_nWidth /(f32)m_nHeight;
    m_fNear = _fNear;
    m_fFar = _fFar;

    UpdatePerspective();
}

/// @brief Update frustum.
INLINE void CCamera::UpdateOrthographic(void)
{
    m_fRight = m_nWidth * m_fProjectionRatio;
    m_fLeft = -m_fRight;
    m_fTop = (f32)m_nHeight;
    m_fBottom = (f32)-m_nHeight;

    // Compute projection matrix.
    m_mProjectionMatrix.m00 = (m_fRight - m_fLeft) * 0.5f;
    m_mProjectionMatrix.m01 = 0.0f;
    m_mProjectionMatrix.m02 = 0.0f;
    m_mProjectionMatrix.m03 = (m_fRight + m_fLeft) / (m_fRight - m_fLeft);

    m_mProjectionMatrix.m10 = 0.0f;
    m_mProjectionMatrix.m11 = (m_fTop - m_fBottom) * 0.5f;
    m_mProjectionMatrix.m12 = 0.0f;
    m_mProjectionMatrix.m13 = (m_fTop + m_fBottom) / (m_fTop - m_fBottom);

    m_mProjectionMatrix.m20 = 0.0f;
    m_mProjectionMatrix.m21 = 0.0f;
    m_mProjectionMatrix.m22 = (m_fFar - m_fNear) * -0.5f;
    m_mProjectionMatrix.m23 = (m_fFar + m_fNear) / (m_fFar - m_fNear);

    m_mProjectionMatrix.m30 = 0.0f;
    m_mProjectionMatrix.m31 = 0.0f;
    m_mProjectionMatrix.m32 = 0.0f;
    m_mProjectionMatrix.m33 = 1.0f;

//     return Matrix4(
//         Vector4( ( inv_rl + inv_rl ), 0.0f, 0.0f, 0.0f ),
//         Vector4( 0.0f, ( inv_tb + inv_tb ), 0.0f, 0.0f ),
//         Vector4( 0.0f, 0.0f, ( inv_nf + inv_nf ), 0.0f ),
//         Vector4( ( -sum_rl * inv_rl ), ( -sum_tb * inv_tb ), ( sum_nf * inv_nf ), 1.0f )
//         );
}

/// @brief Update frustum.
INLINE void CCamera::UpdatePerspective(void)
{
    m_fTop = m_fNear * tan(m_fFov * 0.5f);
    m_fBottom = -m_fTop;
    m_fRight = m_fTop * m_fProjectionRatio;
    m_fLeft = -m_fRight;

    // Compute projection matrix.
    m_mProjectionMatrix.m00 = (2.0f * m_fNear) / (m_fRight - m_fLeft);
    m_mProjectionMatrix.m01 = 0.0f;
    m_mProjectionMatrix.m02 = (m_fRight + m_fLeft) / (m_fRight - m_fLeft);
    m_mProjectionMatrix.m03 = 0.0f;

    m_mProjectionMatrix.m10 = 0.0f;
    m_mProjectionMatrix.m11 = (2.0f * m_fNear) / (m_fTop - m_fBottom);
    m_mProjectionMatrix.m12 = (m_fTop + m_fBottom) / (m_fTop - m_fBottom);
    m_mProjectionMatrix.m13 = 0.0f;

    m_mProjectionMatrix.m20 = 0.0f;
    m_mProjectionMatrix.m21 = 0.0f;
    m_mProjectionMatrix.m22 = (m_fFar + m_fNear) / (m_fFar - m_fNear);
    m_mProjectionMatrix.m23 = (-2.0f * m_fNear + m_fFar) / (m_fFar - m_fNear);

    m_mProjectionMatrix.m30 = 0.0f;
    m_mProjectionMatrix.m31 = 0.0f;
    m_mProjectionMatrix.m32 = -1.0f;
    m_mProjectionMatrix.m33 = 0.0f;
}
