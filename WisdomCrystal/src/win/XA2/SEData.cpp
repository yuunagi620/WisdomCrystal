// SEData.cpp

// Includes
#include "SEData.h"


SEData::SEData() : mWaveData(), mSourceVoiceForSE(nullptr) {
    // empty
}


SEData::~SEData() {
    // empty
}


bool SEData::Init(SoundDevice* soundDevice, LPTSTR waveFilePath) {
    if (mWaveData.Init(waveFilePath) == false) {
        MessageBox(nullptr, TEXT("SEData: Can not read waveData."), TEXT("ERROR"), MB_OK);
        return false; // SE データの読み込みに失敗
    }

    mSourceVoiceForSE = soundDevice->CreateSourceVoice(mWaveData.GetWaveFormatEx());
    if (mSourceVoiceForSE == nullptr) {
        MessageBox(nullptr, TEXT("SEData: Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false; // SourceVoice の作成に失敗
    }

    return true;
}


void SEData::StartSE() {
    mSourceVoiceForSE->Stop();
    mSourceVoiceForSE->FlushSourceBuffers();
    resetSourceVoice();
    mSourceVoiceForSE->Start();
}


void SEData::SetSEVolume(const float volume) {
    mSourceVoiceForSE->SetVolume(volume);
}


void SEData::resetSourceVoice() {
    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = mWaveData.GetDataSize();
    buffer.pAudioData = &(mWaveData.GetDataBufferPtr()->front());
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    mSourceVoiceForSE->SubmitSourceBuffer(&buffer);
}
