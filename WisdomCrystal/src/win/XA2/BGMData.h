// BGMData.h

#pragma once

#include <array>

#include "WaveData.h"
#include "SoundPacket.h"


class BGMData {

public:
    explicit BGMData(const unsigned int packetNum = 10);
    virtual ~BGMData();

    bool Init(SoundDevice* soundDevice, LPTSTR waveFilePath);

    void Start();
    void Stop();

    void UpdateBGM();

    void SetBGMVolume(const float volume);

private:
    void divideSoundPacket(WaveData* waveData);

private:
    const unsigned int SOUND_PACKET_NUM;
    int mNextPacketIndex;

    std::vector<SoundPacket> mSoundPacketArray;
    std::shared_ptr<IXAudio2SourceVoice> mSourceVoiceForBGM;
};
