// OggFile.h

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "vorbis\vorbisfile.h"
#include "vorbis\vorbisenc.h"
#include "Deleter.h"


namespace Ogg {

class OggFile {

public:
    OggFile();
    virtual ~OggFile();

    bool Init(const std::string& filePath);

private:
    void setWaveFormat();

private:
    std::unique_ptr<OggVorbis_File, OvfDeleter> mOvf;
    WAVEFORMATEX mFormat;
    std::vector<unsigned char> mBuffer;
};

}
