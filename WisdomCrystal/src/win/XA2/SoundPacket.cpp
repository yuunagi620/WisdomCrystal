// SoundPacket.cpp

#include "SoundPacket.h"
#include <memory>


SoundPacket::SoundPacket() : mBuffer(nullptr), mDataSize(-1) {
    // empty
}


SoundPacket::~SoundPacket() {
    mBuffer.reset();
}


// buffer�Ƃ��̑傫�����󂯎�����Ƃ��̏�����
bool SoundPacket::Init(const BYTE *srcBuffer, const long dataSize) {

    // mBuffer �� dataSize �o�C�g�m��
    mBuffer.reset(new BYTE[dataSize], std::default_delete<BYTE[]>());

    // �󂯎���� srcBuffer ����mBuffer�փR�s�[
    mDataSize = dataSize;
    memcpy_s(mBuffer.get(), mDataSize, srcBuffer, dataSize);

    return true;
}


// WaveData �݂̂��󂯎�����Ƃ��̏�����
bool SoundPacket::Init(const WaveData& waveData) {
    return Init(waveData.GetDataBuffer(), waveData.GetDataSize());
}


// �{�C�X�L���[�ɐV�����I�[�f�B�I �o�b�t�@�[��ǉ�
void SoundPacket::AddSoundPacket(IXAudio2SourceVoice *targetSourceVoice,
                                 const SoundPacket& soundPacket) {

    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = soundPacket.GetDataSize();
    buffer.pAudioData = soundPacket.GetBuffer();
    buffer.Flags = 0;

    targetSourceVoice->SubmitSourceBuffer(&buffer);
}


// ���ݍĐ����Ă��鉹�����Z�b�g���ă{�C�X�L���[�Ƀo�b�t�@�[��ǉ�
void SoundPacket::ResetSourceVoice(IXAudio2SourceVoice *targetSourceVoice,
                                   const SoundPacket& soundPacket) {

    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = soundPacket.GetDataSize();
    buffer.pAudioData = soundPacket.GetBuffer();
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    HRESULT hr = targetSourceVoice->SubmitSourceBuffer(&buffer);
}
