// BGMData.cpp

// Includes
#include "BGMData.h"


BGMData::BGMData(const unsigned int packetNum) : mWaveData(),
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
        return false; // BGM ƒf[ƒ^‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s
    }

    if (soundDevice->CreateSourceVoice(&mSourceVoiceForBGM, mWaveData.GetWaveFormatExPtr()) == false) {
        MessageBox(nullptr, TEXT("Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false; // SourceVoice ‚Ìì¬‚ÉŽ¸”s
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
        //XAUDIO2_VOICE_STATE state;
        //mSourceVoiceForBGM->GetState(&state);

        //if (state.BuffersQueued >= 2) {
        //    return;
        //}

        //mSoundPacket.at(mNextPacket).AddSoundPacket(mSourceVoiceForBGM);
        //++mNextPacket;
        //mNextPacket %= 2; // Å‘å’l‚ð’´‚¦‚½‚çæ“ª‚Ö
}


void BGMData::SetBGMVolume(const float volume) {
    mSourceVoiceForBGM->SetVolume(volume);
}


void BGMData::ResetSourceVoice() {
    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = mWaveData.GetDataSize();
    buffer.pAudioData = &(mWaveData.GetDataBufferPtr()->front());
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    mSourceVoiceForBGM->SubmitSourceBuffer(&buffer);
}
