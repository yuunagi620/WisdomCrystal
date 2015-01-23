// Input.cpp

#include "Input.h"


bool Input::IsKeyPressed(Key key) {
    switch (key) {
        case NONE:  {
            return false;
        }
        case UP:    {
            return ((GetAsyncKeyState(VK_UP) & 0x8000) ||
                    (Joypad::JoypadKeyDown(Joypad::JOYPAD_1, Joypad::JOYPAD_BUTTON_UP)));
        }
        case DOWN:  {
            return ((GetAsyncKeyState(VK_DOWN) & 0x8000) ||
                    (Joypad::JoypadKeyDown(Joypad::JOYPAD_1, Joypad::JOYPAD_BUTTON_DOWN)));
        }
        case LEFT:  {
            return ((GetAsyncKeyState(VK_LEFT) & 0x8000) ||
                    (Joypad::JoypadKeyDown(Joypad::JOYPAD_1, Joypad::JOYPAD_BUTTON_LEFT)));
        }
        case RIGHT: {
            return ((GetAsyncKeyState(VK_RIGHT) & 0x8000) ||
                    (Joypad::JoypadKeyDown(Joypad::JOYPAD_1, Joypad::JOYPAD_BUTTON_RIGHT)));
        }
        case SPACE: {
            return ((GetAsyncKeyState(VK_SPACE) & 0x8000) ||
                    (Joypad::JoypadKeyDown(Joypad::JOYPAD_1, Joypad::JOYPAD_BUTTON_1)));
        }
        case C:     {
            return ((GetAsyncKeyState('C') & 0x8000) ||
                    (Joypad::JoypadKeyDown(Joypad::JOYPAD_1, Joypad::JOYPAD_BUTTON_2)));
        }
        default:    {
            return false;
        }
    }
    
    return false;
}
