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
#include "SamRendererPCH.h"
#include "renderer/CRenderWindow.h"
#include "renderer/CMaterial.h"

namespace sam
{
    // Constructor.
    CMaterial::CMaterial(ID p_nID)
        : m_nID(p_nID), m_pVertexShader(NULL), m_pPixelShader(NULL), m_pFirstParam(NULL), m_pLastParam(NULL)
    {

    }

    /// @brief Apply current material.
    void CMaterial::Apply(void)
    {
        g_Env->pRenderWindow->SetVertexShader(m_pVertexShader);
        g_Env->pRenderWindow->SetPixelShader(m_pPixelShader);

        // Apply render state.
        SMaterialParams *pNode = m_pFirstParam;
        while(pNode)
        {
            (this->*pNode->m_pFunc)();

            pNode = pNode->m_pNext;
        }

        // Apply texture Unit.
        // TODO.
    }

    /// @brief Add param.
    ///
    /// @param _eID Function ID.
    /// @param _sParams List of parameters.
    void CMaterial::AddParam(EFunctionID _eID, char *_sParams)
    {
        ApplyParam pFunc = NULL; 
        char *sParams = _sParams;

        switch(_eID)
        {
        case FID_BLEND_FACTOR:
            {                
                m_bBlendEnabled = true;

                for(int i = 0; i < 4; ++i)
                {                                      
                    if(strncmp(sParams, "one", 3) == 0)
                    {
                        m_eBlendFactor[i] = BF_One;
                        sParams += 3;
                    }
                    else if(strncmp(sParams, "zero", 4) == 0)
                    {
                        m_eBlendFactor[i] = BF_Zero;
                        sParams += 4;
                    }
                    else if(strncmp(sParams, "src_color", 9) == 0)
                    {
                        m_eBlendFactor[i] = BF_Src_Color;
                        sParams += 9;
                    }
                    else if(strncmp(sParams, "dst_color", 9) == 0)
                    {
                        m_eBlendFactor[i] = BF_Dst_Color;
                        sParams += 9;
                    }
                    else if(strncmp(sParams, "src_alpha", 9) == 0)
                    {
                        m_eBlendFactor[i] = BF_Src_Alpha;
                        sParams += 9;
                    }
                    else if(strncmp(sParams, "dst_alpha", 9) == 0)
                    {
                        m_eBlendFactor[i] = BF_Dst_Alpha;
                        sParams += 9;
                    }
                    else if(strncmp(sParams, "const_color", 11) == 0)
                    {
                        m_eBlendFactor[i] = BF_Constant_Color;
                        sParams += 11;
                    }
                    else if(strncmp(sParams, "const_alpha", 11) == 0)
                    {
                        m_eBlendFactor[i] = BF_Constant_Alpha;
                        sParams += 11;
                    }
                    else if(strncmp(sParams, "src_alpha_saturate", 18) == 0)
                    {
                        m_eBlendFactor[i] = BF_Src_Aplha_Saturate;
                        sParams += 18;
                    }
                    else if(strncmp(sParams, "one_minus_src_color", 19) == 0)
                    {
                        m_eBlendFactor[i] = BF_One_Minus_Src_Color;
                        sParams += 19;
                    }
                    else if(strncmp(sParams, "one_minus_dst_color", 19) == 0)
                    {
                        m_eBlendFactor[i] = BF_One_Minus_Dst_Color;
                        sParams += 19;
                    }
                    else if(strncmp(sParams, "one_minus_src_alpha", 19) == 0)
                    {
                        m_eBlendFactor[i] = BF_One_Minus_Src_Alpha;
                        sParams += 19;
                    }
                    else if(strncmp(sParams, "one_minus_dst_alpha", 19) == 0)
                    {
                        m_eBlendFactor[i] = BF_One_Minus_Dst_Alpha;
                        sParams += 19;
                    }
                    else if(strncmp(sParams, "one_minus_const_color", 21) == 0)
                    {
                        m_eBlendFactor[i] = BF_One_Minus_Constant_Color;
                        sParams += 21;
                    }
                    else if(strncmp(sParams, "one_minus_dst_alpha", 21) == 0)
                    {
                        m_eBlendFactor[i] = BF_One_Minus_Constant_Alpha;
                        sParams += 21;
                    }
                    else
                    {
                        SamLogError("Unable to find parameter '%s' in fx file %d", sParams, m_nID);
                        m_eBlendFactor[i] = BF_Zero;
                    }

                    sParams += RemoveWhiteSpace(sParams);                    
                }

                pFunc = &CMaterial::ApplyBlendFactor;
            }
            break;

        case FID_BLEND_COLOR:
            {
                for(int i = 0; i < 4; ++i)
                {
                    m_fColors[i] = (float)strtod(sParams, &sParams);
                }

                pFunc = &CMaterial::ApplyBlendColor;
            }
            break;

        case FID_BLEND_OP:
            {
                for(int i = 0; i < 2; ++i)
                {
                    if(strncmp(sParams, "add", 3) == 0)
                        m_eBlendOp[i] = BO_Add;
                    else if(strncmp(sParams, "max", 3) == 0)
                        m_eBlendOp[i] = BO_Max;
                    else if(strncmp(sParams, "min", 3) == 0)
                        m_eBlendOp[i] = BO_Min;
                    else if(strncmp(sParams, "subtract", 8) == 0)
                        m_eBlendOp[i] = BO_Subtract;
                    else if(strncmp(sParams, "reverse_subtract", 16) == 0)
                        m_eBlendOp[i] = BO_Reverse_Subtract;

                    sParams += RemoveWhiteSpace(sParams);                    
                }

                pFunc = &CMaterial::ApplyBlendOp;
            }
            break;

        default:
            SAM_ASSERT(false, "Unimplemented");
            return;
        }

        // Add and create node for the specified function.
        AddParam(pFunc);
    }

    /// @brief Add new param.
    /// 
    /// @param _pFunc Pointer to the function to call.
    void CMaterial::AddParam(ApplyParam _pFunc)
    {
        SMaterialParams *pMaterialParam = SAM_NEW SMaterialParams;        
        pMaterialParam->m_pFunc = _pFunc;
        pMaterialParam->m_pNext = NULL;

        if(!m_pFirstParam)
        {            
            m_pFirstParam = m_pLastParam = pMaterialParam;
            return;
        }

        m_pLastParam->m_pNext = pMaterialParam;
        m_pLastParam = pMaterialParam;
    }

    /// @brief Sets blending factor state.
    /// 
    /// @param _bEnabled True to enable blending operation.
    /// @param _eSrcColor Source color factor.
    /// @param _eDstColor Destination color factor.
    /// @param _eSrcAlpha Source alpha factor.
    /// @param _eDstAlpha Destination alpha factor.
    void CMaterial::SetBlendFactor(bool _bEnabled, EBlendFactor _eSrcColor, EBlendFactor _eDstColor, EBlendFactor _eSrcAlpha, EBlendFactor _eDstAlpha)
    {
        m_bBlendEnabled = _bEnabled;
        m_eBlendFactor[0] = _eSrcColor;
        m_eBlendFactor[1] = _eDstColor;
        m_eBlendFactor[2] = _eSrcColor;
        m_eBlendFactor[3] = _eDstAlpha;
    }

    /// @brief Sets blending color.
    /// 
    /// @param _fRed Red channel.
    /// @param _fGreen Green channel.
    /// @param _fBlue Blue channel.
    /// @param _fAlpha Alpha channel.
    void CMaterial::SetBlendColor(float _fRed, float _fGreen, float _fBlue, float _fAlpha)
    {
        m_fColors[0] = _fRed;
        m_fColors[1] = _fGreen;
        m_fColors[2] = _fBlue;
        m_fColors[3] = _fAlpha;
    }

    /// @brief Sets blending operation.
    /// 
    /// @param _eColor Color operation.
    /// @param _eAlpha Alpha operation.
    void CMaterial::SetBlendOp(EBlendOp _eColor, EBlendOp _eAlpha)
    {
        m_eBlendOp[0] = _eColor;
        m_eBlendOp[1] = _eAlpha;
    }
}
