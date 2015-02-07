// WaveData.h

#pragma once

#include <Windows.h>
#include <vector>


class WaveData {

public:
    WaveData();
    virtual ~WaveData();

    bool Init(LPTSTR waveFilePath);

    inline WAVEFORMATEX GetWaveFormatEx() const {
        return mFormatEx;
    }
    inline const DWORD GetDataSize() const {
        return mDataSize;
    }
    inline std::vector<BYTE>* GetDataBufferPtr() {
        return &mDataBuffer;
    }

private:
    bool readWaveFile();

    LPTSTR mWaveFilePath;
    std::vector<BYTE> mDataBuffer;

    WAVEFORMATEX mFormatEx;
    DWORD mDataSize;
};
