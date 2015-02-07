// XAudio2Deleter.h

#pragma once


struct XAudio2Deleter {
    void operator ()(IXAudio2 *ptr) {
        if (ptr != nullptr) {
            ptr->Release();
            ptr = nullptr;
        }
    }
};
