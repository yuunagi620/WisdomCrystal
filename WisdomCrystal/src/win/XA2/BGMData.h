// BGMData.h

#pragma once

#include <vector>

#include "WaveData.h"


class BGMData {

public:
    explicit BGMData(const unsigned int packetNum = 2);
    virtual ~BGMData();

    bool Init(SoundDevice* soundDevice, LPTSTR waveFilePath);
    void Cleanup();

    void StartBGM();
    void UpdateBGM();

    void SetBGMVolume(const float volume);

    void ResetSourceVoice();

private:
    WaveData mWaveData;
    int mNextPacket;
    
    IXAudio2SourceVoice *mSourceVoiceForBGM;
};
