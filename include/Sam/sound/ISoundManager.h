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
#ifndef __ISOUND_MANAGER__
#define __ISOUND_MANAGER__

#include <SamConfig.h>

namespace sam
{
    /// @brief Sound manager.
    class ISoundManager : public IAllocated
    {
    public:
        /// @brief Initialize the sound engine.
        virtual bool Initialize() = 0;

        /// @brief Shutdown the sound engine.
        virtual void Shutdown() = 0;

        /// @brief Update the sound engine.
        /// 
        /// @param _fElapsedTime Elapsed time since the last frame.
        virtual void Update(float _fElapsedTime) = 0;

        /// @brief Retrieves master bus by name.
        /// 
        /// @param _sBusName Name of the master bus.
        /// @return Pointer to the master bus or null if not found.
        virtual IMasterAudioBus *GetMasterBus(const String &_sBusName) const = 0;

        /// @brief Load a sound bank.
        /// 
        /// @param _sBank Name of the sound bank.
        /// @return Pointer to the loaded sound bank or null if an error occurred.
        virtual ISoundBank *LoadSoundBank(const String &_sBank) = 0;

        /// @brief Unload specified sound bank.
        /// 
        /// @param _sBank Sound bank to unload.
        virtual void UnloadSoundBank(const String &_sBank) = 0;

        /// @brief Unload all sound banks.
        virtual void UnloadAllSoundBanks() = 0;

        /// @brief Retrieves sound bank by name.
        /// 
        /// @param _sBank Name of the sound bank.
        /// @return Pointer to the sound bank or null if not found.
        virtual ISoundBank *GetSoundBank(const String &_sBank) const = 0;

        /// @brief Create sound.
        /// 
        /// @param _sName Unique name.
        /// @param _sEvent Sound event name.
        /// @return Pointer to the sound or null if an error occurred.
        virtual ISound *CreateSound(const String &_sName, const String &_sEvent = "") = 0;

        /// @brief Retrieves sound by name.
        /// 
        /// @param _sName Name of the sound.
        /// @return Pointer to the sound or null if not found.
        virtual ISound *GetSound(const String &_sName) const = 0;

        /// @brief Removes sound by name.
        /// 
        /// @param _sName Name of the sound.
        virtual void RemoveSound(const String &_sName) = 0;

        /// @brief Removes all sounds.
        virtual void RemoveAllSounds() = 0;
    };
}

// sam engine renderer subsystem macro export
#ifdef SAM_SOUND_EXPORTS
#   define SAM_SOUND_API DLL_EXPORT
#else
#   define SAM_SOUND_API DLL_IMPORT
#endif

extern "C"
{
    /// @brief Create sound engine.
    /// 
    /// @param _pEnv Global environment variable.
    /// @remarks Should be implemented.
    SAM_SOUND_API sam::ISoundManager *CreateSoundEngine(sam::Env *_pEnv);

    /// @brief Destroy sound engine.
    /// 
    /// @remarks Should be implemented.
    SAM_SOUND_API void DestroySoundEngine();
};


#endif // __ISOUND_MANAGER__
