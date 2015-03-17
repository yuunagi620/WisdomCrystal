// Loading.cpp

#include "Loading.h"
#include "Playing.h"
#include "object/GameObjManager.h"


Loading::Loading() {
    // empty
}


Loading::~Loading() {
    // empty
}


bool Loading::Init(GraphicsDevice *graphicsDevice,
                   SoundDevice *soundDevice,
                   GameObjManager *gameObjManager) {
    // do nothing.
    return true;
}


Scene *Loading::Update() {
    // do nothing.
    return new Playing();
}