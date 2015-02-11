// WaveFile.h

#pragma once

#include <Windows.h>
#include <vector>
#include <string>


class WaveFile {

public:
    WaveFile();
    virtual ~WaveFile();

    bool Init(const std::string& filePath);
    bool InitFromResource(LPCTSTR resourceName, LPCTSTR resourceType);

    inline const WAVEFORMATEX GetWaveFormatEx() const {
        return mFormat;
    }
    inline const DWORD GetDataSize() const {
        return mBuffer.size();
    }
    inline std::vector<unsigned char>* GetDataBufferPtr() {
        return &mBuffer;
    }

private:
    bool readWaveFile();

private:
    std::string mWaveFilePath;
    std::vector<unsigned char> mBuffer;

    WAVEFORMATEX mFormat;
};
