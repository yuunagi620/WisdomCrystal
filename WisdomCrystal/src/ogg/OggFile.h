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

    void Load(int size = 1048576);

    inline WAVEFORMATEX GetWaveFormatEx() const { return mFormat; }

    inline std::vector<std::vector<char>>* GetBufferPtr() { return &mBuffer; }

private:
    static const int MAX_READ_SIZE = 4096; // ov_read ä÷êîÇÃãKíËíl

    std::unique_ptr<OggVorbis_File, OvfDeleter> mOvf;
    std::vector<std::vector<char>> mBuffer;
    WAVEFORMATEX mFormat;
    bool mIsLoadedComplete;
};

}
