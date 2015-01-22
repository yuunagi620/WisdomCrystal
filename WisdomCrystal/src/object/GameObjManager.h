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

    static GameObjManager *GetInstance();
    static std::vector<GameObject*> *GetActiveGameObjects();

    bool Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice);
    void Cleanup();
    void Update();
    void Deactivate();

    bool Activate(int initX, int initY, int objID);

private:
    static const int MAX_GAME_OBJECT;

    static GameObjManager mGameObjManager;
    static std::vector<GameObject*> mActiveGameObjects;

    
    void activateForInitAndCleanup();

};
