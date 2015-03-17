// GameObjManager.h

#pragma once

#include <memory>
#include <unordered_map>
#include <boost/noncopyable.hpp>

#include "GameObject.h"
#include "GameObjectId.h"
#include "win/GraphicsDevice.h"
#include "win/SoundDevice.h"


class GameObjManager : private boost::noncopyable {

public:
    GameObjManager();
    virtual ~GameObjManager();

    bool Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice);
    bool Activate(GameObjectId initId, int initX, int initY);
    void Update();

private:
    std::unordered_multimap<GameObjectId, std::shared_ptr<GameObject>> mGameObjectMap;
};
