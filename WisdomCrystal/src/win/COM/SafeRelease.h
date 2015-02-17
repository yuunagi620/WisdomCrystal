// SafeRelease.h

#pragma once


template <typename T>
inline unsigned long SafeRelease(T **ppT) {
    if (*ppT != nullptr) {
        return (*ppT)->Release();
    }

    return 0;
}


// SwapChain
template <>
inline unsigned long SafeRelease<IDXGISwapChain>(IDXGISwapChain **ppT) {
    if (*ppT != nullptr) {

        // SwapChain���������O�ɕK���E�B���h�E���[�h�ɐ؂�ւ��Ă���
        (*ppT)->SetFullscreenState(false, nullptr); 
        return (*ppT)->Release();
    }

    return 0;
}


// SourceVoice
#include <XAudio2.h>
template <>
inline unsigned long SafeRelease<IXAudio2SourceVoice>(IXAudio2SourceVoice **ppT) {
    if (*ppT != nullptr) {
        (*ppT)->Stop();
        (*ppT)->DestroyVoice();
    }

    return 0;
}
