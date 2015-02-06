// BGMData.cpp

// Includes
#include "BGMData.h"


BGMData::BGMData(const unsigned int packetNum) : mWaveData(),
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
    ResetSourceVoice();
}


void BGMData::SetBGMVolume(const float volume) {
    mSourceVoiceForBGM->SetVolume(volume);
}


// 現在再生している音をリセットしてボイスキューにバッファーを追加
void BGMData::ResetSourceVoice() {
    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = mWaveData.GetDataSize();
    buffer.pAudioData = mWaveData.GetDataBufferPtr();
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    mSourceVoiceForBGM->SubmitSourceBuffer(&buffer);
}


void BGMData::AddSoundPacket() {
    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = mWaveData.GetDataSize();
    buffer.pAudioData = mWaveData.GetDataBufferPtr();
    buffer.Flags = 0;

    mSourceVoiceForBGM->SubmitSourceBuffer(&buffer);
}