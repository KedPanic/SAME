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
#ifndef __DX_CAUDIO_ENGINE__
#define __DX_CAUDIO_ENGINE__

namespace sam
{    
    /// @brief
    class SAM_SOUND_API CAudioEngine
    {	
    public:
        /// @brief Constructor.
        CAudioEngine(void);

        /// @brief Destructor.
        ~CAudioEngine(void);

        /// @brief Initialize audio device.
        /// 
        /// @return EResult_Success or error code.
        EResult Initialize(void);

        /// @brief Shutdown audio device.
        /// 
        /// @return EResult_Success or error code.
        EResult Shutdown(void);

        /// @brief Load sound.
        /// 
        /// @param _pSound Pointer to the created sound.
        /// @param _pFilename Filename.        
        /// @param _pSoundDef Sound definition.
        /// @param _nFlags Bitmask.
        /// 
        /// @return EResult_Success or error code.
        /// 
        /// @see sam::ESoundFlags
        /// @see sam::SSoundDef
        /// 
        /// @remarks Sounds is loaded fully into memory and decoded in PCM.
        EResult LoadSoundFromFile(CSound **_pSound, const char *_pFilename, SSoundDef *_pSoundDef, uint32 _nFlags = 0);

        /// @brief Load sound.
        /// 
        /// @param _pSound Pointer to the created sound.
        /// @param _pBuffer Data.        
        /// @param _pSoundDef Sound definition.
        /// @param _nFlags Bitmask.
        /// 
        /// @return EResult_Success or error code.
        /// 
        /// @see sam::ESoundFlags
        /// @see sam::SSoundDef
        /// 
        /// @remarks Sounds is loaded fully into memory and decoded in PCM.
        EResult LoadSoundFromMem(CSound **_pSound, const char *_pBuffer, SSoundDef *_pSoundDef, uint32 _nFlags = 0);

    private:
        IXAudio2 *m_pAudioEngine;     ///< DX audio engine.

        CAudioDevice *m_pAudioDevice; ///< Audio device.		
    };
}

#endif // __DX_CAUDIO_ENGINE__
