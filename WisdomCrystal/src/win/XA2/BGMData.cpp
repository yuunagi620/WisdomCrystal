// BGMData.cpp

// Includes
#include "BGMData.h"


BGMData::BGMData() : mNextPacketIndex(0),
                     mSoundPacketArray(2),
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

    mSoundPacketArray.at(0).Init(waveData.GetDataBufferPtr(), 0, waveData.GetDataSize() / 2);
    mSoundPacketArray.at(1).Init(waveData.GetDataBufferPtr(), waveData.GetDataSize() / 2, waveData.GetDataSize());

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
    if (state.BuffersQueued >= 2) {
        return;
    }
    mSoundPacketArray.at(mNextPacketIndex).AddSoundPacket(mSourceVoiceForBGM);
    ++mNextPacketIndex;
    mNextPacketIndex %= 2; // 最大値を超えたら最初に戻る
}


void BGMData::SetBGMVolume(const float volume) {
    mSourceVoiceForBGM->SetVolume(volume);
}
