// WaveFile.h

#pragma once

#include <Windows.h>
#include <vector>
#include <string>


class WaveFile {

public:
    WaveFile();
    virtual ~WaveFile();

    bool Load(const std::string& filePath);

    inline const WAVEFORMATEX GetWaveFormatEx() const {
        return mFormat;
    }
    inline const DWORD GetDataSize() const {
        return mBuffer.size();
    }
    inline std::vector<unsigned char>* GetBufferPtr() {
        return &mBuffer;
    }

private:
    std::vector<unsigned char> mBuffer;
    WAVEFORMATEX mFormat;
};
