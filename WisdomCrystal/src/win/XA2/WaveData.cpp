// WaveData.cpp

#include <fstream>
#include <cstdint>
#include <cstring>

#include "WaveData.h"


WaveData::WaveData() : mWaveFilePath(),
                       mBuffer(),
                       mFormat(),
                       mDataSize(0)
{
    //empty
}


WaveData::~WaveData() {
    // empty
}


bool WaveData::Init(const std::string& filePath) {
    mWaveFilePath = filePath;

    if (readWaveFile() == false) {
        return false;
    }
    return true;
}


bool InitFromResource(LPCTSTR resourceName, LPCTSTR resourceType) {

    return true;
}


bool WaveData::readWaveFile(){

    std::ifstream fin(mWaveFilePath, std::ios::in | std::ios::binary);
    if (!fin) {
        throw std::runtime_error("ファイルを開くのに失敗");
    }
    const char riff[4] = {'R', 'I', 'F', 'F'};
    char read_data[4];
    // ヘッダの頭から4バイトを読み込んで"RIFE"かどうかを調べる
    fin.read(read_data, sizeof(read_data));
    if (std::memcmp(riff, read_data, sizeof(riff))) {
        throw std::runtime_error("RIFEチャンクが存在しない");
    } 
    // 4バイト読み飛ばし
    fin.ignore(4);
    const char wave[4] = {'W', 'A', 'V', 'E'};
    // 続いての4バイトを読み込んで"WAVE"かどうかを調べる
    fin.read(read_data, sizeof(read_data));
    if (std::memcmp(wave, read_data, sizeof(wave))) {
	throw std::runtime_error("WAVEチャンクが存在しない");
    } 
    // 続いての4バイトを読み込んで"fmt "かどうかを調べる
    const char fmt[4] = {'f', 'm', 't', ' '};
    fin.read(read_data, sizeof(read_data));
    if (std::memcmp(fmt, read_data, sizeof(fmt))) {
	throw std::runtime_error("fmt チャンクが存在しない");
    } 
    std::uint32_t format_size;
    // フォーマットサイズ読み込み
    fin.read(reinterpret_cast<char *>(&format_size), sizeof(format_size));
    std::uint16_t id;
    // フォーマットタグIDの読み込み
    fin.read(reinterpret_cast<char *>(&id), sizeof(id));
    // IDに対応するフォーマットにする
    switch (id) {
    case 1:
	mFormat.wFormatTag = WAVE_FORMAT_PCM;
	break;
    case 2:
	mFormat.wFormatTag = WAVE_FORMAT_ADPCM;
	break;
    default:
	throw std::runtime_error("対応していないフォーマット");
    }
    // チャンネル数を読み込む
    fin.read(reinterpret_cast<char *>(&mFormat.nChannels), sizeof(mFormat.nChannels));
    // サンプルレートを読み込む
    fin.read(reinterpret_cast<char *>(&mFormat.nSamplesPerSec), sizeof(mFormat.nSamplesPerSec));
    // データ速度を読み込む
    fin.read(reinterpret_cast<char *>(&mFormat.nAvgBytesPerSec), sizeof(mFormat.nAvgBytesPerSec));
    // ブロックサイズを読み込む
    fin.read(reinterpret_cast<char *>(&mFormat.nBlockAlign), sizeof(mFormat.nBlockAlign));
    // サンプル当たりのビット数を読み込む
    fin.read(reinterpret_cast<char *>(&mFormat.wBitsPerSample), sizeof(mFormat.wBitsPerSample));
    // 拡張ヘッダ情報を読み飛ばす
    fin.ignore(format_size - 16);

    const char data[4] = {'d', 'a', 't', 'a'};
    // 続いての4バイトを読み込んで"data"かどうかを調べる
    fin.read(read_data, sizeof(read_data));
    if (std::memcmp(data, read_data, sizeof(data))) {
	    throw std::runtime_error("dataチャンクが存在しない");
    } 
    std::uint32_t size;
    // 波形データのサイズを読み込む
    fin.read(reinterpret_cast<char *>(&size), sizeof(size));
    mBuffer.resize(size);
    // 波形データ読み込み
    fin.read(reinterpret_cast<char *>(&mBuffer.front()), size);

    return true;
}