// Playing.cpp

// Includes
#include "Playing.h"
#include "object/GameObjManager.h"


Playing::Playing() : mGameObjManager(nullptr) {
    // empty
}


Playing::~Playing() {
    // empty
}


bool Playing::Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice, GameObjManager *gameObjManager) {
    mGameObjManager = gameObjManager;
    return true;
}


Scene* Playing::Update() {
    mGameObjManager->Update();
    return this;
}