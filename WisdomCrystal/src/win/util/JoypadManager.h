// JoypadManager.h

#pragma once

#include <Windows.h>
#include "JoypadCode.h"


namespace JoypadManager {

// Joypad ���ڑ�����Ă��邩���肷��
bool CheackJoypadDevices(JoypadID id);

// Joypad �̃{�^���������̓A�i���O�p�b�h�̌X�����牟����Ă��邩���肷��
bool JoypadKeyDown(JoypadID id, JoypadButton joypadcode);

// X �����̃A�i���O�p�b�h�X���p�x���擾����
float JoypadAnalogX(JoypadID id);

// Y �����̃A�i���O�p�b�h�X���p�x���擾����
float JoypadAnalogY(JoypadID id);

} // namespace JoypadManager
