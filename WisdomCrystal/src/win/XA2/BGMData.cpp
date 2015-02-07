// BGMData.cpp

// Includes
#include "BGMData.h"


BGMData::BGMData() : mWaveData(), mSourceVoiceForBGM(nullptr) {
    // empty
}


BGMData::~BGMData() {
    Cleanup();
}


bool BGMData::Init(SoundDevice* soundDevice, LPTSTR waveFilePath) {
    if (mWaveData.Init(waveFilePath) == false) {
        MessageBox(nullptr, TEXT("Can not read waveData."), TEXT("ERROR"), MB_OK);
        return false; // BGM ƒf[ƒ^‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s
    }

    if (soundDevice->CreateSourceVoice(&mSourceVoiceForBGM, mWaveData.GetWaveFormatExPtr()) == false) {
        MessageBox(nullptr, TEXT("Can not create source voice."), TEXT("ERROR"), MB_OK);
        return false; // SourceVoice ‚Ìì¬‚ÉŽ¸”s
    }

    if (ResetSourceVoice() == false) {
        MessageBox(nullptr, TEXT("Can not set source voice."), TEXT("ERROR"), MB_OK);
        return false; // SourceVoice ‚ÌŠ„‚è“–‚Ä‚ÉŽ¸”s
    }
    
    return true;
}


void BGMData::Cleanup() {
    // empty
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
