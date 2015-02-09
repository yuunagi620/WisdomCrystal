// Loading.cpp

// Includes
#include "Loading.h"
#include "Playing.h"
#include "object/GameObjManager.h"


Loading::~Loading() {
    // empty
}


bool Loading::Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice) {
    // do notihng.
    return true;
}


Scene *Loading::Update(GameObjManager *gameObjManager) {

    return new Playing();
}