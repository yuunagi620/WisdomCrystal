// WaveData.cpp

// Includes
#include "WaveData.h"
#include "MmioUtil.h"


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

    if (ReadWaveFile() == false) {
        return false; // WaveFile �̓ǂݎ��Ɏ��s
    }
    return true;
}


bool WaveData::ReadWaveFile() {
    HMMIO hMMIO;
    MMCKINFO mmckRiff;
    MMCKINFO mmckFormat;
    MMCKINFO mmckData;

    std::vector<BYTE> tempBuffer;

    bool ret = true;

    // �t�@�C���̃I�[�v��
    hMMIO = mmioOpen(mWaveFilePath, nullptr, MMIO_READ);
    if (hMMIO == nullptr) {
        MessageBox(nullptr, TEXT("WaveData: �t�@�C���̃I�[�v���Ɏ��s���܂����D"), nullptr, MB_ICONWARNING);
        return false;
    }

    // �t�@�C���� WAVE �`�����ǂ�������
    mmckRiff.fccType = mmioStringToFOURCC(TEXT("WAVE"), 0);
    if (mmioDescend(hMMIO, &mmckRiff, nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR) {
        MessageBox(nullptr, TEXT("WaveData: WAVE�t�@�C���ł͂���܂���D"), nullptr, MB_ICONWARNING);
        ret = false;
        goto cleanup;
    }

    // 'fmt ' chunk �̓ǂݎ��
    mmckFormat.ckid = mmioStringToFOURCC(TEXT("fmt "), 0); // 'fmt '��4�����ڂ͋�
    if (mmioDescend(hMMIO, &mmckFormat, nullptr, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
        MessageBox(nullptr, TEXT("WaveData: �����ȃt�@�C���ł��D(no 'fmt ' chunk)"), nullptr, MB_ICONWARNING);
        ret = false;
        goto cleanup;
    }

    // PCM �f�[�^���ǂ�������
    mmioRead(hMMIO, reinterpret_cast<HPSTR>(&mFormatEx), mmckFormat.cksize);
    mmioAscend(hMMIO, &mmckFormat, 0);
    if (mFormatEx.wFormatTag != WAVE_FORMAT_PCM) {
        MessageBox(nullptr, TEXT("WaveData: PCM�f�[�^�ł͂���܂���D"), nullptr, MB_ICONWARNING);
        ret = false;
        goto cleanup;
    }

    // data chunk �̓ǂݎ��
    mmckData.ckid = mmioStringToFOURCC(TEXT("data"), 0);
    if (mmioDescend(hMMIO, &mmckData, nullptr, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
        MessageBox(nullptr, TEXT("WaveData: data chunk ��ǂݎ��܂���ł����D"), nullptr, MB_ICONWARNING);
        ret = false;
        goto cleanup;
    }

    // mBuffer �� mmckData.cksize �o�C�g�m��
    tempBuffer.resize(mmckData.cksize);

    // WAVE �f�[�^�̃T�C�Y���f�[�^���擾
    mmioRead(hMMIO, reinterpret_cast<HPSTR>(&tempBuffer.front()), tempBuffer.size());

    // RIFF �t�@�C���� chunk ����ޏo
    mmioAscend(hMMIO, &mmckRiff, 0);

    mDataBuffer = tempBuffer; 
    mDataSize = mmckData.cksize;

cleanup:
    mmioClose(hMMIO, 0);
    return ret;
}
