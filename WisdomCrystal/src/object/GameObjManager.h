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
    void Activate(const int initX, const int initY);
    void Update();

private:
    static const int MAX_GAME_OBJCT = 1000;

    std::array<std::unique_ptr<GameObject>, MAX_GAME_OBJCT> mGameObjectArray;
};
