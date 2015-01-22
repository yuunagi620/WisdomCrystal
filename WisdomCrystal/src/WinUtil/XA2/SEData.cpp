// SEData.cpp

// Includes
#include "SEData.h"


SEData::SEData() : mSourceVoiceForSE(nullptr), mSESoundPacket() {
    // empty
}


SEData::~SEData() {
    Cleanup();
}


bool SEData::Init(SoundDevice* soundDevice, TCHAR *waveFilePath) {
    WaveData waveData;

    if (waveData.Init(waveFilePath) == false) {
        MessageBox(nullptr, TEXT("Can not read waveData."), TEXT("ERROR"), MB_OK);
        return false; // SE ƒf[ƒ^‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s
    }

    mSESoundPacket.Init(waveData);
    if (soundDevice->CreateSourceVoice(&mSourceVoiceForSE, waveData.GetWaveFormatExPtr()) == false) {
        MessageBox(nullptr, TEXT("Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false; // SourceVoice ‚Ìì¬‚ÉŽ¸”s
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
    SoundPacket::ResetSourceVoice(mSourceVoiceForSE, mSESoundPacket);
    mSourceVoiceForSE->Start();
}


void SEData::SetSEVolume(const float volume) {
    mSourceVoiceForSE->SetVolume(volume);
}