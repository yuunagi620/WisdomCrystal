// Scene.h

#pragma once

#include "object/GameObjManager.h"


class Scene {

public:
    virtual ~Scene() {}

    virtual bool Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice) = 0;

    virtual Scene* Update(GameObjManager *gameObjManager) = 0;
};
