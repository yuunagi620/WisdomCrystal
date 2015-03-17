// SEData.cpp

#include "SEData.h"


SEData::SEData() : mWaveFile(), mSourceVoice(nullptr) {
    // empty
}


SEData::~SEData() {
    // empty
}


bool SEData::Init(SoundDevice* soundDevice, const std::string& filePath) {

    // SE �f�[�^�̓ǂݍ���
    if (mWaveFile.Load(filePath) == false) {
        MessageBox(nullptr, TEXT("SEData: WaveFile �̓ǂݍ��݂Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice �̍쐬
    mSourceVoice = soundDevice->CreateSourceVoice(mWaveFile.GetWaveFormatEx(), nullptr);
    if (mSourceVoice == nullptr) {
        MessageBox(nullptr, TEXT("SEData: SourceVoice �̍쐬�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
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
    buffer.pAudioData = &(mWaveFile.GetBufferPtr()->front());
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    mSourceVoice->SubmitSourceBuffer(&buffer);
}
