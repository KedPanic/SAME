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
	/// @enum Define type of parameter
	enum EParamType
	{
		e_ParamType_Bool,
		e_ParamType_Int,
		e_ParamType_Float,
		e_ParamType_String,
		e_ParamType_Void,
	};

	/// @brief Parameter
	struct SParam
	{
		EParamType m_eType;		///< Type of the parameter.
		const char *m_sName;	///< Name of the parameter.

		union
		{
			bool  b;
			int   i;
			float f;
			const char *str;
		}m_oValue; ///< Value of the parameter.

		/// @brief Default constructor
		///
		/// @param p_sName Name of the parameter.
		SParam(const char *p_sName)
			: m_eType(e_ParamType_Void), m_sName(p_sName)
		{
		}

		/// @brief Boolean constructor.
		/// 
		/// @param p_bValue Value.
		/// @param p_sName Name of the parameter.
		SParam(bool p_bValue, const char *p_sName)
			: m_eType(e_ParamType_Bool), m_sName(p_sName)
		{
			m_oValue.b = p_bValue;
		}

		/// @brief Integer constructor.
		/// 
		/// @param p_nValue Value.
		/// @param p_sName Name of the parameter.
		SParam(int p_nValue, const char *p_sName)
			: m_eType(e_ParamType_Int), m_sName(p_sName)
		{
			m_oValue.i = p_nValue;
		}

		/// @brief Real constructor.
		/// 
		/// @param p_fValue Value.
		/// @param p_sName Name of the parameter.
		SParam(float p_fValue, const char *p_sName)
			: m_eType(e_ParamType_Float), m_sName(p_sName)
		{
			m_oValue.f = p_fValue;
		}

		/// @brief String constructor.
		/// 
		/// @param p_sValue Value.
		/// @param p_sName Name of the parameter.
		SParam(const char *p_sValue, const char *p_sName)
			: m_eType(e_ParamType_String), m_sName(p_sName)
		{
			m_oValue.str = p_sValue;
		}
	};
}
#endif // __SAM_PARAM__
