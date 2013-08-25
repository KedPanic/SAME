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
#ifndef __SAM_PARAM__
#define __SAM_PARAM__

namespace sam
{
	/// @brief Parameter
	struct SParam
	{
		ETypeID		m_eType;	///< Type of the parameter.
		const ID	m_nID;		///< ID of the parameter.

		union
		{
			bool	b;
			int32	i;
			f32		f;
			uint32	ui;
			const char *str;
		}m_oValue; ///< Value of the parameter.

		/// @brief Default constructor
		///
		/// @param p_nID ID of the parameter.
		SParam(const ID p_nID)
			: m_eType(e_Type_Void), m_nID(p_nID)
		{
		}

		/// @brief Boolean constructor.
		/// 
		/// @param p_bValue Value.
		/// @param p_nID ID of the parameter.
		SParam(bool p_bValue, const ID p_nID)
			: m_eType(e_Type_Bool), m_nID(p_nID)
		{
			m_oValue.b = p_bValue;
		}

		/// @brief Integer constructor.
		/// 
		/// @param p_nValue Value.
		/// @param p_nID ID of the parameter.
		SParam(int32 p_nValue, const ID p_nID)
			: m_eType(e_Type_Int), m_nID(p_nID)
		{
			m_oValue.i = p_nValue;
		}

		/// @brief Integer constructor.
		/// 
		/// @param p_nValue Value.
		/// @param p_nID ID of the parameter.
		SParam(uint32 p_nValue, const ID p_nID)
			: m_eType(e_Type_UInt), m_nID(p_nID)
		{
			m_oValue.ui = p_nValue;
		}

		/// @brief Real constructor.
		/// 
		/// @param p_fValue Value.
		/// @param p_nID ID of the parameter.
		SParam(float p_fValue, const ID p_nID)
			: m_eType(e_Type_Float), m_nID(p_nID)
		{
			m_oValue.f = p_fValue;
		}

		/// @brief String constructor.
		/// 
		/// @param p_sValue Value.
		/// @param p_nID ID of the parameter.
		SParam(const char *p_sValue, const ID p_nID)
			: m_eType(e_Type_Char), m_nID(p_nID)
		{
			m_oValue.str = p_sValue;
		}
	};
}
#endif // __SAM_PARAM__
