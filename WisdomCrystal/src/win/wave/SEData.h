// SEData.h

#pragma once

#include "win/SoundDevice.h"
#include "WaveFile.h"


class SEData {

public:
    SEData();
    virtual ~SEData();

    bool Init(SoundDevice* soundDevice, const std::string& filePath);
    void Start();
    void SetVolume(const float volume);

private:
    void resetSourceVoice();
    
private:
    WaveFile mWaveFile;
    std::shared_ptr<IXAudio2SourceVoice> mSourceVoice;
};
