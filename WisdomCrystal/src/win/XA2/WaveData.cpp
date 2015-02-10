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

    // mmckData.cksize �o�C�g���m��
    mDataBuffer.resize(mmckData.cksize);

    // WAVE �f�[�^�̃T�C�Y���f�[�^�� mDataBuffer �ɓǂݎ��
    if (mmioRead(hMMIO, reinterpret_cast<HPSTR>(&mDataBuffer.front()), mDataBuffer.size()) == -1) {
        MessageBox(nullptr, TEXT("WaveData: �f�[�^�̓ǂݎ��Ɏ��s���܂����D"), nullptr, MB_ICONWARNING);
        ret = false;
        goto cleanup;
    }

    // RIFF �t�@�C���� chunk ����ޏo
    mmioAscend(hMMIO, &mmckRiff, 0);

    mDataSize = mmckData.cksize;

cleanup:
    mmioClose(hMMIO, 0);
    return ret;
}
