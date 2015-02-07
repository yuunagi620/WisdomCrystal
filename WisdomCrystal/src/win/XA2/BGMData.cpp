// BGMData.cpp

// Includes
#include "BGMData.h"


BGMData::BGMData(const unsigned int packetNum) : mWaveData(),
                                                 mSoundPacket(packetNum),
                                                 mNextPacket(0),
                                                 mSourceVoiceForBGM(nullptr) {

    // empty
}


BGMData::~BGMData() {
    Cleanup();
}


bool BGMData::Init(SoundDevice* soundDevice, LPTSTR waveFilePath) {

    if (mWaveData.Init(waveFilePath) == false) {
        MessageBox(nullptr, TEXT("Can not read waveData."), TEXT("ERROR"), MB_OK);
        return false; // BGM データの読み込みに失敗
    }

    if (divideWaveData() == false) {
        return false;
    }

    if (soundDevice->CreateSourceVoice(&mSourceVoiceForBGM, mWaveData.GetWaveFormatExPtr()) == false) {
        MessageBox(nullptr, TEXT("Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false; // SourceVoice の作成に失敗
    }
    
    return true;
}


void BGMData::Cleanup() {
    if (mSourceVoiceForBGM != nullptr) {
        mSourceVoiceForBGM->Stop();
        mSourceVoiceForBGM->DestroyVoice();
        mSourceVoiceForBGM = nullptr;
    }
}


void BGMData::StartBGM() {
    mSourceVoiceForBGM->Start();
}


void BGMData::UpdateBGM() {
    XAUDIO2_VOICE_STATE state;
    mSourceVoiceForBGM->GetState(&state);

    if (state.BuffersQueued >= 2) {
        return;
    }

    mSoundPacket.at(mNextPacket).AddSoundPacket(mSourceVoiceForBGM);
    ++mNextPacket;
    mNextPacket %= 2; // 最大値を超えたら先頭へ
}


void BGMData::SetBGMVolume(const float volume) {
    mSourceVoiceForBGM->SetVolume(volume);
}



bool BGMData::divideWaveData() {
    if (mSoundPacket.at(0).Init(mWaveData.GetDataBufferPtr(), 0, mWaveData.GetDataSize() / 2) == false) {
        return false;
    }
    if (mSoundPacket.at(1).Init(mWaveData.GetDataBufferPtr(), mWaveData.GetDataSize() / 2, mWaveData.GetDataSize()) == false) {

        return false;
    }

    //ResetSoundPacket();
    mSoundPacket.at(0).AddSoundPacket(mSourceVoiceForBGM);


    return true;
}