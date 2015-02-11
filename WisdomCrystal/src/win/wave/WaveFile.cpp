// WaveFile.cpp

#include <fstream>
#include <cstdint>

#include "win/wave/WaveFile.h"


WaveFile::WaveFile() : mWaveFilePath(),
                       mBuffer(),
                       mFormat()
{
    //empty
}


WaveFile::~WaveFile() {
    // empty
}


bool WaveFile::Init(const std::string& filePath) {
    mWaveFilePath = filePath;

    if (readWaveFile() == false) {
        return false;
    }
    return true;
}


bool InitFromResource(LPCTSTR resourceName, LPCTSTR resourceType) {

    return true;
}


bool WaveFile::readWaveFile(){

    // ファイルの読み込み
    std::ifstream ifs(mWaveFilePath, std::ios::in | std::ios::binary);
    if (ifs == false) {
        MessageBox(nullptr, TEXT("WaveFile: ファイルのオープンに失敗．"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // 4バイトを読み込んで RIFE ヘッダかどうかを調べる
    const char riff[4] = {'R', 'I', 'F', 'F'};
    char readData[4];  
    ifs.read(readData, sizeof(readData));
    if (std::memcmp(riff, readData, sizeof(riff))) {
        MessageBox(nullptr, TEXT("WaveFile: RIFEチャンクが存在しませんでした．"), TEXT("ERROR"), MB_OK);
        return false;
    } 

    // ファイルサイズ情報の4バイト読み飛ばす
    ifs.ignore(4);

    // 4バイトを読み込んで WAVE ヘッダかどうかを調べる
    const char wave[4] = {'W', 'A', 'V', 'E'};

    ifs.read(readData, sizeof(readData));
    if (std::memcmp(wave, readData, sizeof(wave))) {
        MessageBox(nullptr, TEXT("WaveFile: WAVEチャンクが存在しませんでした．"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // 4バイトを読み込んで fmt チャンクかどうかを調べる
    const char fmt[4] = {'f', 'm', 't', ' '};
    ifs.read(readData, sizeof(readData));
    if (std::memcmp(fmt, readData, sizeof(fmt))) {
        MessageBox(nullptr, TEXT("WaveFile: WAVEチャンクが存在しませんでした．"), TEXT("ERROR"), MB_OK);
        return false;
    } 

    // フォーマットサイズの読み込み
    std::uint32_t formatSize;
    ifs.read(reinterpret_cast<char *>(&formatSize), sizeof(formatSize));

    // フォーマットIDの読み込み
    std::uint16_t id;
    ifs.read(reinterpret_cast<char *>(&id), sizeof(id));

    //  フォーマットIDから対応している形式か調べる
    if (id == 1) {
        mFormat.wFormatTag = WAVE_FORMAT_PCM; // リニアPCM
    } else if (id == 2) {
        mFormat.wFormatTag = WAVE_FORMAT_ADPCM; // MS ADPCM 
    } else {
        MessageBox(nullptr, TEXT("WaveFile: このフォーマットには対応していません．"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // チャンネル数の読み込み
    ifs.read(reinterpret_cast<char *>(&mFormat.nChannels), sizeof(mFormat.nChannels));

    // サンプルレートの読み込み
    ifs.read(reinterpret_cast<char *>(&mFormat.nSamplesPerSec), sizeof(mFormat.nSamplesPerSec));

    // データ速度 (Byte/sec)の読み込み
    ifs.read(reinterpret_cast<char *>(&mFormat.nAvgBytesPerSec), sizeof(mFormat.nAvgBytesPerSec));

    // ブロックサイズ(Byte/sample×チャンネル数)の読み込み
    ifs.read(reinterpret_cast<char *>(&mFormat.nBlockAlign), sizeof(mFormat.nBlockAlign));

    // サンプル当たりのビット数の読み込み
    ifs.read(reinterpret_cast<char *>(&mFormat.wBitsPerSample), sizeof(mFormat.wBitsPerSample));

    // 拡張ヘッダ情報を読み飛ばす
    ifs.ignore(formatSize - 16);

    // 4バイトを読み込んで data チャンクかどうかを調べる
    const char data[4] = {'d', 'a', 't', 'a'};
    ifs.read(readData, sizeof(readData));
    if (std::memcmp(data, readData, sizeof(data))) {
        MessageBox(nullptr, TEXT("WaveFile: dataチャンクが存在しませんでした．"), TEXT("ERROR"), MB_OK);
        return false;
    } 

    // 波形データのバイト数の読み込み
    std::uint32_t size;
    ifs.read(reinterpret_cast<char *>(&size), sizeof(size));


    // 波形データの読み込み
    mBuffer.resize(size);
    ifs.read(reinterpret_cast<char *>(&mBuffer.front()), size);

    return true;
}