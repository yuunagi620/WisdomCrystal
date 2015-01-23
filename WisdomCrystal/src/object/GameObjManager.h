// GameObjManager.h

#pragma once

#include <boost/noncopyable.hpp>

#include "GameObject.h"
#include "GraphicsDevice.h"
#include "SoundDevice.h"


class GameObjManager : private boost::noncopyable {

public:
    GameObjManager();
    virtual ~GameObjManager();

    bool Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice);
    void Cleanup();
    void Update();
    void Deactivate();

    bool Activate(int initX, int initY, int objID);

private:
    void activateForInitAndCleanup();

    static GameObjManager mGameObjManager;
    static std::vector<GameObject*> mActiveGameObjects;
};
