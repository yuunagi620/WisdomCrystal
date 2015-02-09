// Error.cpp

// Includes
#include "Error.h"


Error::~Error() {
    // empty
}


bool Error::Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice) {
    // do notihng.
    return true;
}


Scene *Error::Update(GameObjManager *gameObjManager) {
    PostQuitMessage(0);
    return this;
}