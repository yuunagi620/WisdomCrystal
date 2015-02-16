// Deleter.h

#pragma once


template <typename T>
struct Deleter {
    void operator()(T *ptr) {
        if (ptr != nullptr) {
            ptr->Release();
            ptr = nullptr;
        }
    }
};


// SourceVoice
#include <XAudio2.h>
template <>
struct Deleter<IXAudio2SourceVoice> {
    void operator()(IXAudio2SourceVoice *ptr) {
        if (ptr != nullptr) {
            ptr->Stop();
            ptr->DestroyVoice();
            ptr = nullptr;
        }
    }
};


// MasteringVoice
template <>
struct Deleter<IXAudio2MasteringVoice> {
    void operator()(IXAudio2MasteringVoice *ptr) {
        if (ptr != nullptr) {
            ptr->DestroyVoice();
            ptr = nullptr;
        }
    }
};


// SwapChain
template <>
struct Deleter<IDXGISwapChain> {
    void operator()(IDXGISwapChain *ptr) {
        if (ptr != nullptr) {

            // SwapChainを解放する前に必ずウィンドウモードに切り替えておく
            ptr->SetFullscreenState(false, nullptr); 
            ptr->Release();
            ptr = nullptr;
        }
    }
};

