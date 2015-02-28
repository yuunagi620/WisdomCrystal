// BGMData.cpp

#include "BGMData.h"


BGMData::BGMData() : SOUND_PACKET_NUM(2),
                     mNextPacketIndex(0),
                     mSoundPacketArray(SOUND_PACKET_NUM),
                     mSourceVoiceForBGM(nullptr)
{
    // empty
}


BGMData::~BGMData() {
    // empty
}


bool BGMData::Init(SoundDevice* soundDevice, const std::string& filePath) {
    WaveFile WaveFile;

    // BGM データの読み込み
    if (WaveFile.Load(filePath) == false) {
        MessageBox(nullptr, TEXT("BGMData: Can not read WaveFile."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice の作成
    mSourceVoiceForBGM = soundDevice->CreateSourceVoice(WaveFile.GetWaveFormatEx(), nullptr);
    if (mSourceVoiceForBGM == nullptr) {
        MessageBox(nullptr, TEXT("BGMData: Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // BGM データを Sound Packet に分割
    if (divideSoundPacket(&WaveFile) == false) {
        MessageBox(nullptr, TEXT("BGMData: Can not divide sound packet."), TEXT("ERROR"), MB_OK);
        return false;
    }

    mSoundPacketArray.front().AddSoundPacket(mSourceVoiceForBGM);
    mNextPacketIndex = 1;
    return true;
}


void BGMData::Start() {
    mSourceVoiceForBGM->Start();
}


void BGMData::Stop() {
    mSourceVoiceForBGM->Stop();
}


void BGMData::UpdateBGM() {
    XAUDIO2_VOICE_STATE state;
    mSourceVoiceForBGM->GetState(&state);
    if (state.BuffersQueued >= SOUND_PACKET_NUM) {
        return;
    }
    mSoundPacketArray.at(mNextPacketIndex).AddSoundPacket(mSourceVoiceForBGM);
    ++mNextPacketIndex;
    mNextPacketIndex %= SOUND_PACKET_NUM; // 最大値を超えたら最初に戻る
}


void BGMData::SetVolume(const float volume) {
    mSourceVoiceForBGM->SetVolume(volume);
}


bool BGMData::divideSoundPacket(WaveFile* WaveFile) {

    try {
        unsigned int index = 0;

        // 最初のパケット
        mSoundPacketArray.at(index).Init(WaveFile->GetBufferPtr(), 0, WaveFile->GetDataSize() / SOUND_PACKET_NUM);

        ++index;
        while (index < SOUND_PACKET_NUM - 1) {
            mSoundPacketArray.at(index).Init(WaveFile->GetBufferPtr(),
                                            (WaveFile->GetDataSize() / SOUND_PACKET_NUM  * index),
                                            (WaveFile->GetDataSize() / SOUND_PACKET_NUM) * (index + 1));

            ++index;
        }

        // 最後のパケット
        mSoundPacketArray.at(index).Init(WaveFile->GetBufferPtr(),
                                         WaveFile->GetDataSize() / SOUND_PACKET_NUM  * index,
                                         WaveFile->GetDataSize());
    } catch (const std::out_of_range&) {
        return false; // 範囲外アクセス
    }

    return true;
}
