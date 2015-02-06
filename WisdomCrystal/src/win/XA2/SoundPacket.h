// SoundPacket.h

#pragma once

#include "WaveData.h"

#include <XAudio2.h>
#include <memory>
#include <vector>


class SoundPacket {

public:
    SoundPacket();
    virtual ~SoundPacket();

    bool Init(std::vector<BYTE> *srcBuffer, const long dataSize);
    bool Init(WaveData* waveData);

    inline BYTE* GetBuffer() {
        return &mBuffer.front();
    }
    inline const long GetDataSize() const {
        return mDataSize;
    }

    static void AddSoundPacket(IXAudio2SourceVoice *targetSourceVoice,
                               SoundPacket *soundPacket);

    static void ResetSourceVoice(IXAudio2SourceVoice *targetSourceVoice,
                                 SoundPacket *soundPacket);

private:
    std::vector<BYTE> mBuffer;
    long mDataSize;
};


