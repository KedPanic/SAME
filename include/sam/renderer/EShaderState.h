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
#ifndef __ESHADER_STATE__
#define __ESHADER_STATE__

namespace sam
{
    /// @enum Blend factors.
    enum EBlendFactor
    {
        BF_Zero,
        BF_One,
        BF_Src_Color,
        BF_One_Minus_Src_Color,
        BF_Dst_Color,
        BF_One_Minus_Dst_Color,
        BF_Constant_Color,
        BF_One_Minus_Constant_Color,
        BF_Src_Alpha,
        BF_One_Minus_Src_Alpha,        
        BF_Dst_Alpha,
        BF_One_Minus_Dst_Alpha,
        BF_Constant_Alpha,
        BF_One_Minus_Constant_Alpha,
        BF_Src_Aplha_Saturate,
    };
    
    /// @enum Blend operations.
    enum EBlendOp
    {
        BO_Add,
        BO_Subtract,
        BO_Reverse_Subtract,
        BO_Min,
        BO_Max,
    };

    /// @enum Comparison function used for depth, alpha, stencil testing.
    enum EComparisonFunc
    {
        e_ComparisonFunc_Never,           ///< Never pass.
        e_ComparisonFunc_Less,            ///< Passes if the current value is less than the reference value.
        e_ComparisonFunc_Less_Equal,      ///< Passes if the current value is less than or equal to the reference value.
        e_ComparisonFunc_Equal,           ///< Passes if the current value is equal to the reference value.
        e_ComparisonFunc_Greater_Equal,   ///< Passes if the current value is greater than or equal to the reference value.
        e_ComparisonFunc_Greater,         ///< Passes if the current value is greater than the reference value.
        e_ComparisonFunc_Not_Equal,       ///< Passes if the current value is not equal to the reference value.
        e_ComparisonFunc_Always,          ///< Always pass.
    };

    /// @enum Stencil operations.
    enum EStencilOp
    {
        SO_Keep,            ///< Keep the current value.
        SO_Zero,            ///< Set the value to 0.
        SO_Replace,         ///< Replace the current value.
        SO_Incr,            ///< Increment the value and clamp the result.
        SO_Decr,            ///< Decrement the value and clamp the result.
        SO_Invert,          ///< invert bits of the current value.
        SO_Incr_Wrap,       ///< Increment the value and wrap the result if necessary.
        SO_Decr_Wrap,       ///< Decrement the value and wrap the result if necessary.
    };

    /// @enum Culling mode.
    enum ECullMode
    {
        CM_None,            ///< All polygons will be drawn.
        CM_Front,           ///< Cull polygons that are front-facing.
        CM_Back,            ///< Cull polygons that are back-facing.
    };

    /// @enum Fill mode.
    enum EFillMode
    {
        FM_WireFrame,       ///< Fill the edges of the polygons.
        FM_Solid,           ///< Fill the polygons.
    };
}

#endif // __ESHADER_STATE__
