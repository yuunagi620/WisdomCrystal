// BGMData.h

#pragma once

#include "win/SoundDevice.h"
#include "WaveFile.h"


class BGMData {

public:
    BGMData();
    virtual ~BGMData();

    bool Init(SoundDevice* soundDevice, const std::string& filePath);
    void Start();
    void Stop();
    void SetVolume(const float volume);

private:
    WaveFile mWaveFile;
    std::shared_ptr<IXAudio2SourceVoice> mSourceVoice;
};
