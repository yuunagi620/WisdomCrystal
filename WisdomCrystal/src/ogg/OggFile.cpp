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

        // 曲が終わった場合
	    if (readSize == 0) {
            if (mIsLooped) {

                // イントロを抜かした位置にシーク
                ov_pcm_seek(mOvf.get(), mOffset); 
            } else {

                // ループしないので何もせず抜ける
                break;
            }
        } 

        completeSize += readSize;

        // 波形データ配列の次の書き込み位置がバッファサイズを超えてたらループを抜ける
	    if (completeSize >= mBuffer.back().size()) {
	        break;
	    }

        // バッファを全部書き込んでなかったら次の書き込み要求サイズをバッファサイズから書き込んだサイズを引いたものにする
	    if (mBuffer.back().size() - completeSize < 4096) {
	        requestSize = mBuffer.back().size() - completeSize;
	    }

    }
}

} // namespace Ogg
