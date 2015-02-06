// SoundPacket.cpp

#include "SoundPacket.h"
#include <memory>
#include <iterator>


SoundPacket::SoundPacket() : mBuffer(), mDataSize(-1) {
    // empty
}


SoundPacket::~SoundPacket() {
    // empty
}


// buffer�Ƃ��̑傫�����󂯎�����Ƃ��̏�����
bool SoundPacket::Init(std::vector<BYTE> *srcBuffer, const long dataSize) {

    // mBuffer �� dataSize �o�C�g�m��
    mBuffer.resize(srcBuffer->size());

    std::copy(srcBuffer->begin(), srcBuffer->end(), mBuffer.begin());

    // �󂯎���� srcBuffer ����mBuffer�փR�s�[
    mDataSize = dataSize;
    //memcpy_s(&mBuffer.front(), mDataSize, srcBuffer, dataSize);

    return true;
}


// WaveData �݂̂��󂯎�����Ƃ��̏�����
bool SoundPacket::Init(WaveData* waveData) {
    return Init(waveData->GetDataBuffer(), waveData->GetDataSize());
}


// �{�C�X�L���[�ɐV�����I�[�f�B�I �o�b�t�@�[��ǉ�
void SoundPacket::AddSoundPacket(IXAudio2SourceVoice *targetSourceVoice,
                                 SoundPacket *soundPacket) {

    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = soundPacket->GetDataSize();
    buffer.pAudioData = soundPacket->GetBuffer();
    buffer.Flags = 0;

    targetSourceVoice->SubmitSourceBuffer(&buffer);
}


// ���ݍĐ����Ă��鉹�����Z�b�g���ă{�C�X�L���[�Ƀo�b�t�@�[��ǉ�
void SoundPacket::ResetSourceVoice(IXAudio2SourceVoice *targetSourceVoice,
                                   SoundPacket* soundPacket) {

    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = soundPacket->GetDataSize();
    buffer.pAudioData = soundPacket->GetBuffer();
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    HRESULT hr = targetSourceVoice->SubmitSourceBuffer(&buffer);
}
