// MasteringVoiceDeleter.h

#pragma once


struct MasteringVoiceDeleter {
    void operator ()(IXAudio2MasteringVoice *ptr) {
        if (ptr != nullptr) {
            ptr->DestroyVoice();
            ptr = nullptr;
        }
    }
};
