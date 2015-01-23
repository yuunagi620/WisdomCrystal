// JoypadManager.h

#pragma once

#include <Windows.h>
#include "JoypadCode.h"


namespace JoypadManager {

// Joypad が接続されているか判定する
bool CheackJoypadDevices(JoypadID id);

// Joypad のボタンもしくはアナログパッドの傾きから押されているか判定する
bool JoypadKeyDown(JoypadID id, JoypadButton joypadcode);

// X 方向のアナログパッド傾き角度を取得する
float JoypadAnalogX(JoypadID id);

// Y 方向のアナログパッド傾き角度を取得する
float JoypadAnalogY(JoypadID id);

} // namespace JoypadManager
