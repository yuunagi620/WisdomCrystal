// BGMData.cpp

// Includes
#include "BGMData.h"


BGMData::BGMData() : mWaveData(), mSourceVoiceForBGM(nullptr) {
    // empty
}


BGMData::~BGMData() {
    // empty
}


bool BGMData::Init(SoundDevice* soundDevice, LPTSTR waveFilePath) {

    // BGM �f�[�^�̓ǂݍ���
    if (mWaveData.Init(waveFilePath) == false) {
        MessageBox(nullptr, TEXT("BGMData: Can not read waveData."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice �̍쐬
    mSourceVoiceForBGM = soundDevice->CreateSourceVoice(mWaveData.GetWaveFormatEx());
    if (mSourceVoiceForBGM == nullptr) {
        MessageBox(nullptr, TEXT("BGMData: Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice �̊��蓖��
    if (ResetSourceVoice() == false) {
        MessageBox(nullptr, TEXT("BGMData: Can not set source voice."), TEXT("ERROR"), MB_OK);
        return false;
    }
    
    return true;
}


void BGMData::Start() {
    mSourceVoiceForBGM->Start();
}


void BGMData::Stop() {
    mSourceVoiceForBGM->Stop();
}


void BGMData::SetBGMVolume(const float volume) {
    mSourceVoiceForBGM->SetVolume(volume);
}


bool BGMData::ResetSourceVoice() {
    const XAUDIO2_BUFFER buffer = {
        XAUDIO2_END_OF_STREAM,
	    mWaveData.GetDataSize(),
	    &(mWaveData.GetDataBufferPtr()->front()),
        0,
        0,
        0,
        0,
        XAUDIO2_LOOP_INFINITE,
        nullptr
    };
    
    HRESULT hr = mSourceVoiceForBGM->SubmitSourceBuffer(&buffer);
    if (FAILED(hr)) {
        return false;
    }

    return true;
}
