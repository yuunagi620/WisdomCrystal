// WaveData.cpp

// Includes
#include "WaveData.h"
#include "MmioUtil.h"


WaveData::WaveData() : mWaveFilePath(nullptr),
                       mDataBuffer(nullptr),
                       mHeader(),
                       mFormatEx(),
                       mDataSize(0)
{
    //empty
}


WaveData::~WaveData() {
    mDataBuffer.reset();
}


bool WaveData::Init(TCHAR* waveFilePath) {

    mWaveFilePath = waveFilePath;

    if (ReadWaveFile() == false) {
        return false; // WaveFile の読み取りに失敗
    }

    mHeader.lpData = reinterpret_cast<LPSTR>(mDataBuffer.get());
    mHeader.dwBufferLength = mDataSize;
    mHeader.dwFlags = 0;

    return true;
}


bool WaveData::ReadWaveFile() {
    HMMIO hMMIO;
    MMCKINFO mmckRiff;
    MMCKINFO mmckFormat;
    MMCKINFO mmckData;

    std::shared_ptr<BYTE> dataBuffer;

    bool ret = true;

    // ファイルのオープン
    hMMIO = mmioOpen(mWaveFilePath, nullptr, MMIO_READ);
    if (hMMIO == nullptr) {
        MessageBox(nullptr, TEXT("readWaveFile: ファイルのオープンに失敗しました。"), nullptr, MB_ICONWARNING);
        return false;
    }

    // ファイルが WAVE 形式かどうか判定
    mmckRiff.fccType = mmioStringToFOURCC(TEXT("WAVE"), 0);
    if (mmioDescend(hMMIO, &mmckRiff, nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR) {
        MessageBox(nullptr, TEXT("readWaveFile: WAVEファイルではありません。"), nullptr, MB_ICONWARNING);
        ret = false;
        goto onError;
    }

    // 'fmt ' chunk の読み取り
    mmckFormat.ckid = mmioStringToFOURCC(TEXT("fmt "), 0); // 'fmt 'の4文字目は空白
    if (mmioDescend(hMMIO, &mmckFormat, nullptr, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
        MessageBox(nullptr, TEXT("readWaveFile: 無効なファイルです。(no 'fmt ' chunk)"), nullptr, MB_ICONWARNING);
        ret = false;
        goto onError;
    }

    // PCM データかどうか判定
    mmioRead(hMMIO, reinterpret_cast<HPSTR>(&mFormatEx), mmckFormat.cksize);
    mmioAscend(hMMIO, &mmckFormat, 0);
    if (mFormatEx.wFormatTag != WAVE_FORMAT_PCM) {
        MessageBox(nullptr, TEXT("readWaveFile: PCMデータではありません。"), nullptr, MB_ICONWARNING);
        ret = false;
        goto onError;
    }

    // data chunk の読み取り
    mmckData.ckid = mmioStringToFOURCC(TEXT("data"), 0);
    if (mmioDescend(hMMIO, &mmckData, nullptr, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
        MessageBox(nullptr, TEXT("readWaveFile: data chunk を読み取れませんでした。"), nullptr, MB_ICONWARNING);
        ret = false;
        goto onError;
    }

    // mBuffer を mmckData.cksize バイト確保
    dataBuffer.reset(new BYTE[mmckData.cksize], std::default_delete<BYTE[]>());

    // WAVE データのサイズ分データを取得
    mmioRead(hMMIO, reinterpret_cast<HPSTR>(dataBuffer.get()), mmckData.cksize);

    // RIFF ファイルの chunk から退出
    mmioAscend(hMMIO, &mmckRiff, 0);

    mDataBuffer = dataBuffer; 
    mDataSize = mmckData.cksize;

onError:
    mmioClose(hMMIO, 0);
    return ret;
}
