// SourceVoiceDeleter.h

#pragma once


struct SourceVoiceDeleter {
    void operator ()(IXAudio2SourceVoice *ptr) {
        if (ptr != nullptr) {
            ptr->Stop();
            ptr->DestroyVoice();
            ptr = nullptr;
        }
    }
};
