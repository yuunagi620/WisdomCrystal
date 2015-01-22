// JoypadManager.cpp

#include "JoypadManager.h"


bool JoypadManager::JoypadKeyDown(JoypadID id, JoypadCode joypadcode) {
    JOYINFOEX joypad_info;
    JOYCAPS joypad_caps;

    joyGetDevCaps(id, &joypad_caps, sizeof(joypad_caps));
    joypad_info.dwSize  = sizeof(joypad_info);
    joypad_info.dwFlags = JOY_RETURNBUTTONS;

    if (joyGetPosEx(id, &joypad_info) == JOYERR_NOERROR) {
        if (joypadcode <= PAD_INPUT_28) {
            return (joypad_info.dwButtons & joypadcode) != 0;
        } else if (joypadcode == PAD_INPUT_UP) {
            return (joypad_info.dwYpos < joypad_caps.wYmin + (joypad_caps.wYmax - joypad_caps.wYmin) / 3) != 0;
        } else if (joypadcode == PAD_INPUT_DOWN) {
            return (joypad_info.dwYpos > joypad_caps.wYmax - (joypad_caps.wYmax - joypad_caps.wYmin) / 3) != 0;
        } else if (joypadcode == PAD_INPUT_LEFT) {
            return (joypad_info.dwXpos < joypad_caps.wXmin + (joypad_caps.wXmax - joypad_caps.wXmin) / 3) != 0;
        }else if (joypadcode == PAD_INPUT_RIGHT) {
            return (joypad_info.dwYpos > joypad_caps.wXmax - (joypad_caps.wXmax - joypad_caps.wXmin) / 3) != 0;
        } else {
            return false;
        }
    }
    return false;
}


float JoypadManager::JoypadAnalogX(JoypadID id) {
    JOYINFOEX joypad_info;
    JOYCAPS joypad_caps;
    joyGetDevCaps(id, &joypad_caps, sizeof(joypad_caps));
    joypad_info.dwSize  = sizeof(joypad_info);
    joypad_info.dwFlags = JOY_RETURNX;
    if (joyGetPosEx(id, &joypad_info) == JOYERR_NOERROR) {
        const float center((static_cast<float>(joypad_caps.wXmin + joypad_caps.wXmax)) / 2.f);
        const float diff(static_cast<float>(joypad_caps.wXmax - joypad_caps.wXmin));
        const float val((static_cast<float>(joypad_info.dwXpos) - center) * 2.f / diff);
        return fabsf(val) < 0.1f ? 0.f : val;
    }
    return false;
}


float JoypadManager::JoypadAnalogY(JoypadID id) {
    JOYINFOEX joypad_info;
    JOYCAPS joypad_caps;
    joyGetDevCaps(id, &joypad_caps, sizeof(joypad_caps));
    joypad_info.dwSize  = sizeof(joypad_info);
    joypad_info.dwFlags = JOY_RETURNY;
    if (joyGetPosEx(id, &joypad_info) == JOYERR_NOERROR) {
        const float center((static_cast<float>(joypad_caps.wYmin + joypad_caps.wYmax)) / 2.f);
        const float diff(static_cast<float>(joypad_caps.wYmax - joypad_caps.wYmin));
        const float val((static_cast<float>(joypad_info.dwYpos) - center) * 2.f / diff);
        return fabsf(val) < 0.1f ? 0.f : val;
    }
    return false;
}