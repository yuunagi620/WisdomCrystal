// Input.h

#pragma once

#include <Windows.h>

#include "win/joypad/Joypad.h"


namespace Input {

typedef enum KeyTag {
    NONE    = 0x00,
    UP      = 0x01, 
    DOWN    = 0x02,
    LEFT    = 0x04,
    RIGHT   = 0x08,
    SPACE   = 0x10,
    C       = 0x20,
} Key;

// ƒL[“ü—Í‚Ì”»’è‚ğ‚·‚é
bool IsKeyPressed(Key key);

} // namespace Input
