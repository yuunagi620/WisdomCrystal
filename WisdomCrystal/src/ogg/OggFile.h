// OggFile.h

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <vorbis/vorbisfile.h>
#include <vorbis/vorbisenc.h>

#include "Deleter.h"


namespace Ogg {

class OggFile {

public:
    OggFile();
    virtual ~OggFile();

    bool Init(const std::string& filePath);

    void Load(int size);

    inline WAVEFORMATEX GetWaveFormatEx() const { return mFormat; }

    inline std::vector<std::vector<char>>* GetBufferPtr() { return &mBuffer; }

private:
    static const int MAX_READ_SIZE = 4096; // ov_read ä÷êîÇÃãKíËíl

    std::unique_ptr<OggVorbis_File, OvfDeleter> mOvf;
    WAVEFORMATEX mFormat;

    std::vector<std::vector<char>> mBuffer;
    bool mIsLoadedComplete;
};

}
