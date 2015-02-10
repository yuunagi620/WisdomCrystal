// WaveData.cpp

#include "WaveData.h"


WaveData::WaveData() : mWaveFilePath(nullptr),
                       mDataBuffer(),
                       mFormatEx(),
                       mDataSize(0)
{
    //empty
}


WaveData::~WaveData() {
    // empty
}


bool WaveData::Init(LPTSTR waveFilePath) {
    mWaveFilePath = waveFilePath;

    if (readWaveFile() == false) {
        return false;
    }
    return true;
}


bool WaveData::readWaveFile() {
    bool ret = true;

    HMMIO hMMIO;
    MMCKINFO mmckRiff;
    MMCKINFO mmckFormat;
    MMCKINFO mmckData;

    // ファイルのオープン
    hMMIO = mmioOpen(mWaveFilePath, nullptr, MMIO_READ);
    if (hMMIO == nullptr) {
        MessageBox(nullptr, TEXT("WaveData: ファイルのオープンに失敗しました．"), nullptr, MB_ICONWARNING);
        return false;
    }

    // ファイルが WAVE 形式かどうか判定
    mmckRiff.fccType = mmioStringToFOURCC(TEXT("WAVE"), 0);
    if (mmioDescend(hMMIO, &mmckRiff, nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR) {
        MessageBox(nullptr, TEXT("WaveData: WAVEファイルではありません．"), nullptr, MB_ICONWARNING);
        ret = false;
        goto cleanup;
    }

    // 'fmt ' chunk の読み取り
    mmckFormat.ckid = mmioStringToFOURCC(TEXT("fmt "), 0); // 'fmt 'の4文字目は空白
    if (mmioDescend(hMMIO, &mmckFormat, nullptr, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
        MessageBox(nullptr, TEXT("WaveData: 無効なファイルです．(no 'fmt ' chunk)"), nullptr, MB_ICONWARNING);
        ret = false;
        goto cleanup;
    }

    // PCM データかどうか判定
    mmioRead(hMMIO, reinterpret_cast<HPSTR>(&mFormatEx), mmckFormat.cksize);
    mmioAscend(hMMIO, &mmckFormat, 0);
    if (mFormatEx.wFormatTag != WAVE_FORMAT_PCM) {
        MessageBox(nullptr, TEXT("WaveData: PCMデータではありません．"), nullptr, MB_ICONWARNING);
        ret = false;
        goto cleanup;
    }

    // data chunk の読み取り
    mmckData.ckid = mmioStringToFOURCC(TEXT("data"), 0);
    if (mmioDescend(hMMIO, &mmckData, nullptr, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
        MessageBox(nullptr, TEXT("WaveData: data chunk を読み取れませんでした．"), nullptr, MB_ICONWARNING);
        ret = false;
        goto cleanup;
    }

    // mmckData.cksize バイト分確保
    mDataBuffer.resize(mmckData.cksize);

    // WAVE データのサイズ分データを mDataBuffer に読み取る
    if (mmioRead(hMMIO, reinterpret_cast<HPSTR>(&mDataBuffer.front()), mDataBuffer.size()) == -1) {
        MessageBox(nullptr, TEXT("WaveData: データの読み取りに失敗しました．"), nullptr, MB_ICONWARNING);
        ret = false;
        goto cleanup;
    }

    // RIFF ファイルの chunk から退出
    mmioAscend(hMMIO, &mmckRiff, 0);

    mDataSize = mmckData.cksize;

cleanup:
    mmioClose(hMMIO, 0);
    return ret;
}
