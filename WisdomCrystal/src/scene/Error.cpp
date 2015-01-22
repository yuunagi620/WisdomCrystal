// Error.cpp

// Includes
#include "Error.h"


Error::~Error() {
    // empty
}


Scene *Error::Update() {
    PostQuitMessage(0);
    return this;
}