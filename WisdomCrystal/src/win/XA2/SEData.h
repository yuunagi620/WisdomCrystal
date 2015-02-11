// SEData.h

#pragma once

#include "SoundDevice.h"
#include "WaveData.h"


class SEData {

public:
    SEData();
    virtual ~SEData();

    bool Init(SoundDevice* soundDevice, const std::string& filePath);

    void StartSE();
    void SetSEVolume(const float volume);

private:
    void resetSourceVoice();
    
private:
    WaveData mWaveData;
    std::shared_ptr<IXAudio2SourceVoice> mSourceVoiceForSE;
};
