// SoundPacket.h

#pragma once

#include "WaveData.h"

#include <vector>


class SoundPacket {

public:
    SoundPacket();
    virtual ~SoundPacket();

    bool Init(std::vector<BYTE> *srcBuffer, const long begin, const long end);
    bool Init(WaveData* waveData);

    inline std::vector<BYTE>* GetBufferPtr() {
        return &mBuffer;
    }
    inline const long GetDataSize() const {
        return mDataSize;
    }

    void ResetSoundPacket(std::shared_ptr<IXAudio2SourceVoice> targetSourceVoice);
    void AddSoundPacket(std::shared_ptr<IXAudio2SourceVoice> targetSourceVoice);

private:
    std::vector<BYTE> mBuffer;
    long mDataSize;
};


