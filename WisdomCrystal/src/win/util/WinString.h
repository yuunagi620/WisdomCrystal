// WinString.h

#pragma once

#include <string>


class WinString : public std::basic_string<TCHAR> {

public:

    // デフォルトコンストラクタ
    WinString();

    // TCHAR から構築
    explicit WinString(const std::basic_string<TCHAR>& string);

    // int から構築
    explicit WinString(const int value) throw();

    // double から構築
    explicit WinString(double value) throw();

    // float から構築
    explicit WinString(float value) throw();

    virtual ~WinString();
};
