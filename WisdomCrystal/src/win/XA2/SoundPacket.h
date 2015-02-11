// SoundPacket.h

#pragma once

#include "WaveData.h"

#include <vector>


class SoundPacket {

public:
    SoundPacket();
    virtual ~SoundPacket();

    void Init(std::vector<unsigned char> *srcBuffer, const long begin, const long end);
    void Init(WaveData* waveData);

    inline std::vector<unsigned char>* GetBufferPtr() {
        return &mBuffer;
    }
    inline const long GetDataSize() const {
        return mDataSize;
    }

    void ResetSoundPacket(std::shared_ptr<IXAudio2SourceVoice> targetSourceVoice);
    void AddSoundPacket(std::shared_ptr<IXAudio2SourceVoice> targetSourceVoice);

private:
    std::vector<unsigned char> mBuffer;
    long mDataSize;
};


