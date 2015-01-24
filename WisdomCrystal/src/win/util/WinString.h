// WinString.h

#pragma once

#include <string>


class WinString : public std::basic_string<TCHAR> {

public:

    // デフォルトコンストラクタ
    WinString();

    // TCHAR から構築
    explicit WinString(const std::basic_string<TCHAR>& string);

    // 数値から構築
    explicit WinString(const int value) throw();
    explicit WinString(double value) throw();
    explicit WinString(float value) throw();

    virtual ~WinString();
};
