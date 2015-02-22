// OggFile.cpp

#pragma comment (lib, "libogg_static.lib")
#pragma comment (lib, "libvorbis_static.lib")
#pragma comment (lib, "libvorbisfile_static.lib")

#include "OggFile.h"


namespace Ogg {

OggFile::OggFile() : mOvf(nullptr),
                     mFormat(),
                     mBuffer()
{
    // empty
}


OggFile::~OggFile() {
    // empty
}


bool OggFile::Init(const std::string& filePath) {
    
    // Oggファイルのオープン
    mOvf.reset(new OggVorbis_File);
    int errorCode = ov_fopen(filePath.c_str(), mOvf.get());
    if (errorCode) {
        return false;
    }

    // Oggファイルの情報を取得
    vorbis_info* oggInfo = ov_info(mOvf.get(), -1);
    if (oggInfo == nullptr) {
        return false;
    }

    // WAVEFORMATEXを設定
    mFormat.wFormatTag      = WAVE_FORMAT_PCM;
    mFormat.nChannels       = static_cast<WORD>(oggInfo->channels);
    mFormat.nSamplesPerSec  = oggInfo->rate;
    mFormat.wBitsPerSample  = 16;
    mFormat.nBlockAlign     = static_cast<WORD>(oggInfo->channels * 2);
    mFormat.nAvgBytesPerSec = mFormat.nSamplesPerSec * mFormat.nBlockAlign;


    mBuffer.resize(4096);
    int bitStream = 0;
    long readSize = ov_read(mOvf.get(),
                            reinterpret_cast<char *>(&mBuffer.front()),
                            4096,
                            0,
                            2,
                            1,
                            &bitStream);

    return true;
}


void OggFile::setWaveFormat() {

}

} // namespace Ogg
