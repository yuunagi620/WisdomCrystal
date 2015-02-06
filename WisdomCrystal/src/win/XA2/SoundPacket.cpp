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


// bufferとその大きさを受け取ったときの初期化
bool SoundPacket::Init(std::vector<BYTE> *srcBuffer, const long dataSize) {

    // mBuffer を dataSize バイト確保
    mBuffer.resize(srcBuffer->size());

    std::copy(srcBuffer->begin(), srcBuffer->end(), mBuffer.begin());

    // 受け取った srcBuffer からmBufferへコピー
    mDataSize = dataSize;
    //memcpy_s(&mBuffer.front(), mDataSize, srcBuffer, dataSize);

    return true;
}


// WaveData のみを受け取ったときの初期化
bool SoundPacket::Init(WaveData* waveData) {
    return Init(waveData->GetDataBuffer(), waveData->GetDataSize());
}


// ボイスキューに新しいオーディオ バッファーを追加
void SoundPacket::AddSoundPacket(IXAudio2SourceVoice *targetSourceVoice,
                                 SoundPacket *soundPacket) {

    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = soundPacket->GetDataSize();
    buffer.pAudioData = soundPacket->GetBuffer();
    buffer.Flags = 0;

    targetSourceVoice->SubmitSourceBuffer(&buffer);
}


// 現在再生している音をリセットしてボイスキューにバッファーを追加
void SoundPacket::ResetSourceVoice(IXAudio2SourceVoice *targetSourceVoice,
                                   SoundPacket* soundPacket) {

    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = soundPacket->GetDataSize();
    buffer.pAudioData = soundPacket->GetBuffer();
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    HRESULT hr = targetSourceVoice->SubmitSourceBuffer(&buffer);
}
