// OggSE.cpp

#include "OggSE.h"


namespace Ogg {

OggSE::OggSE() : mOggFile(),
                 mSourceVoice(nullptr)
{
    // empty
}


OggSE::~OggSE() {
    // empty
}


bool OggSE::Init(SoundDevice* soundDevice, const std::string& filePath) {

    // SE ƒf[ƒ^‚Ì“Ç‚Ýž‚Ý
    if (mOggFile.Init(filePath) == false) {
        MessageBox(nullptr, TEXT("OggSE: Can not read OggFile."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice ‚Ìì¬
    mSourceVoice = soundDevice->CreateSourceVoice(mOggFile.GetWaveFormatEx(), nullptr);
    if (mSourceVoice == nullptr) {
        MessageBox(nullptr, TEXT("OggSE: Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false;
    }

    mOggFile.Load();
    return true;
}


void OggSE::Start() {
    mSourceVoice->Stop();
    mSourceVoice->FlushSourceBuffers();
    resetSourceVoice();
    mSourceVoice->Start();
}


void OggSE::Stop() {
    mSourceVoice->Stop();
}


void OggSE::SetVolume(float volume) {
    mSourceVoice->SetVolume(volume);
}


void OggSE::resetSourceVoice() {
    XAUDIO2_BUFFER xa2Buffer = {0};
    xa2Buffer.AudioBytes = mOggFile.GetBufferPtr()->front().size();
    xa2Buffer.pAudioData = reinterpret_cast<unsigned char*>(&mOggFile.GetBufferPtr()->front().front());
    xa2Buffer.Flags = XAUDIO2_END_OF_STREAM;
    mSourceVoice->SubmitSourceBuffer(&xa2Buffer);
}


} // namespace Ogg
