// WaveData.cpp

// Includes
#include "WaveData.h"
#include "MmioUtil.h"


WaveData::WaveData() : mDataBuffer(nullptr),
                       mHeader(),
                       mFormatEx(),
                       mDataSize(0) {
    //empty
}


WaveData::~WaveData() {
    mDataBuffer.reset();
}


bool WaveData::Init(TCHAR* waveFilePath) {

    if (MmioUtil::ReadWaveFile(&mFormatEx, &mDataBuffer, &mDataSize, waveFilePath) == false) {
        return false; // WaveFile ‚Ì“Ç‚ÝŽæ‚è‚ÉŽ¸”s
    }

    mHeader.lpData = reinterpret_cast<LPSTR>(mDataBuffer.get());
    mHeader.dwBufferLength = mDataSize;
    mHeader.dwFlags = 0;

    return true;
}
