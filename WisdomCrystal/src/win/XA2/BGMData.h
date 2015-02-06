// BGMData.h

#pragma once

#include "WaveData.h"


class BGMData {

public:
    explicit BGMData(const unsigned int packetNum = 3);
    virtual ~BGMData();

    bool Init(SoundDevice* soundDevice, LPTSTR waveFilePath);
    void Cleanup();

    void StartBGM();
    void UpdateBGM();

    void SetBGMVolume(const float volume);

    void ResetSourceVoice();
    void AddSoundPacket();

private:
    WaveData mWaveData;
    IXAudio2SourceVoice *mSourceVoiceForBGM;
};
