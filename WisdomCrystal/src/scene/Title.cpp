// Title.cpp

// Includes
#include "Title.h"
#include "Loading.h"


Scene *Title::Update() {
    Scene *next = this;

    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        next = new Loading();
    }

    return next;
}
