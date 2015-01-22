// DebugManager.cpp

#include <boost/lexical_cast.hpp>

#include "DebugManager.h"


void DebugManager::OutputString(const std::wstring& string) {
    OutputDebugString(string.c_str());
}


void DebugManager::OutputValue(const int value) {
    std::wstring string = boost::lexical_cast<std::wstring>(value);
    string += TEXT("\n");
    OutputDebugString(string.c_str());
}


void DebugManager::OutputValue(const double value) {
    std::wstring string = boost::lexical_cast<std::wstring>(value);
    string += TEXT("\n");
    OutputDebugString(string.c_str());
}
