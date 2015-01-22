// SEData.h

#pragma once

#include "SoundPacket.h"
#include "SoundDevice.h"


class SEData {

public:
    SEData();
    virtual ~SEData();

    bool Init(SoundDevice* soundDevice, TCHAR *inWaveFilePath);
    void Cleanup();

    void StartSE();
    void SetSEVolume(const float volume);

private:
    IXAudio2SourceVoice *mSourceVoiceForSE;
    SoundPacket mSESoundPacket;
};
