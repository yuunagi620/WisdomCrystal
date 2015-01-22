// DebugManager.h

#pragma once

#include <Windows.h>
#include <string>


namespace DebugManager {

void OutputString(const std::wstring& string);
void OutputValue(const int value);
void OutputValue(const double value);

} // namespace DebugManager
