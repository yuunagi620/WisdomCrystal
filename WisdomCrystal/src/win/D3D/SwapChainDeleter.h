// SwapChainDeleter.h

#pragma once


struct SwapChainDeleter {
    void operator ()(IDXGISwapChain *ptr) {
        if (ptr != nullptr) {

            // SwapChainを解放する前に必ずウィンドウモードに切り替えておく
            ptr->SetFullscreenState(false, nullptr); 
            ptr->Release();
            ptr = nullptr;
        }
    }
};
