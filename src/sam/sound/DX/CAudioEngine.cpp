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
#include "SamSoundPCH.h"
#include <sound/CAudioEngine.h>
#include <sound/CAudioDevice.h>
#include <sound/CSound.h>

namespace sam
{
	/// @brief Constructor.
	CAudioEngine::CAudioEngine(void)
		: m_pAudioEngine(NULL), m_pAudioDevice(NULL)
	{        
	}

	/// @brief Destructor.
	CAudioEngine::~CAudioEngine(void)
	{
	}

	/// @brief Initialize audio device.
	EResult CAudioEngine::Initialize(void)
	{
		EResult result = EResult_Success;

        if(!m_pAudioEngine)
        {
            uint32 nFlags = 0;

#ifdef SAM_PLATFORM_WIN
            CoInitializeEx(NULL, COINIT_MULTITHREADED);

#   ifdef SAM_DEBUG
            nFlags = XAUDIO2_DEBUG_ENGINE;
#   endif
#endif
            // create the audio engine low level access.
            HRESULT hResult = XAudio2Create(&m_pAudioEngine, nFlags, XAUDIO2_DEFAULT_PROCESSOR);
            if(hResult != S_OK)
            {
                switch(hResult)
                {
                case XAUDIO2_E_INVALID_CALL:
                    SamLogError("Returned by XAudio2 for certain API usage errors (invalid calls etc) that are hard to avoid completely and should be handled by a title at runtime. (API usage errors that are completely avoidable, such as invalid parameters, cause an ASSERT in debug builds and undefined behavior in retail builds, so no error code is defined for them.)");
                    break;                              

#ifdef SAM_PLATFORM_X360
                case XAUDIO2_E_XMA_DECODER_ERROR:
                    SamLogError("The Xbox 360 XMA hardware suffered an unrecoverable error.");
                    break;
#endif
                case XAUDIO2_E_XAPO_CREATION_FAILED:
                    SamLogError("An effect failed to instantiate.");
                    break;

                case XAUDIO2_E_DEVICE_INVALIDATED:
                    SamLogError("An audio device became unusable through being unplugged or some other event.");
                    break;
                }

                return EResult_Invalid_Device; 
            }

            if(m_pAudioDevice == NULL)
            {
                m_pAudioDevice = SAM_NEW CAudioDevice;
                result = m_pAudioDevice->Initialize(m_pAudioEngine);
            }
        }		

		return result;
	}

	/// @brief Shutdown audio device.
	EResult CAudioEngine::Shutdown(void)
	{
		EResult result = EResult_Success;

		if(m_pAudioDevice != NULL)
		{
			result = m_pAudioDevice->Shutdown();

			SAM_DELETE m_pAudioDevice;
			m_pAudioDevice = NULL;
		}

		return result;
	}

    /// @brief Load sound.
    EResult CAudioEngine::LoadSoundFromFile(CSound **_pSound, const char *_pFilename, SSoundDef *_pSoundDef, uint32 _nFlags /*= 0*/)
    {
        CFile file;
        file.Open(_pFilename);

		return EResult_Success;
    }

    /// @brief Load sound.
    EResult CAudioEngine::LoadSoundFromMem(CSound **_pSound, const char *_pBuffer, SSoundDef *_pSoundDef, uint32 _nFlags /*= 0*/)
    {
		return EResult_Success;
    }
}