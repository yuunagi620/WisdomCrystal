// SEData.cpp

#include "SEData.h"


SEData::SEData() : mWaveFile(), mSourceVoiceForSE(nullptr) {
    // empty
}


SEData::~SEData() {
    // empty
}


bool SEData::Init(SoundDevice* soundDevice, const std::string& filePath) {
    if (mWaveFile.Load(filePath) == false) {
        MessageBox(nullptr, TEXT("SEData: Can not read WaveFile."), TEXT("ERROR"), MB_OK);
        return false; // SE ƒf[ƒ^‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s
    }

    mSourceVoiceForSE = soundDevice->CreateSourceVoice(mWaveFile.GetWaveFormatEx());
    if (mSourceVoiceForSE == nullptr) {
        MessageBox(nullptr, TEXT("SEData: Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false; // SourceVoice ‚Ìì¬‚ÉŽ¸”s
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
    buffer.AudioBytes = mWaveFile.GetDataSize();
    buffer.pAudioData = &(mWaveFile.GetDataBufferPtr()->front());
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    mSourceVoiceForSE->SubmitSourceBuffer(&buffer);
}
