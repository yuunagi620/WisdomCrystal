// OggFile.cpp

#pragma comment (lib, "libogg_static.lib")
#pragma comment (lib, "libvorbis_static.lib")
#pragma comment (lib, "libvorbisfile_static.lib")

#include "OggFile.h"


namespace Ogg {

OggFile::OggFile() : mOvf(nullptr), mBuffer(), mFormat(), mIsLoadedComplete(false) {
    // empty
}


OggFile::~OggFile() {
    // empty
}


bool OggFile::Init(const std::string& filePath) {
    
    // Ogg�t�@�C���̃I�[�v��
    mOvf.reset(new OggVorbis_File);
    int errorCode = ov_fopen(filePath.c_str(), mOvf.get());
    if (errorCode != 0) {
        return false;
    }

    // Ogg�t�@�C���̏����擾
    vorbis_info* oggInfo = ov_info(mOvf.get(), -1);
    if (oggInfo == nullptr) {
        return false;
    }

    // WAVEFORMATEX��ݒ�
    mFormat.wFormatTag      = WAVE_FORMAT_PCM;
    mFormat.nChannels       = static_cast<WORD>(oggInfo->channels);
    mFormat.nSamplesPerSec  = oggInfo->rate;
    mFormat.wBitsPerSample  = 16;
    mFormat.nBlockAlign     = static_cast<WORD>(oggInfo->channels * 2);
    mFormat.nAvgBytesPerSec = mFormat.nSamplesPerSec * mFormat.nBlockAlign;

    return true;
}


void OggFile::Load(int size) {
    if (mIsLoadedComplete) {
        return;
    }

    mBuffer.push_back(std::vector<char>());	
    mBuffer.back().resize(size);

    int bitStream = 0;     // ���݂̘_���r�b�g�X�g���[���̔ԍ��D���Ɏg�p���Ȃ�
    int readSize  = 0;     // 1��œǂݍ��񂾃T�C�Y
    long completeSize = 0; // ���܂œǂݍ��񂾃T�C�Y

    long requestSize = MAX_READ_SIZE; // 1��̓ǂݍ��݂ɗv������T�C�Y

    for(;;) {
	    readSize = ov_read(mOvf.get(),
                           static_cast<char*>(&mBuffer.back().front() + completeSize),
                           requestSize,
                           0,
                           2,
                           1,
                           &bitStream);

        // �Ȃ��I������ꍇ
	    if (readSize == 0) {
            mBuffer.back().resize(completeSize);
            mIsLoadedComplete = true;
            break;
        } 

        // �������񂾃T�C�Y�𑫂�
        completeSize += readSize;

        // �o�b�t�@�̎��̏������݈ʒu���o�b�t�@�T�C�Y�𒴂��Ă��烋�[�v�𔲂���
	    if (completeSize >= static_cast<long>(mBuffer.back().size())) {
	        break;
	    }

        // �c��̃o�b�t�@�T�C�Y�ɍ��킹�� requestSize �𒲐� 
	    if (mBuffer.back().size() - completeSize < MAX_READ_SIZE) {
	        requestSize = mBuffer.back().size() - completeSize;
	    }

    }
}

} // namespace Ogg
