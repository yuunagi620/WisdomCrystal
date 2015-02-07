// BGMData.h

#pragma once

#include <vector>

#include "WaveData.h"
#include "SoundPacket.h"


class BGMData {

public:
    explicit BGMData(const unsigned int packetNum = 2);
    virtual ~BGMData();

    bool Init(SoundDevice* soundDevice, LPTSTR waveFilePath);
    void Cleanup();

    void StartBGM();
    void UpdateBGM();

    void SetBGMVolume(const float volume);

private:
    bool divideWaveData();

    WaveData mWaveData;
    std::vector<SoundPacket>mSoundPacket;
    int mNextPacket;
    
    IXAudio2SourceVoice *mSourceVoiceForBGM;
};
