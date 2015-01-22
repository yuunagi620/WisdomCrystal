// BGMData.h

#pragma once

#include "SoundPacket.h"
#include <vector>

class BGMData {

public:
    explicit BGMData(const unsigned int packetNum = 3);
    virtual ~BGMData();

    bool Init(SoundDevice* soundDevice, TCHAR *inWaveFilePath);
    void Cleanup();

    void StartBGM();
    void UpdateBGM();

    void SetBGMVolume(const float volume);

private:
    const unsigned int SOUND_PACKET_NUM;

    IXAudio2SourceVoice *mSourceVoiceForBGM;
    std::vector<SoundPacket> mBGMSoundPacket;
    int mNextBGMPacket;

    void divideWaveData(const WaveData& waveData);
};
