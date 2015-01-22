// SafeRelease.h

#pragma once


template <class T>
inline void SafeRelease(T **ppT) {
    if (*ppT) {
        (*ppT)->Release();
        *ppT = nullptr;
    }
}
