// BGMData.cpp

#include "BGMData.h"


BGMData::BGMData() : SOUND_PACKET_NUM(2),
                     mNextPacketIndex(0),
                     mSoundPacketArray(SOUND_PACKET_NUM),
                     mSourceVoiceForBGM(nullptr)
{
    // empty
}


BGMData::~BGMData() {
    // empty
}


bool BGMData::Init(SoundDevice* soundDevice, LPTSTR waveFilePath) {
    WaveData waveData;

    // BGM �f�[�^�̓ǂݍ���
    if (waveData.Init(waveFilePath) == false) {
        MessageBox(nullptr, TEXT("BGMData: Can not read waveData."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // SourceVoice �̍쐬
    mSourceVoiceForBGM = soundDevice->CreateSourceVoice(waveData.GetWaveFormatEx());
    if (mSourceVoiceForBGM == nullptr) {
        MessageBox(nullptr, TEXT("BGMData: Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // BGM �f�[�^�� Sound Packet �ɕ���
    if (divideSoundPacket(&waveData) == false) {
        MessageBox(nullptr, TEXT("BGMData: Can not divide sound packet."), TEXT("ERROR"), MB_OK);
        return false;
    }

    mSoundPacketArray.front().AddSoundPacket(mSourceVoiceForBGM);
    mNextPacketIndex = 1;
    return true;
}


void BGMData::Start() {
    mSourceVoiceForBGM->Start();
}


void BGMData::Stop() {
    mSourceVoiceForBGM->Stop();
}


void BGMData::UpdateBGM() {
    XAUDIO2_VOICE_STATE state;
    mSourceVoiceForBGM->GetState(&state);
    if (state.BuffersQueued >= SOUND_PACKET_NUM) {
        return;
    }
    mSoundPacketArray.at(mNextPacketIndex).AddSoundPacket(mSourceVoiceForBGM);
    ++mNextPacketIndex;
    mNextPacketIndex %= SOUND_PACKET_NUM; // �ő�l�𒴂�����ŏ��ɖ߂�
}


void BGMData::SetBGMVolume(const float volume) {
    mSourceVoiceForBGM->SetVolume(volume);
}


bool BGMData::divideSoundPacket(WaveData* waveData) {

    try {
        unsigned int index = 0;

        // �ŏ��̃p�P�b�g
        mSoundPacketArray.at(index).Init(waveData->GetDataBufferPtr(), 0, waveData->GetDataSize() / SOUND_PACKET_NUM);

        ++index;
        while (index < SOUND_PACKET_NUM - 1) {
            mSoundPacketArray.at(index).Init(waveData->GetDataBufferPtr(),
                                            (waveData->GetDataSize() / SOUND_PACKET_NUM  * index),
                                            (waveData->GetDataSize() / SOUND_PACKET_NUM) * (index + 1));

            ++index;
        }

        // �Ō�̃p�P�b�g
        mSoundPacketArray.at(index).Init(waveData->GetDataBufferPtr(),
                                         waveData->GetDataSize() / SOUND_PACKET_NUM  * index,
                                         waveData->GetDataSize());
    } catch (const std::out_of_range&) {
        return false; // �͈͊O�A�N�Z�X
    }

    return true;
}
