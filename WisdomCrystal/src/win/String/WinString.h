// WinString.h

#pragma once

#include <string>


class WinString : public std::basic_string<TCHAR> {

public:

    // �f�t�H���g�R���X�g���N�^
    WinString();

    // TCHAR ����\�z
    // UNICODE ���`���Ă��邩�ɂ����
    // TCHAR ��char �� WCHAR �ɕς��̂� explicit �͂��Ȃ�
    WinString(const TCHAR* string);
    WinString(const std::basic_string<TCHAR>& string);

    // ���l����\�z
    explicit WinString(const int value) throw();
    explicit WinString(double value) throw();
    explicit WinString(float value) throw();

    virtual ~WinString();
};
