// WinString.h

// Includes
#include "WinString.h"

#pragma warning (disable: 4005) // C4005 åxçêñ≥éã
#include <boost/lexical_cast.hpp>
#pragma warning (default: 4005) // C4005 åxçêâèú


WinString::WinString() : std::basic_string<TCHAR>() {
    // empty
}


WinString::WinString(const TCHAR* string) : std::basic_string<TCHAR>(string) {
    // empty
}


WinString::WinString(const std::basic_string<TCHAR>& string) : std::basic_string<TCHAR>(string) {
    // empty
}


WinString::WinString(const int value) :
    std::basic_string<TCHAR>(boost::lexical_cast<std::basic_string<TCHAR>>(value)) {
    // empty
}


WinString::WinString(const double value) :
    std::basic_string<TCHAR>(boost::lexical_cast<std::basic_string<TCHAR>>(value)) {
    // empty
}


WinString::WinString(const float value) :
    std::basic_string<TCHAR>(boost::lexical_cast<std::basic_string<TCHAR>>(value)) {
    // empty
}


WinString::~WinString() {
    // empty
}
