// DebugManager.cpp

#include "DebugManager.h"


void DebugManager::OutputString(const std::wstring& string) {
    OutputDebugString(string.c_str());
}


void DebugManager::OutputValue(int value) {
    std::wstring string = std::to_wstring(value) + TEXT("\n");
    OutputDebugString(string.c_str());
}


void DebugManager::OutputValue(double value) {
    std::wstring string = std::to_wstring(value) + TEXT("\n");
    OutputDebugString(string.c_str());
}


void DebugManager::OutputValue(float value) {
    std::wstring string = std::to_wstring(value) + TEXT("\n");
    OutputDebugString(string.c_str());
}