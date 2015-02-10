// GameObjManager.h

#pragma once

#include <unordered_map>
#include <boost/noncopyable.hpp>

#include "GameObject.h"
#include "GameObjectId.h"
#include "GraphicsDevice.h"
#include "SoundDevice.h"


class GameObjManager : private boost::noncopyable {

public:
    GameObjManager();
    virtual ~GameObjManager();

    bool Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice);
    bool Activate(const GameObjectId initId, const int initX, const int initY);
    void Update();

private:
    std::unordered_multimap<GameObjectId, std::unique_ptr<GameObject>> mGameObjectMap;
};
