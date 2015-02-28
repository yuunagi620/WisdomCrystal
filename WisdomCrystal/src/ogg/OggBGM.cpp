// OggBGM.cpp

#include "OggBGM.h"


namespace Ogg {

OggBGM::OggBGM() : mOggFile(),
                   mSourceVoice(nullptr),
                   mBufferIndex(0)
{
    // empty
}


OggBGM::~OggBGM() {
    // empty
}


bool OggBGM::Init(SoundDevice* soundDevice, const std::string& filePath) {

    // BGM �f�[�^�̓ǂݍ���
    if (mOggFile.Init(filePath) == false) {
        MessageBox(nullptr, TEXT("OggBGM: Can not read OggFile."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice �̍쐬
    mSourceVoice = soundDevice->CreateSourceVoice(mOggFile.GetWaveFormatEx());
    if (mSourceVoice == nullptr) {
        MessageBox(nullptr, TEXT("OggBGM: Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false;
    }

    mOggFile.Load(1000000);
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
        return; // �Đ��L���[��2�ȏ�̃o�b�t�@���������ꍇ�������X�V���Ȃ�
    }

    mOggFile.Load(1000000);

    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = mOggFile.GetBufferPtr()->at(mBufferIndex).size();
    buffer.pAudioData = reinterpret_cast<unsigned char*>(&mOggFile.GetBufferPtr()->at(mBufferIndex).front());
    buffer.Flags = 0;
    mSourceVoice->SubmitSourceBuffer(&buffer);

    ++mBufferIndex %= mOggFile.GetBufferPtr()->size();
}


void OggBGM::SetVolume(const float volume) {
    mSourceVoice->SetVolume(volume);
}

} // namespace Ogg
