// SwapChainDeleter.h

#pragma once


struct SwapChainDeleter {
    void operator ()(IDXGISwapChain *ptr) {
        if (ptr != nullptr) {

            // SwapChain���������O�ɕK���E�B���h�E���[�h�ɐ؂�ւ��Ă���
            ptr->SetFullscreenState(false, nullptr); 
            ptr->Release();
            ptr = nullptr;
        }
    }
};
