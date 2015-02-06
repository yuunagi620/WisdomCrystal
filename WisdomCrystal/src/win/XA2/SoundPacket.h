// SoundPacket.h

#pragma once

#include "WaveData.h"

#include <XAudio2.h>
#include <vector>


class SoundPacket {

public:
    SoundPacket();
    virtual ~SoundPacket();

    bool Init(std::vector<BYTE> *srcBuffer);
    bool Init(WaveData* waveData);

    inline BYTE* GetBuffer() {
        return &mBuffer.front();
    }
    inline const long GetDataSize() const {
        return mDataSize;
    }

private:
    std::vector<BYTE> mBuffer;
    long mDataSize;
};


