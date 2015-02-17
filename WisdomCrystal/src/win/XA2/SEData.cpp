// SEData.cpp

#include "SEData.h"


SEData::SEData() : mWaveFile(), mSourceVoice(nullptr) {
    // empty
}


SEData::~SEData() {
    // empty
}


bool SEData::Init(SoundDevice* soundDevice, const std::string& filePath) {

    // SE ƒf[ƒ^‚Ì“Ç‚Ýž‚Ý
    if (mWaveFile.Load(filePath) == false) {
        MessageBox(nullptr, TEXT("SEData: Can not read WaveFile."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice ‚Ìì¬
    mSourceVoice = soundDevice->CreateSourceVoice(mWaveFile.GetWaveFormatEx());
    if (mSourceVoice == nullptr) {
        MessageBox(nullptr, TEXT("SEData: Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false;
    }

    return true;
}


void SEData::Start() {
    mSourceVoice->Stop();
    mSourceVoice->FlushSourceBuffers();
    resetSourceVoice();
    mSourceVoice->Start();
}


void SEData::SetVolume(const float volume) {
    mSourceVoice->SetVolume(volume);
}


void SEData::resetSourceVoice() {
    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = mWaveFile.GetDataSize();
    buffer.pAudioData = &(mWaveFile.GetDataBufferPtr()->front());
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    mSourceVoice->SubmitSourceBuffer(&buffer);
}
