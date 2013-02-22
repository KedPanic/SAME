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
#ifndef __CMATERIAL_MANAGER__
#define __CMATERIAL_MANAGER__

namespace sam
{
    /// @brief Shader builder, helper class to create shader from file.
    class CMaterialManager : public IAllocated
    {
    public:
        /// @brief Default constructor.
        CMaterialManager(void);

        /// @brief Load material from stream.
        /// 
        /// @param p_pStream .
		/// @param p_sName Material name.
        /// 
        /// @return Pointer to the created material or null.
        CMaterial *CreateMaterial(IStream *p_pStream, const char *p_sName);

        /// @brief Retrieves material from its ID.
        /// 
        /// @param p_nID Material ID.
        /// 
        /// @return Pointer to the material or null if not found.
        CMaterial *GetMaterial(const ID &p_nID) const;

        /// @brief Retrieves material from its name.
        /// 
        /// @param p_sName Material name.
        /// 
        /// @return Pointer to the material or null if not found.
        CMaterial *GetMaterial(const char *p_sName) const;

    private:
        CMaterial *m_pFirstMaterial;
        CMaterial *m_pLastMaterial;
    };
}

#endif // __CMATERIAL_MANAGER__
