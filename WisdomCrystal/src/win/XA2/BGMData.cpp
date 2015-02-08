// BGMData.cpp

// Includes
#include "BGMData.h"


BGMData::BGMData(const unsigned int packetNum) : SOUND_PACKET_NUM(packetNum),
                                                 mNextPacketIndex(0),
                                                 mSoundPacketArray(SOUND_PACKET_NUM),
                                                 mSourceVoiceForBGM(nullptr)
{
    // empty
}


BGMData::~BGMData() {
    // empty
}


bool BGMData::Init(SoundDevice* soundDevice, LPTSTR waveFilePath) {
    WaveData waveData;

    // BGM データの読み込み
    if (waveData.Init(waveFilePath) == false) {
        MessageBox(nullptr, TEXT("BGMData: Can not read waveData."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice の作成
    mSourceVoiceForBGM = soundDevice->CreateSourceVoice(waveData.GetWaveFormatEx());
    if (mSourceVoiceForBGM == nullptr) {
        MessageBox(nullptr, TEXT("BGMData: Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // BGM データを Sound Packet に分割
    divideSoundPacket(&waveData);

    mSoundPacketArray.at(0).AddSoundPacket(mSourceVoiceForBGM);
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


void BGMData::SetBGMVolume(const float volume) {
    mSourceVoiceForBGM->SetVolume(volume);
}


void BGMData::divideSoundPacket(WaveData* waveData) {

    auto it = mSoundPacketArray.begin();

    it->Init(waveData->GetDataBufferPtr(), 0, waveData->GetDataSize() / SOUND_PACKET_NUM);
    ++it;

    while (it != mSoundPacketArray.end()) {
        int index = std::distance(mSoundPacketArray.begin(), it);
        it->Init(waveData->GetDataBufferPtr(),
                (waveData->GetDataSize() / SOUND_PACKET_NUM  * index),
                (waveData->GetDataSize() / SOUND_PACKET_NUM) * (index + 1));
        ++it;
    }
}
