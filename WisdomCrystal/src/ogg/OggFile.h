// OggFile.h

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <vorbis/vorbisfile.h>
#include <vorbis/vorbisenc.h>

#include "Deleter.h"


namespace Ogg {

class OggFile {

public:
    OggFile();
    virtual ~OggFile();

    bool Init(const std::string& filePath);

    WAVEFORMATEX GetWaveFormatEx() const { return mFormat; }
    std::vector<std::vector<char>>* GetBufferPtr() { return &mBuffer; }

    void Update();

private:
    static const int BUFFER_SIZE = 4096;

    std::unique_ptr<OggVorbis_File, OvfDeleter> mOvf;
    WAVEFORMATEX mFormat;

    std::vector<std::vector<char>> mBuffer;
    bool mIsLoaded;
    long mOffset;
};

}
