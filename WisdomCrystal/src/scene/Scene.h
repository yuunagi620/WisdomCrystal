// Scene.h

#pragma once

#include "object/GameObjManager.h"


class Scene {

public:
    virtual ~Scene() {}

    virtual bool Init(GraphicsDevice *graphicsDevice,
                      SoundDevice *soundDevice,
                      GameObjManager *gameObjManager) = 0;

    virtual Scene* Update() = 0;
};
