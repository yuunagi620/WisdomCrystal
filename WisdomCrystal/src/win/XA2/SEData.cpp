// SEData.cpp

// Includes
#include "SEData.h"


SEData::SEData() : mWaveData(), mSourceVoiceForSE(nullptr) {
    // empty
}


SEData::~SEData() {
    Cleanup();
}


bool SEData::Init(SoundDevice* soundDevice, LPTSTR waveFilePath) {
    if (mWaveData.Init(waveFilePath) == false) {
        MessageBox(nullptr, TEXT("SEData: Can not read waveData."), TEXT("ERROR"), MB_OK);
        return false; // SE データの読み込みに失敗
    }

    if (soundDevice->CreateSourceVoice(&mSourceVoiceForSE, mWaveData.GetWaveFormatExPtr()) == false) {
        MessageBox(nullptr, TEXT("SEData: Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false; // SourceVoice の作成に失敗
    }

    return true;
}


void SEData::Cleanup() {
    if (mSourceVoiceForSE != nullptr) {
        mSourceVoiceForSE->Stop();
        mSourceVoiceForSE->DestroyVoice();
        mSourceVoiceForSE = nullptr;
    }
}


void SEData::StartSE() {
    mSourceVoiceForSE->Stop();
    mSourceVoiceForSE->FlushSourceBuffers();
    ResetSourceVoice();
    mSourceVoiceForSE->Start();
}


void SEData::SetSEVolume(const float volume) {
    mSourceVoiceForSE->SetVolume(volume);
}


void SEData::ResetSourceVoice() {
    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = mWaveData.GetDataSize();
    buffer.pAudioData = mWaveData.GetDataBufferPtr();
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    HRESULT hr = mSourceVoiceForSE->SubmitSourceBuffer(&buffer);
}
