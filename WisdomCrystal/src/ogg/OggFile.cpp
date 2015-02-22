// OggFile.cpp

#pragma comment (lib, "libogg_static.lib")
#pragma comment (lib, "libvorbis_static.lib")
#pragma comment (lib, "libvorbisfile_static.lib")

#include "OggFile.h"

#include "vorbis\vorbisfile.h"
#include "vorbis\vorbisenc.h"


namespace Ogg {

OggFile::OggFile() : mOvf(nullptr),
                     mWaveFormat()
{

}


OggFile::~OggFile() {
    // empty
}


bool OggFile::Init(const std::string& filePath) {
    
    // Oggファイルのオープン
    mOvf.reset(new OggVorbis_File());
    int errorCode = ov_fopen(filePath.c_str(), mOvf.get());

    if (errorCode) {
        return false;
    }

    return true;
}

} // namespace Ogg
