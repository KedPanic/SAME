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
#ifndef __CPIXEL_SHADER_PLF__
#define __CPIXEL_SHADER_PLF__

#ifndef __CPIXEL_SHADER__
#   error "Do not include it directly"
#endif

namespace sam
{    
    class SAM_RENDERER_API CPixelShader : public IAllocated
    {
    public:
        /// @brief Constructor.
		/// 
		/// @param p_nID Unique ID.
        CPixelShader(ID p_nID);

        /// @brief Destructor.
        ~CPixelShader(void);

		/// @brief Retrieves program ID.
		/// 
		/// @return Program ID.
		const ID &GetID(void) const {return m_nID;}

        // @brief Create pixel shader.
        /// 
        /// @param p_pStream Program file.
        /// @param p_sFuncName Function name.
        /// @param p_sProfile Profile name.
        /// 
        /// @return True if no error occurred.
        bool CreateShader(IStream *p_pStream, const char *p_sFuncName, const char *p_sProfile);

        /// @brief Set next pixel shader.
        /// 
        /// @param p_pNext Next node.
        void SetNext(CPixelShader *p_pNext) {m_pNext = p_pNext;}

        /// @brief Retrieves next node.
        /// 
        /// @return Next node.
        CPixelShader *GetNext() const {return m_pNext;}

        /// @brief Retrieves D3D11 pixel shader.
        /// 
        /// @return D3D11 pixel shader.
        ID3D11PixelShader *GetD3DPixelShader() const {return m_pPixelShader;}

    private:
        ID m_nID;
        ID3D11PixelShader *m_pPixelShader;

        CPixelShader *m_pNext; ///< Next node in the chained list.
    };
}

#endif // __CPIXEL_SHADER_PLF__
