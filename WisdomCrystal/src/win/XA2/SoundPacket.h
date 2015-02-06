// SoundPacket.h

#pragma once

#include "WaveData.h"

#include <vector>


class SoundPacket {

public:
    SoundPacket();
    virtual ~SoundPacket();

    bool Init(std::vector<BYTE> *srcBuffer);
    bool Init(WaveData* waveData);

    inline std::vector<BYTE>* GetBufferPtr() {
        return &mBuffer;
    }
    inline const long GetDataSize() const {
        return mDataSize;
    }

private:
    std::vector<BYTE> mBuffer;
    long mDataSize;
};


