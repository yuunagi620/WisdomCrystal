// Playing.cpp

// Includes
#include "Playing.h"
#include "object/GameObjManager.h"


Playing::~Playing() {
    // empty
}


bool Playing::Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice) {
    // do notihng.
    return true;
}


Scene* Playing::Update(GameObjManager *gameObjManager) {
    gameObjManager->Update();
    return this;
}