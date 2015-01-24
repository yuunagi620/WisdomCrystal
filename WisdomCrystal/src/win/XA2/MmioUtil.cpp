// MmioUtil.cpp

// Includes
#include "MmioUtil.h"


bool MmioUtil::ReadWaveFile(WAVEFORMATEX *WaveFormatEX,
                            std::shared_ptr<BYTE> *DataBodyAddress,
                            DWORD *DataSize,
                            TCHAR* WaveFilePath) {
    HMMIO hMMIO;
    MMCKINFO mmckRiff;
    MMCKINFO mmckFormat;
    MMCKINFO mmckData;

    std::shared_ptr<BYTE> dataBuffer;

    bool ret = true;

    // �t�@�C���̃I�[�v��
    hMMIO = mmioOpen(WaveFilePath, nullptr, MMIO_READ);
    if (hMMIO == nullptr) {
        MessageBox(nullptr, TEXT("readWaveFile: �t�@�C���̃I�[�v���Ɏ��s���܂����B"), nullptr, MB_ICONWARNING);
        return false;
    }

    // �t�@�C���� WAVE �`�����ǂ�������
    mmckRiff.fccType = mmioStringToFOURCC(TEXT("WAVE"), 0);
    if (mmioDescend(hMMIO, &mmckRiff, nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR) {
        MessageBox(nullptr, TEXT("readWaveFile: WAVE�t�@�C���ł͂���܂���B"), nullptr, MB_ICONWARNING);
        ret = false;
        goto onError;
    }

    // 'fmt ' chunk �̓ǂݎ��
    mmckFormat.ckid = mmioStringToFOURCC(TEXT("fmt "), 0); // 'fmt '��4�����ڂ͋�
    if (mmioDescend(hMMIO, &mmckFormat, nullptr, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
        MessageBox(nullptr, TEXT("readWaveFile: �����ȃt�@�C���ł��B(no 'fmt ' chunk)"), nullptr, MB_ICONWARNING);
        ret = false;
        goto onError;
    }

    // PCM �f�[�^���ǂ�������
    mmioRead(hMMIO, reinterpret_cast<HPSTR>(WaveFormatEX), mmckFormat.cksize);
    mmioAscend(hMMIO, &mmckFormat, 0);
    if (WaveFormatEX->wFormatTag != WAVE_FORMAT_PCM) {
        MessageBox(nullptr, TEXT("readWaveFile: PCM�f�[�^�ł͂���܂���B"), nullptr, MB_ICONWARNING);
        ret = false;
        goto onError;
    }

    // data chunk �̓ǂݎ��
    mmckData.ckid = mmioStringToFOURCC(TEXT("data"), 0);
    if (mmioDescend(hMMIO, &mmckData, nullptr, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
        MessageBox(nullptr, TEXT("readWaveFile: data chunk ��ǂݎ��܂���ł����B"), nullptr, MB_ICONWARNING);
        ret = false;
        goto onError;
    }

    // mBuffer �� mmckData.cksize �o�C�g�m��
    dataBuffer.reset(new BYTE[mmckData.cksize], std::default_delete<BYTE[]>());

    // WAVE �f�[�^�̃T�C�Y���f�[�^���擾
    mmioRead(hMMIO, reinterpret_cast<HPSTR>(dataBuffer.get()), mmckData.cksize);

    // RIFF �t�@�C���� chunk ����ޏo
    mmioAscend(hMMIO, &mmckRiff, 0);

    // ���̊֐��œ��� data �� size ��Ԃ�
    *DataBodyAddress = dataBuffer; 
    *DataSize = mmckData.cksize;

onError:
    mmioClose(hMMIO, 0);
    return ret;
}
