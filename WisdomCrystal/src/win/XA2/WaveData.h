// WaveData.h

#pragma once

#include <Windows.h>
#include <memory>
#include <vector>


class WaveData {

public:
    WaveData();
    virtual ~WaveData();

    bool Init(TCHAR *waveFilePath);

    inline WAVEFORMATEX *GetWaveFormatExPtr() {
        return &mFormatEx;
    }
    inline const DWORD GetDataSize() const {
        return mDataSize;
    }
    inline BYTE *GetDataBuffer() const {
        return mDataBuffer.get();
    }

private:
    bool ReadWaveFile();

    LPTSTR mWaveFilePath;
    std::shared_ptr<BYTE> mDataBuffer;

    WAVEHDR mHeader;
    WAVEFORMATEX mFormatEx;
    DWORD mDataSize;
};
