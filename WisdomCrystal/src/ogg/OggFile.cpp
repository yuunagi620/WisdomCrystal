// OggFile.cpp

#pragma comment (lib, "libogg_static.lib")
#pragma comment (lib, "libvorbis_static.lib")
#pragma comment (lib, "libvorbisfile_static.lib")

#include "OggFile.h"
#include "util/CSVHandler.h"


namespace Ogg {

OggFile::OggFile() : mOvf(nullptr),
                     mFormat(),
                     mBuffer(),
                     mIsLooped(true),
                     mOffset(0)
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
    mFormat.wFormatTag      = WAVE_FORMAT_PCM;
    mFormat.nChannels       = static_cast<WORD>(oggInfo->channels);
    mFormat.nSamplesPerSec  = oggInfo->rate;
    mFormat.wBitsPerSample  = 16;
    mFormat.nBlockAlign     = static_cast<WORD>(oggInfo->channels * 2);
    mFormat.nAvgBytesPerSec = mFormat.nSamplesPerSec * mFormat.nBlockAlign;

    return true;
}


void OggFile::Update() {
    mBuffer.push(std::vector<char>());	
    //mBuffer.back().resize(262144);
    mBuffer.back().resize(162144);

    int readSize = 0;
    int bitStream = 0;
    long completeSize = 0;
    long requestSize = 4096;

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
            if (mIsLooped) {

                // �C���g���𔲂������ʒu�ɃV�[�N
                ov_pcm_seek(mOvf.get(), mOffset); 
            } else {

                // ���[�v���Ȃ��̂ŉ�������������
                break;
            }
        } 

        completeSize += readSize;

        // �g�`�f�[�^�z��̎��̏������݈ʒu���o�b�t�@�T�C�Y�𒴂��Ă��烋�[�v�𔲂���
	    if (completeSize >= mBuffer.back().size()) {
	        break;
	    }

        // �o�b�t�@��S����������łȂ������玟�̏������ݗv���T�C�Y���o�b�t�@�T�C�Y���珑�����񂾃T�C�Y�����������̂ɂ���
	    if (mBuffer.back().size() - completeSize < 4096) {
	        requestSize = mBuffer.back().size() - completeSize;
	    }

    }
}

} // namespace Ogg
