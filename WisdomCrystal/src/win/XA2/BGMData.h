// BGMData.h

#pragma once


#include "WaveData.h"


class BGMData {

public:
    BGMData();
    virtual ~BGMData();

    bool Init(SoundDevice* soundDevice, LPTSTR waveFilePath);

    void Start();
    void Stop();

    void SetBGMVolume(const float volume);

    bool ResetSourceVoice();

private:
    WaveData mWaveData;
    IXAudio2SourceVoice* mSourceVoiceForBGM;
};
