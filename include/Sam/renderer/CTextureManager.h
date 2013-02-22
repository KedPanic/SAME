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
#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

namespace sam
{
    /// @brief Texture manager.
    class CTextureManager : public IAllocated
    {
    public:
		/// @brief Constructor.
		CTextureManager();

		/// @brief Destructor.
		~CTextureManager();

		/// @brief Load texture from file.
		/// 
		/// @param p_pTexture Stream.
        /// @param _eType Type of texture.
        /// @param _eUsage Usage.
		/// 
		/// @return Pointer to the loaded texture or null if not found.
		CTexture *LoadTexture(IStream *p_pTexture, ETextureType _eType, ETextureUsage _eUsage);

		/// @brief Create empty texture.
		/// 
		/// @param p_nWidth
		/// @param p_nHeight
		/// @param p_eFormat
		/// @param p_eType
		/// @param p_eUsage
		/// 
		/// @return Create texture.
        CTexture *CreateTexture(uint32 p_nWidth, uint32 p_nHeight, ETextureFormat p_eFormat, ETextureType _eType, ETextureUsage _eUsage);

		/// @brief Retrieves texture by id.
		/// 
		/// @param _iID The unique id of the texture.
		/// 
		/// @return Pointer to the texture or null if not found.
		CTexture *GetTexture(uint32 _iID) const;

		/// @brief Unload the specified texture.
		/// 
		/// @param _iID The unique id of the texture.
		void UnloadTexture(uint32 _iID);

		/// @brief Unload all textures.
		void UnloadAllTextures();

        /// @brief Retrieves pitch from texture format.
        /// 
        /// @param p_eFormat Texture format.
        ///
        /// @return Pitch.
        uint32 GetPitch(ETextureFormat p_eFormat);

    private:
        typedef std::map<uint32, CTexture*> Textures;
		Textures m_aTextures; ///< Array of loaded textures.

		int m_iCurrentTextureID; ///< Incremental id.
    };
}

#endif // __TEXTURE_MANAGER_H__
