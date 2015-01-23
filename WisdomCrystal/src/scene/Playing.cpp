// Playing.cpp

// Includes
#include "Playing.h"
#include "object/GameObjManager.h"


Playing::~Playing() {
    // empty
}


Scene *Playing::Update(GameObjManager *gameObjManager) {
    gameObjManager->Update();
    return this;
}