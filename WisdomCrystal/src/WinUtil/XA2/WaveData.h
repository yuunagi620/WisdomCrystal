// WaveData.h

#pragma once

#include <Windows.h>
#include <memory>


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
    std::shared_ptr<BYTE> mDataBuffer;

    WAVEHDR mHeader;
    WAVEFORMATEX mFormatEx;
    DWORD mDataSize;
};
