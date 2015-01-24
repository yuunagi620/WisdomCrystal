// WinString.h

#pragma once

#include <string>


class WinString {

public:
    WinString();
    virtual ~WinString();

private:
    std::basic_string<TCHAR> mString;
};
