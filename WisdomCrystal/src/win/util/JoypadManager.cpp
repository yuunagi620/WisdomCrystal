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

        // JOYPAD_BUTTON_28�ȉ�(�A�i���O�p�b�h�ȊO)�̔���
        if (joypadcode <= JOYPAD_BUTTON_28) {
            return ((joypadInfo.dwButtons & joypadcode) != 0); 
        } 

        // �A�i���O�p�b�h�̌X�����牟����Ă��邩����
        // max �� min �� 4 �Ŋ������l��␳�W���Ƃ��ė^���邱�Ƃŏ����ȌX�������m���Ȃ��悤�ɂ���
        switch (joypadcode) {
            case JOYPAD_BUTTON_UP:
                return (joypadInfo.dwYpos < joypadCaps.wYmin + (joypadCaps.wYmax - joypadCaps.wYmin) / 4);
            case JOYPAD_BUTTON_DOWN:
                return (joypadInfo.dwYpos > joypadCaps.wYmax - (joypadCaps.wYmax - joypadCaps.wYmin) / 4);
            case JOYPAD_BUTTON_LEFT:
                return (joypadInfo.dwXpos < joypadCaps.wXmin + (joypadCaps.wXmax - joypadCaps.wXmin) / 4);
            case JOYPAD_BUTTON_RIGHT:
                return (joypadInfo.dwXpos > joypadCaps.wXmax - (joypadCaps.wXmax - joypadCaps.wXmin) / 4);
            default:
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

        float centerX = (static_cast<float>(joypadCaps.wXmin + joypadCaps.wXmax)) / 2.0f;
        float differentX = static_cast<float>(joypadCaps.wXmax - joypadCaps.wXmin);

        // X���W�̌X����̌W�������߂�
        float coefficient = (static_cast<float>(joypadInfo.dwXpos) - centerX) * 2.0f;

        // �ő�ƍŏ��̍��Ŋ�����, 0����1�Ɋۂ߂�
        coefficient /= differentX;

        // 0.1 �ȉ��͐؂�̂Ă� 0 ��Ԃ�
        if (fabsf(coefficient) >= 0.1f) {
            return coefficient;
        } else {
            return 0.0f;
        }
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

        float centerY = (static_cast<float>(joypadCaps.wYmin + joypadCaps.wYmax)) / 2.0f;
        float differentY = static_cast<float>(joypadCaps.wYmax - joypadCaps.wYmin);

        // Y���W�̌X����̌W�������߂�
        float coefficient = (static_cast<float>(joypadInfo.dwYpos) - centerY) * 2.0f;

        // �ő�ƍŏ��̍��Ŋ�����, 0����1�Ɋۂ߂�
        coefficient /= differentY;

        // 0.1 �ȉ��͐؂�̂Ă� 0 ��Ԃ�
        if (fabsf(coefficient) >= 0.1f) {
            return coefficient;
        } else {
            return 0.0f;
        }
    }

    return 0.0f;
}
