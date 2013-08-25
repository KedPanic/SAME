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
#ifndef __CTEXTURE2D_DX11__
#define __CTEXTURE2D_DX11__

namespace sam
{
    /// @brief Texture implementation.
    class CTexture : public IAllocated
    {
    public:
        /// @brief Constructor.
        CTexture(void);

        /// @brief Destructor.
        ~CTexture(void);

        /// @brief Retrieves type of texture.
        /// 
        /// @return Type of texture.
        ETextureType GetType(void) const {return m_eType;}

        /// @brief Retrieves mipmap levels.
        /// 
        /// @return Mipmap levels.
        uint32 GetMipLevels(void) const {return m_nMipLevels;}

        /// @brief Create texture from buffer.
        /// 
        /// @param _pBuffer Memory buffer.
        /// @param _nSize Buffer size.
        /// @param _eUsage Usage.
        /// @param _eType Type.
        /// @return false if any error occurred.
        bool CreateTexture(void *_pBuffer, uint32 _nSize, ETextureUsage _eUsage, ETextureType _eType);

        /// @brief Create empty texture.
        /// 
        /// @param p_nWidth
        /// @param p_nHeight
        /// @param p_eFormat
        /// @param p_eType
        /// @param p_eUsage
        /// 
        /// @return Create texture.
        bool CreateTexture(uint32 p_nWidth, uint32 p_nHeight, ETextureFormat p_eFormat, ETextureType p_eType, ETextureUsage p_eUsage);

        /// @brief Release the texture.
        void Release(void);

        /// @brief Retrieves the size of the texture.
        /// 
        /// @return Width of the texture.
        int GetWidth(void) {return m_iWidth;}

        /// @brief Retrieves the size of the texture.
        /// 
        /// @return Height of the texture.
        int GetHeight(void) {return m_iHeight;}

        /// @brief Retrieves the original size of the texture.
        /// 
        /// @return Width of the texture.
        int GetBaseWidth(void) {return m_iWidth;}

        /// @brief Retrieves the original size of the texture.
        /// 
        /// @return Height of the texture.
        int GetBaseHeight(void) {return m_iHeight;}

        /// @brief Retrieves the unique id of the texture.
        /// 
        /// @return The unique id of the texture.
        int GetID(void) {return m_iID;}

        /// @brief Map the texture for CPU access.
        /// 
        /// @param _eAccess Map access.
        /// @param _nLevel Mipmap level.
        /// @param _nSide For cubemap (side of the "cube").
        /// @return Data of the texture.
        uint8 *Map(ETextureMap _eAccess, uint32 _nLevel = 0, uint32 _nSide = 0);

        /// @brief Unmap the texture data and re-enable the GPU's access.
        /// 
        /// @param _nLevel Mipmap level.
        /// @param _nSide For cubemap (side of the "cube").
        void Unmap(uint32 _nLevel = 0, uint32 _nSide = 0);

		//================================================//
		//                  INTERNAL USE                  //
		//================================================//

		/// @brief Retrieves texture.
		/// 
		/// @return Pointer to the texture.
		ID3D11ShaderResourceView *GetTexture() const {return m_pShaderResourceView;}

    private:
        ID3D11Resource *m_pTexture;
		ID3D11ShaderResourceView *m_pShaderResourceView;

        uint32 m_nMipLevels;     ///< Mip levels.
        int m_iID;               ///< Unique ID of the texture.
        int m_iWidth, m_iHeight; ///< Size of the texture.
        ETextureType m_eType;    ///< Texture type.

        /// @brief Create 1D texture.

        /// @brief Create 2D texture.
        /// 
        /// @param _pBuffer Memory buffer.
        /// @param _eUsage Usage.
        /// @param _eFormat Texture format.
        ///
        /// @return True if no error occurred.
        bool CreateTexture2D(void *_pBuffer, ETextureUsage _eUsage, DXGI_FORMAT _eFormat);

        /// @brief Create 3D texture.
        /// @brief Create render target.
    };
}

#endif // __CTEXTURE2D_DX11__
