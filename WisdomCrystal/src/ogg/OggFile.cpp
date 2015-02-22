// OggFile.cpp

#pragma comment (lib, "libogg_static.lib")
#pragma comment (lib, "libvorbis_static.lib")
#pragma comment (lib, "libvorbisfile_static.lib")

#include "OggFile.h"


namespace Ogg {

OggFile::OggFile() : mOvf(nullptr),
                     mWaveFormat()
{
    // empty
}


OggFile::~OggFile() {
    // empty
}


bool OggFile::Init(const std::string& filePath) {
    
    // Ogg�t�@�C���̃I�[�v��
    mOvf.reset(new OggVorbis_File);
    int errorCode = ov_fopen(filePath.c_str(), mOvf.get());
    if (errorCode) {
        return false;
    }

    // Ogg�t�@�C���̏����擾
    vorbis_info* oggInfo = ov_info(mOvf.get(), -1);
    if (oggInfo == nullptr) {
        return false;
    }

    // WAVEFORMATEX��ݒ�
    mWaveFormat.wFormatTag      = WAVE_FORMAT_PCM;
    mWaveFormat.nChannels       = static_cast<WORD>(oggInfo->channels);
    mWaveFormat.nSamplesPerSec  = oggInfo->rate;
    mWaveFormat.wBitsPerSample  = 16;
    mWaveFormat.nBlockAlign     = static_cast<WORD>(oggInfo->channels * 2);
    mWaveFormat.nAvgBytesPerSec = mWaveFormat.nSamplesPerSec * mWaveFormat.nBlockAlign;

    return true;
}


void OggFile::setWaveFormat() {

}

} // namespace Ogg
