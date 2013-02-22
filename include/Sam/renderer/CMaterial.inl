//================================================//
//                  RENDER STATE                  //
//================================================//

/// @brief Sets blending factor state.
INLINE void CMaterial::ApplyBlendFactor()
{
    g_Env->pRenderWindow->SetBlendFactor(m_bBlendEnabled, m_eBlendFactor[0], m_eBlendFactor[1], m_eBlendFactor[2], m_eBlendFactor[3]);
}

/// @brief Sets blending color.
INLINE void CMaterial::ApplyBlendColor()
{
    g_Env->pRenderWindow->SetBlendColor(m_fColors[0], m_fColors[1], m_fColors[2], m_fColors[3]);
}

/// @brief Sets blending operation.
INLINE void CMaterial::ApplyBlendOp()
{
    g_Env->pRenderWindow->SetBlendOp(m_eBlendOp[0], m_eBlendOp[1]);
}
