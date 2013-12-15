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
#ifndef __CMATERIAL__
#define __CMATERIAL__

namespace sam
{
    /// @brief
    class CMaterial : public IAllocated
    {
    public:
        /// @enum Function ID.
        enum EFunctionID
        {
            FID_BLEND_FACTOR,
            FID_BLEND_COLOR,
            FID_BLEND_OP,     

            FID_Unknown,
        };

        /// @brief Constructor.
        /// 
        /// @param p_nID Unique ID.
        CMaterial(ID p_nID);

        /// @brief Apply current material.
        void Apply(void);

        /// @brief Retrieves unique ID.
        /// 
        /// @return Unique ID.
        const ID &GetID(void) const {return m_nID;}

        /// @brief Sets vertex shader.
        /// 
        /// @param _pVertexShader Pointer to shader instance.
        void SetVertexShader(CVertexShader *_pVertexShader) {m_pVertexShader = _pVertexShader;}

        /// @brief Sets pixel shader.
        /// 
        /// @param _pPixelShader Pointer to shader instance.
        void SetPixelShader(CPixelShader *_pPixelShader) {m_pPixelShader = _pPixelShader;}

        /// @brief Set next material.
        /// 
        /// @param _pNext Next node.
        void SetNext(CMaterial *_pNext) {m_pNext = _pNext;}

        /// @brief Retrieves next node.
        /// 
        /// @return Next node.
        CMaterial *GetNext(void) const {return m_pNext;}

        /// @brief Sets blending factor state.
        /// 
        /// @param _bEnabled True to enable blending operation.
        /// @param _eSrcColor Source color factor.
        /// @param _eDstColor Destination color factor.
        /// @param _eSrcAlpha Source alpha factor.
        /// @param _eDstAlpha Destination alpha factor.
        void SetBlendFactor(bool _bEnabled, EBlendFactor _eSrcColor, EBlendFactor _eDstColor, EBlendFactor _eSrcAlpha, EBlendFactor _eDstAlpha);

        /// @brief Sets blending color.
        /// 
        /// @param _fRed Red channel.
        /// @param _fGreen Green channel.
        /// @param _fBlue Blue channel.
        /// @param _fAlpha Alpha channel.
        void SetBlendColor(float _fRed, float _fGreen, float _fBlue, float _fAlpha);

        /// @brief Sets blending operation.
        /// 
        /// @param _eColor Color operation.
        /// @param _eAlpha Alpha operation.
        void SetBlendOp(EBlendOp _eColor, EBlendOp _eAlpha);

        /// @brief Add param.
        ///
        /// @param _eID Function ID.
        /// @param _sParams List of parameters.
        void AddParam(EFunctionID _eID, char *_sParams);

    private:
        ID m_nID; ///< Unique ID.

        CVertexShader *m_pVertexShader;
        CPixelShader *m_pPixelShader;

        CMaterial *m_pNext; ///< Chained list.

        typedef void (CMaterial::*ApplyParam)();
        struct SMaterialParams : IAllocated
        {
            ApplyParam m_pFunc;
            SMaterialParams *m_pNext;
        };
        SMaterialParams *m_pFirstParam;
        SMaterialParams *m_pLastParam;

        /// @brief Add new param.
        /// 
        /// @param _pFunc Pointer to the function to call.
        void AddParam(ApplyParam _pFunc);


        //================================================//
        //                  RENDER STATE                  //
        //================================================//

        bool m_bBlendEnabled;
        EBlendFactor m_eBlendFactor[4]; // SrcColor, DstColor, SrcAlpha, DstAlpha
        float m_fColors[5];             // Red, Green, Blue, Alpha
        EBlendOp m_eBlendOp[2];         // Color, Alpha

        /// @brief Sets blending factor state.
        inline void ApplyBlendFactor(void);

        // @brief Sets blending color.
        inline void ApplyBlendColor(void);

        /// @brief Sets blending operation.
        inline void ApplyBlendOp(void);
    };

#include "renderer/CMaterial.inl"
}

#endif // __CMATERIAL__
