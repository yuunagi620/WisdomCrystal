// OggBGM.cpp

#include "OggBGM.h"


namespace Ogg {

OggBGM::OggBGM() : mOggFile(), mSourceVoice(nullptr), mBufferIndex(0) {
    // empty
}


OggBGM::~OggBGM() {
    // empty
}


bool OggBGM::Init(SoundDevice* soundDevice, const std::string& filePath) {

    // BGM �f�[�^�̓ǂݍ���
    if (mOggFile.Init(filePath) == false) {
        MessageBox(nullptr, TEXT("OggBGM: OggFile�̓ǂݍ��݂Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice �̍쐬
    mSourceVoice = soundDevice->CreateSourceVoice(mOggFile.GetWaveFormatEx(), this);
    if (mSourceVoice == nullptr) {
        MessageBox(nullptr, TEXT("OggBGM: SourceVoice�̍쐬�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK);
        return false;
    }

    mOggFile.Load(); // �\�߁C�]����1�����ǂݍ���ł���
    Update();
    return true;
}


void OggBGM::Start() {
    mSourceVoice->Start();
}


void OggBGM::Stop() {
    mSourceVoice->Stop();
}


bool OggBGM::Update() {
    mOggFile.Load();

    std::vector<char>* currentBuffer;

    try {
        currentBuffer = &mOggFile.GetBufferPtr()->at(mBufferIndex);
    } catch (const std::out_of_range&) {
        return false; // �͈͊O�A�N�Z�X
    }

    // �{�C�X�L���[�ɐV�����o�b�t�@�[��ǉ�
    XAUDIO2_BUFFER xa2Buffer = {0};
    xa2Buffer.AudioBytes = currentBuffer->size();
    xa2Buffer.pAudioData = reinterpret_cast<unsigned char*>(&currentBuffer->front());
    xa2Buffer.Flags = 0;
    mSourceVoice->SubmitSourceBuffer(&xa2Buffer);

    // 1�C���f�b�N�X��i�߂čő�l�𒴂��Ă�����ŏ��ɖ߂�
    ++mBufferIndex %= mOggFile.GetBufferPtr()->size();

    return true;
}


void OggBGM::SetVolume(float volume) {
    mSourceVoice->SetVolume(volume);
}

} // namespace Ogg
