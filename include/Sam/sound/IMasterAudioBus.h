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
#ifndef __IMASTER_AUDIO_BUS__
#define __IMASTER_AUDIO_BUS__

#include <SamConfig.h>
#include <sound/SSoundParam.h>

namespace sam
{
    /// @brief Master audio bus interface. To manage a category of sounds.
    class IMasterAudioBus : public IAllocated
    {
    public:
        /// @brief Retrieves the name of the master audio bus.
        /// 
        /// @return Name of the master audio bus.
        virtual const String &getName() const = 0;

        /// @brief Set volume.
        /// 
        /// @param _fValue New volume.
        virtual void SetVolume(float _fValue) = 0;

        /// @brief Retrieves current volume.
        /// 
        /// @return Current volume.
        virtual float GetVolume() const = 0;

        /// @brief Sets parameter.
        /// 
        /// @param _sName Name of the parameter.
        /// @param _Param Parameter.
        virtual void SetParameter(const String &_sName, SParam &_Param) = 0;

        /// @brief Sets parameter.
        /// 
        /// @param _iID ID of the parameter.
        /// @param _Param Parameter.
        virtual void SetParameter(uint32 _iID, SParam &_Param) = 0;

        /// @brief Sets parameter by type.
        /// 
        /// @param _iType Type of parameter.
        /// @param _sName Name of the parameter.
        /// @param _Param Parameter.
        /// 
        /// @remarks 
        ///     _iType is sound engine specific
        virtual void SetParameter(uint32 _iType, const String &_sName, SParam &_Param) = 0;

        /// @brief Sets parameter by type.
        /// 
        /// @param _iType Type of parameter.
        /// @param _iID ID of the parameter.
        /// @param _Param Parameter.
        /// 
        /// @remarks 
        ///     _iType is sound engine specific
        virtual void SetParameter(uint32 _iType, uint32 _iID, SParam &_Param) = 0;
    };
}

#endif // __IMASTER_AUDIO_BUS__
