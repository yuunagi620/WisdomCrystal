// JoypadManager.cpp

#include "JoypadManager.h"


bool JoypadManager::CheackJoypadDevices() {
    JOYINFOEX joypadInfo;
    SecureZeroMemory(&joypadInfo, sizeof(joypadInfo));

	if (joyGetPosEx(INPUT_PAD1, &joypadInfo) == JOYERR_NOERROR) {
        return true;
    }

    return false;
}


bool JoypadManager::JoypadKeyDown(JoypadID id, JoypadCode joypadcode) {
    JOYINFOEX joypadInfo;
    SecureZeroMemory(&joypadInfo, sizeof(joypadInfo));

    JOYCAPS joypadCaps;
    SecureZeroMemory(&joypadCaps, sizeof(joypadCaps));

    joyGetDevCaps(id, &joypadCaps, sizeof(joypadCaps));
    joypadInfo.dwSize  = sizeof(joypadInfo);
    joypadInfo.dwFlags = JOY_RETURNBUTTONS;

    if (joyGetPosEx(id, &joypadInfo) == JOYERR_NOERROR) {
        if (joypadcode <= PAD_INPUT_28) {
            return (joypadInfo.dwButtons & joypadcode) != 0;
        } else if (joypadcode == PAD_INPUT_UP) {
            return (joypadInfo.dwYpos < joypadCaps.wYmin + (joypadCaps.wYmax - joypadCaps.wYmin) / 3) != 0;
        } else if (joypadcode == PAD_INPUT_DOWN) {
            return (joypadInfo.dwYpos > joypadCaps.wYmax - (joypadCaps.wYmax - joypadCaps.wYmin) / 3) != 0;
        } else if (joypadcode == PAD_INPUT_LEFT) {
            return (joypadInfo.dwXpos < joypadCaps.wXmin + (joypadCaps.wXmax - joypadCaps.wXmin) / 3) != 0;
        } else if (joypadcode == PAD_INPUT_RIGHT) {
            return (joypadInfo.dwYpos > joypadCaps.wXmax - (joypadCaps.wXmax - joypadCaps.wXmin) / 3) != 0;
        } else {
            return false;
        }
    }
    return false;
}


float JoypadManager::JoypadAnalogX(JoypadID id) {
    JOYINFOEX joypadInfo;
    SecureZeroMemory(&joypadInfo, sizeof(joypadInfo));

    JOYCAPS joypadCaps;
    SecureZeroMemory(&joypadCaps, sizeof(joypadCaps));

    joyGetDevCaps(id, &joypadCaps, sizeof(joypadCaps));
    joypadInfo.dwSize  = sizeof(joypadInfo);
    joypadInfo.dwFlags = JOY_RETURNX;

    if (joyGetPosEx(id, &joypadInfo) == JOYERR_NOERROR) {
        const float center((static_cast<float>(joypadCaps.wXmin + joypadCaps.wXmax)) / 2.f);
        const float diff(static_cast<float>(joypadCaps.wXmax - joypadCaps.wXmin));
        const float val((static_cast<float>(joypadInfo.dwXpos) - center) * 2.f / diff);
        return fabsf(val) < 0.1f ? 0.f : val;
    }

    return false;
}


float JoypadManager::JoypadAnalogY(JoypadID id) {
    JOYINFOEX joypadInfo;
    SecureZeroMemory(&joypadInfo, sizeof(joypadInfo));

    JOYCAPS joypadCaps;
    SecureZeroMemory(&joypadCaps, sizeof(joypadCaps));

    joyGetDevCaps(id, &joypadCaps, sizeof(joypadCaps));
    joypadInfo.dwSize  = sizeof(joypadInfo);
    joypadInfo.dwFlags = JOY_RETURNY;
    if (joyGetPosEx(id, &joypadInfo) == JOYERR_NOERROR) {
        const float center((static_cast<float>(joypadCaps.wYmin + joypadCaps.wYmax)) / 2.f);
        const float diff(static_cast<float>(joypadCaps.wYmax - joypadCaps.wYmin));
        const float val((static_cast<float>(joypadInfo.dwYpos) - center) * 2.f / diff);
        return fabsf(val) < 0.1f ? 0.f : val;
    }

    return false;
}