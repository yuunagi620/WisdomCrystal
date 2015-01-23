// Scene.h

#pragma once

#include "object/GameObjManager.h"


class Scene {

public:
    virtual ~Scene() {}
    virtual Scene *Update(GameObjManager *gameObjManager) = 0;
};
