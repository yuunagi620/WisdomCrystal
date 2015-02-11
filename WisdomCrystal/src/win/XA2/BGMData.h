// BGMData.h

#pragma once

#include <array>

#include "win/wave/WaveFile.h"
#include "SoundPacket.h"


class BGMData {

public:
    BGMData();
    virtual ~BGMData();

    bool Init(SoundDevice* soundDevice, const std::string& filePath);

    void Start();
    void Stop();

    void UpdateBGM();

    void SetBGMVolume(const float volume);

private:
    bool divideSoundPacket(WaveFile* WaveFile);

private:
    const unsigned int SOUND_PACKET_NUM;
    int mNextPacketIndex;

    std::vector<SoundPacket> mSoundPacketArray;
    std::shared_ptr<IXAudio2SourceVoice> mSourceVoiceForBGM;
};
