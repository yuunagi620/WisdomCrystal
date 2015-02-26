// SoundPacket.cpp

#include "SoundPacket.h"
#include <memory>


SoundPacket::SoundPacket() : mBuffer(), mDataSize(-1) {
    // empty
}


SoundPacket::~SoundPacket() {
    // empty
}


// buffer�Ƃ��̑傫�����󂯎�����Ƃ��̏�����
void SoundPacket::Init(std::vector<unsigned char> *srcBuffer, const long begin, const long end) {
    mDataSize = end - begin;

    // mBuffer �� dataSize �o�C�g�m��
    mBuffer.resize(mDataSize);

    // srcBuffer ���� mBuffer �֎w��͈̓R�s�[
    std::copy(srcBuffer->begin() + begin, srcBuffer->begin() + end, mBuffer.begin());
}


// WaveFile �݂̂��󂯎�����Ƃ��̏�����
void SoundPacket::Init(WaveFile* WaveFile) {
    return Init(WaveFile->GetBufferPtr(), 0, WaveFile->GetDataSize());
}


void SoundPacket::ResetSoundPacket(std::shared_ptr<IXAudio2SourceVoice> targetSourceVoice) {
    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = GetDataSize();
    buffer.pAudioData = &(GetBufferPtr()->front());
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    targetSourceVoice->SubmitSourceBuffer(&buffer);
}


void SoundPacket::AddSoundPacket(std::shared_ptr<IXAudio2SourceVoice> targetSourceVoice) {
    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = GetDataSize();
    buffer.pAudioData = &(GetBufferPtr()->front());
    buffer.Flags = 0;

    targetSourceVoice->SubmitSourceBuffer(&buffer);
}