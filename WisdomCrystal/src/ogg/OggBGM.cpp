// OggBGM.cpp

#include "OggBGM.h"


namespace Ogg {

OggBGM::OggBGM() : mSourceVoice(nullptr)
{
    // empty
}


OggBGM::~OggBGM() {
    // empty
}


bool OggBGM::Init(SoundDevice* soundDevice, const std::string& filePath) {

    // BGM データの読み込み
    if (mOggFile.Init(filePath) == false) {
        MessageBox(nullptr, TEXT("OggBGM: Can not read OggFile."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice の作成
    mSourceVoice = soundDevice->CreateSourceVoice(mOggFile.GetWaveFormatEx(), this);
    if (mSourceVoice == nullptr) {
        MessageBox(nullptr, TEXT("OggBGM: Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false;
    }

    mOggFile.Update();
    UpdateBGM();
    return true;
}


void OggBGM::Start() {
    mSourceVoice->Start();
}


void OggBGM::Stop() {
    mSourceVoice->Stop();
}


void OggBGM::UpdateBGM() {
    XAUDIO2_VOICE_STATE state;
    mSourceVoice->GetState(&state);
    if (state.BuffersQueued >= 2) {
        return;
    }

    mOggFile.Update();
    static auto i = 0;

    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = mOggFile.GetBufferPtr()->at(i).size();
    buffer.pAudioData = reinterpret_cast<unsigned char*>(&mOggFile.GetBufferPtr()->at(i).front());
    buffer.Flags = 0;

    mSourceVoice->SubmitSourceBuffer(&buffer);

    ++i;
    if (i == 21) {i =0;}
}


void OggBGM::SetVolume(const float volume) {
    mSourceVoice->SetVolume(volume);
}

} // namespace Ogg
