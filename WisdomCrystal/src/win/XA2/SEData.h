// SEData.h

#pragma once

#include "SoundDevice.h"
#include "WaveData.h"


class SEData {

public:
    SEData();
    virtual ~SEData();

    bool Init(SoundDevice* soundDevice, LPTSTR waveFilePath);
    void Cleanup();

    void StartSE();
    void SetSEVolume(const float volume);
    void ResetSourceVoice();

private:
    WaveData mWaveData;
    IXAudio2SourceVoice *mSourceVoiceForSE;
};
