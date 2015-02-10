// Playing.cpp

#include "Playing.h"
#include "object/GameObjManager.h"


Playing::Playing() : mGameObjManager(nullptr),
                     mBackGround()
{
    // empty
}


Playing::~Playing() {
    // empty
}


bool Playing::Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice, GameObjManager *gameObjManager) {
    mGameObjManager = gameObjManager;

    if (mBackGround.Init(graphicsDevice, 1) == false) {
        return false;
    }
    return true;
}


Scene* Playing::Update() {
    mBackGround.Draw();
    mGameObjManager->Update();
    return this;
}