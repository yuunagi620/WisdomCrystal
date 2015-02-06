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
bool SoundPacket::Init(std::vector<BYTE> *srcBuffer) {
    mDataSize = srcBuffer->size();

    // mBuffer を dataSize バイト確保
    mBuffer.resize(mDataSize);

    std::copy(srcBuffer->begin(), srcBuffer->end(), mBuffer.begin());

    return true;
}


// WaveData のみを受け取ったときの初期化
bool SoundPacket::Init(WaveData* waveData) {
    return Init(waveData->GetDataBufferPtr());
}
