// BGMData.cpp

#include "BGMData.h"


BGMData::BGMData() : SOUND_PACKET_NUM(2),
                     mNextPacketIndex(0),
                     mSoundPacketArray(SOUND_PACKET_NUM),
                     mSourceVoice(nullptr)
{
    // empty
}


BGMData::~BGMData() {
    // empty
}


bool BGMData::Init(SoundDevice* soundDevice, const std::string& filePath) {
    WaveFile WaveFile;

    // BGM �f�[�^�̓ǂݍ���
    if (WaveFile.Load(filePath) == false) {
        MessageBox(nullptr, TEXT("BGMData: Can not read WaveFile."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice �̍쐬
    mSourceVoice = soundDevice->CreateSourceVoice(WaveFile.GetWaveFormatEx(), nullptr);
    if (mSourceVoice == nullptr) {
        MessageBox(nullptr, TEXT("BGMData: Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // BGM �f�[�^�� Sound Packet �ɕ���
    if (divideSoundPacket(&WaveFile) == false) {
        MessageBox(nullptr, TEXT("BGMData: Can not divide sound packet."), TEXT("ERROR"), MB_OK);
        return false;
    }

    mSoundPacketArray.front().AddSoundPacket(mSourceVoice);
    mNextPacketIndex = 1;
    return true;
}


void BGMData::Start() {
    mSourceVoice->Start();
}


void BGMData::Stop() {
    mSourceVoice->Stop();
}


void BGMData::UpdateBGM() {
    XAUDIO2_VOICE_STATE state;
    mSourceVoice->GetState(&state);
    if (state.BuffersQueued >= SOUND_PACKET_NUM) {
        return;
    }
    mSoundPacketArray.at(mNextPacketIndex).AddSoundPacket(mSourceVoice);
    ++mNextPacketIndex;
    mNextPacketIndex %= SOUND_PACKET_NUM; // �ő�l�𒴂�����ŏ��ɖ߂�
}


void BGMData::SetVolume(const float volume) {
    mSourceVoice->SetVolume(volume);
}


bool BGMData::divideSoundPacket(WaveFile* WaveFile) {

    try {
        unsigned int index = 0;

        // �ŏ��̃p�P�b�g
        mSoundPacketArray.at(index).Init(WaveFile->GetBufferPtr(), 0, WaveFile->GetDataSize() / SOUND_PACKET_NUM);

        ++index;
        while (index < SOUND_PACKET_NUM - 1) {
            mSoundPacketArray.at(index).Init(WaveFile->GetBufferPtr(),
                                            (WaveFile->GetDataSize() / SOUND_PACKET_NUM  * index),
                                            (WaveFile->GetDataSize() / SOUND_PACKET_NUM) * (index + 1));

            ++index;
        }

        // �Ō�̃p�P�b�g
        mSoundPacketArray.at(index).Init(WaveFile->GetBufferPtr(),
                                         WaveFile->GetDataSize() / SOUND_PACKET_NUM  * index,
                                         WaveFile->GetDataSize());
    } catch (const std::out_of_range&) {
        return false; // �͈͊O�A�N�Z�X
    }

    return true;
}
