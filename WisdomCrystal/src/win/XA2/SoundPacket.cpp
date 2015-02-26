// SoundPacket.cpp

#include "SoundPacket.h"
#include <memory>


SoundPacket::SoundPacket() : mBuffer(), mDataSize(-1) {
    // empty
}


SoundPacket::~SoundPacket() {
    // empty
}


// bufferとその大きさを受け取ったときの初期化
void SoundPacket::Init(std::vector<unsigned char> *srcBuffer, const long begin, const long end) {
    mDataSize = end - begin;

    // mBuffer を dataSize バイト確保
    mBuffer.resize(mDataSize);

    // srcBuffer から mBuffer へ指定範囲コピー
    std::copy(srcBuffer->begin() + begin, srcBuffer->begin() + end, mBuffer.begin());
}


// WaveFile のみを受け取ったときの初期化
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