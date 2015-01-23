// Title.cpp

// Includes
#include "Title.h"
#include "Loading.h"
#include "win/util/Input.h"


Title::~Title() {
    // empty
}


Scene *Title::Update(GameObjManager *gameObjManager) {
    Scene *next = this;

    if (Input::IsKeyPressed(Input::SPACE)) {
        next = new Loading();
    }

    return next;
}
