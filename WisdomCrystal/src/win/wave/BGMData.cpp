// BGMData.cpp

#include "BGMData.h"


BGMData::BGMData() : mWaveFile(), mSourceVoice(nullptr) {
    // empty
}


BGMData::~BGMData() {
    // empty
}


bool BGMData::Init(SoundDevice* soundDevice, const std::string& filePath) {

    // BGM ƒf[ƒ^‚Ì“Ç‚Ýž‚Ý
    if (mWaveFile.Load(filePath) == false) {
        MessageBox(nullptr, TEXT("BGMData: WaveFile ‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice ‚Ìì¬
    mSourceVoice = soundDevice->CreateSourceVoice(mWaveFile.GetWaveFormatEx(), nullptr);
    if (mSourceVoice == nullptr) {
        MessageBox(nullptr, TEXT("BGMData: SourceVoice ‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½"), TEXT("ERROR"), MB_OK);
        return false;
    }

    return true;
}


void BGMData::Start() {
    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = mWaveFile.GetDataSize();
    buffer.pAudioData = &(mWaveFile.GetBufferPtr()->front());
    buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
    buffer.Flags = XAUDIO2_END_OF_STREAM;
    mSourceVoice->SubmitSourceBuffer(&buffer);
    mSourceVoice->Start();
}


void BGMData::Stop() {
    mSourceVoice->Stop();
}


void BGMData::SetVolume(const float volume) {
    mSourceVoice->SetVolume(volume);
}
