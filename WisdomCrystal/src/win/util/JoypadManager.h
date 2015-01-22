// JoypadManager.h

#pragma once

#include <Windows.h>
#include "JoypadCode.h"


namespace JoypadManager {

bool CheackJoypadDevices();

bool JoypadKeyDown(JoypadID id, JoypadCode joypadcode);
float JoypadAnalogX(JoypadID id);
float JoypadAnalogY(JoypadID id);

} // namespace JoypadManager
