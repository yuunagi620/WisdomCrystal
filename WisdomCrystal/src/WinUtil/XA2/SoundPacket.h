// SoundPacket.h

#pragma once

#include "WaveData.h"

#include <XAudio2.h>
#include <memory>


class SoundPacket {

public:
    SoundPacket();
    virtual ~SoundPacket();

    bool Init(const BYTE *srcBuffer, const long dataSize);
    bool Init(const WaveData& waveData);

    inline BYTE *GetBuffer() const {
        return mBuffer.get();
    }

    inline const long GetDataSize() const {
        return mDataSize;
    }

    static void AddSoundPacket(IXAudio2SourceVoice *targetSourceVoice,
                               const SoundPacket& soundPacket);

    static void ResetSourceVoice(IXAudio2SourceVoice *targetSourceVoice,
                                 const SoundPacket& soundPacket);

private:
    std::shared_ptr<BYTE> mBuffer;
    long mDataSize;

};


