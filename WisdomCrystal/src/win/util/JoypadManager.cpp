// JoypadManager.cpp

#include "JoypadManager.h"


bool JoypadManager::CheackJoypadDevices(JoypadID id) {
    JOYINFOEX joypadInfo;
    SecureZeroMemory(&joypadInfo, sizeof(joypadInfo));
    joypadInfo.dwSize  = sizeof(joypadInfo);
    joypadInfo.dwFlags = JOY_RETURNALL;

	if (joyGetPosEx(JOYPAD_1, &joypadInfo) == JOYERR_NOERROR) {
        return true;
    }

    return false;
}


bool JoypadManager::JoypadKeyDown(JoypadID id, JoypadButton joypadcode) {
    JOYINFOEX joypadInfo;
    SecureZeroMemory(&joypadInfo, sizeof(joypadInfo));
    joypadInfo.dwSize  = sizeof(joypadInfo);
    joypadInfo.dwFlags = JOY_RETURNBUTTONS;

    JOYCAPS joypadCaps;
    SecureZeroMemory(&joypadCaps, sizeof(joypadCaps));
    joyGetDevCaps(id, &joypadCaps, sizeof(joypadCaps));

    if (joyGetPosEx(id, &joypadInfo) == JOYERR_NOERROR) {

        // アナログパッド以外が押されたか判定
        if (joypadcode <= JOYPAD_BUTTON_28) {
            return ((joypadInfo.dwButtons & joypadcode) != 0);
        } else if (joypadcode == JOYPAD_BUTTON_UP) {
            return (joypadInfo.dwYpos < joypadCaps.wYmin + (joypadCaps.wYmax - joypadCaps.wYmin) / 3) != 0;
        } else if (joypadcode == JOYPAD_BUTTON_DOWN) {
            return (joypadInfo.dwYpos > joypadCaps.wYmax - (joypadCaps.wYmax - joypadCaps.wYmin) / 3) != 0;
        } else if (joypadcode == JOYPAD_BUTTON_LEFT) {
            return (joypadInfo.dwXpos < joypadCaps.wXmin + (joypadCaps.wXmax - joypadCaps.wXmin) / 3) != 0;
        } else if (joypadcode == JOYPAD_BUTTON_RIGHT) {
            return (joypadInfo.dwXpos > joypadCaps.wXmax - (joypadCaps.wXmax - joypadCaps.wXmin) / 3) != 0;
        } else {
            return false;
        }
    }
    return false;
}


float JoypadManager::JoypadAnalogX(JoypadID id) {
    JOYINFOEX joypadInfo;
    SecureZeroMemory(&joypadInfo, sizeof(joypadInfo));
    joypadInfo.dwSize  = sizeof(joypadInfo);
    joypadInfo.dwFlags = JOY_RETURNX;

    JOYCAPS joypadCaps;
    SecureZeroMemory(&joypadCaps, sizeof(joypadCaps));
    joyGetDevCaps(id, &joypadCaps, sizeof(joypadCaps));

    if (joyGetPosEx(id, &joypadInfo) == JOYERR_NOERROR) {
        const float center((static_cast<float>(joypadCaps.wXmin + joypadCaps.wXmax)) / 2.f);
        const float diff(static_cast<float>(joypadCaps.wXmax - joypadCaps.wXmin));
        const float val((static_cast<float>(joypadInfo.dwXpos) - center) * 2.f / diff);
        return (fabsf(val) < 0.1f) ? 0.f : val;
    }

    return 0.0f;
}


float JoypadManager::JoypadAnalogY(JoypadID id) {
    JOYINFOEX joypadInfo;
    SecureZeroMemory(&joypadInfo, sizeof(joypadInfo));
    joypadInfo.dwSize  = sizeof(joypadInfo);
    joypadInfo.dwFlags = JOY_RETURNY;

    JOYCAPS joypadCaps;
    SecureZeroMemory(&joypadCaps, sizeof(joypadCaps));
    joyGetDevCaps(id, &joypadCaps, sizeof(joypadCaps));

    if (joyGetPosEx(id, &joypadInfo) == JOYERR_NOERROR) {
        const float center((static_cast<float>(joypadCaps.wYmin + joypadCaps.wYmax)) / 2.f);
        const float diff(static_cast<float>(joypadCaps.wYmax - joypadCaps.wYmin));
        const float val((static_cast<float>(joypadInfo.dwYpos) - center) * 2.f / diff);
        return (fabsf(val) < 0.1f) ? 0.f : val;
    }

    return 0.0f;
}