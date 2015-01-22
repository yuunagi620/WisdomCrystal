// DebugManager.h

#pragma once

#include <Windows.h>
#include <string>

#pragma warning (disable: 4005) // C4005 Œx–³‹
#include <boost/lexical_cast.hpp>
#pragma warning (default: 4005) // C4005 Œx‰ğœ


namespace DebugManager {

void OutputString(const std::wstring& string);

template<typename T>
void OutputValue(const T value) {
    std::wstring string = boost::lexical_cast<std::wstring>(value);
    string += TEXT("\n");
    DebugManager::OutputString(string);
}

} // namespace DebugManager
