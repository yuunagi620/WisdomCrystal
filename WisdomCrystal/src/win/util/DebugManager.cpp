// DebugManager.cpp

#include "DebugManager.h"

void DebugManager::OutputStr(const wchar_t *str) {
    OutputDebugString(str);
}


void DebugManager::OutputVal(const double val) {
    wchar_t buf[1024];
    _snwprintf_s(buf, 1024, _TRUNCATE, L"%f\n", val);
    OutputDebugString(buf);
}
