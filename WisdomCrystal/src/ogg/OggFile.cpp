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
    
    // Oggファイルのオープン
    mOvf.reset(new OggVorbis_File);
    int errorCode = ov_fopen(filePath.c_str(), mOvf.get());
    if (errorCode != 0) {
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

    return true;
}


void OggFile::Load(int size) {
    if (mIsLoadedComplete) {
        return;
    }

    mBuffer.push_back(std::vector<char>());	
    mBuffer.back().resize(size);

    int bitStream = 0;     // 現在の論理ビットストリームの番号．特に使用しない
    int readSize  = 0;     // 1回で読み込んだサイズ
    long completeSize = 0; // 今まで読み込んだサイズ

    long requestSize = MAX_READ_SIZE; // 1回の読み込みに要求するサイズ

    for(;;) {
	    readSize = ov_read(mOvf.get(),
                           static_cast<char*>(&mBuffer.back().front() + completeSize),
                           requestSize,
                           0,
                           2,
                           1,
                           &bitStream);

        // 曲が終わった場合
	    if (readSize == 0) {
            mBuffer.back().resize(completeSize);
            mIsLoadedComplete = true;
            break;
        } 

        // 書き込んだサイズを足す
        completeSize += readSize;

        // バッファの次の書き込み位置がバッファサイズを超えてたらループを抜ける
	    if (completeSize >= static_cast<long>(mBuffer.back().size())) {
	        break;
	    }

        // 残りのバッファサイズに合わせて requestSize を調整 
	    if (mBuffer.back().size() - completeSize < MAX_READ_SIZE) {
	        requestSize = mBuffer.back().size() - completeSize;
	    }

    }
}

} // namespace Ogg
