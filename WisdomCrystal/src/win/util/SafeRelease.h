// SafeRelease.h

#pragma once


template <typename T>
inline void SafeRelease(T **ppT) {
    if (*ppT) {
        (*ppT)->Release();
        *ppT = nullptr;
    }
}
