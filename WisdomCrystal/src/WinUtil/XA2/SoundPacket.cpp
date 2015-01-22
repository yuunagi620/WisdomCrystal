// SoundPacket.cpp

#include "SoundPacket.h"
#include <memory>


SoundPacket::SoundPacket() : mBuffer(nullptr), mDataSize(-1) {
    // empty
}


SoundPacket::~SoundPacket() {
    mBuffer.reset();
}


// bufferとその大きさを受け取ったときの初期化
bool SoundPacket::Init(const BYTE *srcBuffer, const long dataSize) {

    // mBuffer を dataSize バイト確保
    mBuffer.reset(new BYTE[dataSize], std::default_delete<BYTE[]>());

    // 受け取った srcBuffer からmBufferへコピー
    mDataSize = dataSize;
    memcpy_s(mBuffer.get(), mDataSize, srcBuffer, dataSize);

    return true;
}


// WaveData のみを受け取ったときの初期化
bool SoundPacket::Init(const WaveData& waveData) {
    return Init(waveData.GetDataBuffer(), waveData.GetDataSize());
}


// ボイスキューに新しいオーディオ バッファーを追加
void SoundPacket::AddSoundPacket(IXAudio2SourceVoice *targetSourceVoice,
                                 const SoundPacket& soundPacket) {

    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = soundPacket.GetDataSize();
    buffer.pAudioData = soundPacket.GetBuffer();
    buffer.Flags = 0;

    targetSourceVoice->SubmitSourceBuffer(&buffer);
}


// 現在再生している音をリセットしてボイスキューにバッファーを追加
void SoundPacket::ResetSourceVoice(IXAudio2SourceVoice *targetSourceVoice,
                                   const SoundPacket& soundPacket) {

    XAUDIO2_BUFFER buffer = {0};
    buffer.AudioBytes = soundPacket.GetDataSize();
    buffer.pAudioData = soundPacket.GetBuffer();
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    HRESULT hr = targetSourceVoice->SubmitSourceBuffer(&buffer);
}
