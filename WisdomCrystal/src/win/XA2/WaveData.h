// WaveData.h

#pragma once

#include <Windows.h>
#include <memory>
#include <vector>


class WaveData {

public:
    WaveData();
    virtual ~WaveData();

    bool Init(LPTSTR waveFilePath);

    inline WAVEFORMATEX* GetWaveFormatExPtr() {
        return &mFormatEx;
    }
    inline BYTE* GetDataBuffer() {
        return &mDataBuffer.front();
    }
    inline const DWORD GetDataSize() const {
        return mDataSize;
    }

private:
    bool ReadWaveFile();

    LPTSTR mWaveFilePath;
    std::vector<BYTE> mDataBuffer;

    WAVEFORMATEX mFormatEx;
    DWORD mDataSize;
};
