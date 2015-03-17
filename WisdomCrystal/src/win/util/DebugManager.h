// DebugManager.h

#pragma once

#include <Windows.h>
#include <string>


namespace DebugManager {

void OutputString(const std::wstring& string);
void OutputValue(int value);
void OutputValue(double value);
void OutputValue(float value);

} // namespace DebugManager
