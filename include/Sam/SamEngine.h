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
#ifndef __SAM_ENGINE__
#define __SAM_ENGINE__

#include <SamConfig.h>

#include <action/CActionHandler.h>
#include <action/IActionMap.h>
#include <action/CActionMapManager.h>
#include <action/EAction.h>
#include <action/IActionListener.h>
#include <action/MappedKeys.h>

#include <event/EInput.h>
#include <event/IInputManager.h>
//#include <event/IWindowEventListener.h>

#include <common/SamCommon.h>
#include <sound/SamSound.h>

#include <game/IGame.h>
#include <game/IProfile.h>
#include <game/IProfileManager.h>

#include <physics/IPhysicalBody.h>
#include <physics/IPhysicalShape.h>
#include <physics/IPhysicalWorld.h>

#include <render/CCamera.h>
#include <render/IFlashPlayer.h>
#include <render/IRenderWindow.h>
#include <render/IVertexBuffer.h>
#include <render/SFlashEvent.h>
#include <render/IMaterial.h>
#include <render/IMaterialManager.h>

#include <sound/IMasterAudioBus.h>
#include <sound/ISound.h>
#include <sound/ISoundBank.h>
#include <sound/ISoundManager.h>
#include <sound/SSoundParam.h>

#include <world/IEntityFactory.h>
#include <world/IEntityRelay.h>
#include <world/IEntity.h>
#include <world/IEntitySystem.h>
#include <world/IGameObject.h>
#include <world/IGameObjectSystem.h>
#include <world/IWorld.h>

#endif // __SAM_ENGINE__
