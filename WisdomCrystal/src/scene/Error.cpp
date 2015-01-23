// Error.cpp

// Includes
#include "Error.h"


Error::~Error() {
    // empty
}


Scene *Error::Update(GameObjManager *gameObjManager) {
    PostQuitMessage(0);
    return this;
}