// GameObjManager.h

#pragma once

#include <array>
#include <boost/noncopyable.hpp>

#include "GameObject.h"
#include "GraphicsDevice.h"
#include "SoundDevice.h"


class GameObjManager : private boost::noncopyable {

public:
    GameObjManager();
    virtual ~GameObjManager();

    bool Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice);
    void Cleanup();
    void Update();

    bool Activate(int initX, int initY, int objID);

private:
    static const int MAX_GAME_OBJCT = 1080;
    static const int NUM_GAME_OBJECT = 2;

    std::array<std::unique_ptr<GameObject>, MAX_GAME_OBJCT> mActiveGameObjects;
};
