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
bool SoundPacket::Init(std::vector<BYTE> *srcBuffer) {
    mDataSize = srcBuffer->size();

    // mBuffer �� dataSize �o�C�g�m��
    mBuffer.resize(mDataSize);

    std::copy(srcBuffer->begin(), srcBuffer->end(), mBuffer.begin());

    return true;
}


// WaveData �݂̂��󂯎�����Ƃ��̏�����
bool SoundPacket::Init(WaveData* waveData) {
    return Init(waveData->GetDataBufferPtr());
}
