// Error.cpp

// Includes
#include "Error.h"

Scene *Error::Update() {
    PostQuitMessage(0);
    return this;
}