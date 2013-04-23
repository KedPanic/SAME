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
#include <sound/DX/CAudioDevice.h>

namespace sam
{
	/// @brief Constructor.
	CAudioDevice::CAudioDevice(void)
		: m_pDevice(NULL)
	{
	}

	/// @brief Destructor.
	CAudioDevice::~CAudioDevice(void)
	{
	}

	/// @brief Initialize audio device.
	EResult CAudioDevice::Initialize(IXAudio2 *_pAudioEngine)
	{
        SAM_ASSERT(_pAudioEngine, "Audio engine is null");

		EResult result = EResult_Success;

       if(!m_pDevice)
       {
            // create the audio device.
            HRESULT hResult = _pAudioEngine->CreateMasteringVoice(&m_pDevice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL);
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
        }

		return result;
	}

	/// @brief Shutdown audio device.
	EResult CAudioDevice::Shutdown(void)
	{
		EResult result = EResult_Success;

		return result;
	}
}
