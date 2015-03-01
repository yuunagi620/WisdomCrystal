// SafeRelease.h

#pragma once


template <typename T>
inline unsigned long SafeRelease(T **ppT) {
    if (*ppT != nullptr) {
        return (*ppT)->Release();
    }

    return 0;
}


// SwapChain 用の特殊化
template <>
inline unsigned long SafeRelease<IDXGISwapChain>(IDXGISwapChain **ppT) {
    if (*ppT != nullptr) {

        // SwapChainを解放する前に必ずウィンドウモードに切り替えておく
        (*ppT)->SetFullscreenState(false, nullptr); 
        return (*ppT)->Release();
    }

    return 0;
}


// SourceVoice 用の特殊化
#include <XAudio2.h>
template <>
inline unsigned long SafeRelease<IXAudio2SourceVoice>(IXAudio2SourceVoice **ppT) {
    if (*ppT != nullptr) {
        (*ppT)->Stop();
        (*ppT)->DestroyVoice();
    }

    return 0;
}
