// Loading.cpp

// Includes
#include "Loading.h"
#include "Playing.h"
#include "object/GameObjManager.h"


Loading::~Loading() {
    // empty
}


Scene *Loading::Update(GameObjManager *gameObjManager) {

    return new Playing();
}