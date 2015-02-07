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
bool SoundPacket::Init(std::vector<BYTE> *srcBuffer, const long begin, const long end) {
    mDataSize = end - begin;

    // mBuffer を dataSize バイト確保
    mBuffer.resize(mDataSize);

    std::vector<BYTE>::iterator beginIt = srcBuffer->begin() + begin;
    std::vector<BYTE>::iterator endIt = srcBuffer->begin() + end;

    std::copy(beginIt, endIt, mBuffer.begin());

    return true;
}


// WaveData のみを受け取ったときの初期化
bool SoundPacket::Init(WaveData* waveData) {
    return Init(waveData->GetDataBufferPtr(), 0, waveData->GetDataSize());
}


// 現在再生している音をリセットしてボイスキューにバッファーを追加
void SoundPacket::ResetSoundPacket(IXAudio2SourceVoice *targetSourceVoice) {
    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = GetDataSize();
    buffer.pAudioData = &(GetBufferPtr()->front());
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    targetSourceVoice->SubmitSourceBuffer(&buffer);
}


void SoundPacket::AddSoundPacket(IXAudio2SourceVoice *targetSourceVoice) {
    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = GetDataSize();
    buffer.pAudioData = &(GetBufferPtr()->front());
    buffer.Flags = 0;

    targetSourceVoice->SubmitSourceBuffer(&buffer);
}