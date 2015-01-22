// BGMData.cpp

// Includes
#include "BGMData.h"


BGMData::BGMData(const unsigned int packetNum) : SOUND_PACKET_NUM(packetNum),
                                                 mSourceVoiceForBGM(nullptr),
                                                 mBGMSoundPacket(SOUND_PACKET_NUM),
                                                 mNextBGMPacket(-1) {

    // empty
}


BGMData::~BGMData() {
    Cleanup();
}


bool BGMData::Init(SoundDevice* soundDevice, TCHAR *waveFilePath) {
    WaveData waveData;

    if (waveData.Init(waveFilePath) == false) {
        MessageBox(nullptr, TEXT("Can not read waveData."), TEXT("ERROR"), MB_OK);
        return false; // BGM �f�[�^�̓ǂݍ��݂Ɏ��s
    }

    if (soundDevice->CreateSourceVoice(&mSourceVoiceForBGM, waveData.GetWaveFormatExPtr()) == false) {
        MessageBox(nullptr, TEXT("Can not create sourceVoice."), TEXT("ERROR"), MB_OK);
        return false; // SourceVoice �̍쐬�Ɏ��s
    }

    divideWaveData(waveData);

    SoundPacket::AddSoundPacket(mSourceVoiceForBGM, mBGMSoundPacket[0]);
    mNextBGMPacket = 1;
    
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

    XAUDIO2_VOICE_STATE state;
    mSourceVoiceForBGM->GetState(&state);

    if (state.BuffersQueued >= SOUND_PACKET_NUM) {
        return;
    }

    SoundPacket::AddSoundPacket(mSourceVoiceForBGM, mBGMSoundPacket[mNextBGMPacket]);
    ++mNextBGMPacket;
    mNextBGMPacket %= SOUND_PACKET_NUM; // �ő�l�𒴂�����擪��
}


void BGMData::SetBGMVolume(const float volume) {
    mSourceVoiceForBGM->SetVolume(volume);
}


void BGMData::divideWaveData(const WaveData& waveData) {

    long dividedDataSize = 0; // ���łɕ������ꂽ�f�[�^�T�C�Y
    auto it = mBGMSoundPacket.begin(); // iterator

    // �Ō��1���܂ŕ���
    while (it != (mBGMSoundPacket.end() - 1)) {

        int index = std::distance(mBGMSoundPacket.begin(), it);
        
        it->Init(waveData.GetDataBuffer() + dividedDataSize,
                (waveData.GetDataSize()   - dividedDataSize) / (SOUND_PACKET_NUM - index));

        dividedDataSize += it->GetDataSize();
        ++it;
    }

    // �Ō��1�͊���Z�̒[�����l�����ăf�[�^�T�C�Y�����߂�
    it->Init(waveData.GetDataBuffer() + dividedDataSize,
             waveData.GetDataSize()   - dividedDataSize);
}
