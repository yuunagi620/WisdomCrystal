// Input.h

#pragma once

#include <Windows.h>

#include "win/joypad/Joypad.h"


namespace Input {

typedef enum KeyTag {
    NONE    = 0,
    UP      = (1 << 1), 
    DOWN    = (1 << 2),
    LEFT    = (1 << 3),
    RIGHT   = (1 << 4),
    SPACE   = (1 << 5),
    C       = (1 << 6),
} Key;

// ƒL[“ü—Í‚Ì”»’è‚ð‚·‚é
bool IsKeyPressed(Key key);

} // namespace Input
