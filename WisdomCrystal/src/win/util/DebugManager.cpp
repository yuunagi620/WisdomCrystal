// DebugManager.cpp



#include "DebugManager.h"


void DebugManager::OutputString(const std::wstring& string) {
    OutputDebugString(string.c_str());
}


