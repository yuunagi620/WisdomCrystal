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

    // �t�@�C���̓ǂݍ���
    std::ifstream ifs(mWaveFilePath, std::ios::in | std::ios::binary);
    if (ifs == false) {
        MessageBox(nullptr, TEXT("WaveFile: �t�@�C���̃I�[�v���Ɏ��s�D"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // 4�o�C�g��ǂݍ���� RIFE �w�b�_���ǂ����𒲂ׂ�
    const char riff[4] = {'R', 'I', 'F', 'F'};
    char readData[4];  
    ifs.read(readData, sizeof(readData));
    if (std::memcmp(riff, readData, sizeof(riff))) {
        MessageBox(nullptr, TEXT("WaveFile: RIFE�`�����N�����݂��܂���ł����D"), TEXT("ERROR"), MB_OK);
        return false;
    } 

    // �t�@�C���T�C�Y����4�o�C�g�ǂݔ�΂�
    ifs.ignore(4);

    // 4�o�C�g��ǂݍ���� WAVE �w�b�_���ǂ����𒲂ׂ�
    const char wave[4] = {'W', 'A', 'V', 'E'};

    ifs.read(readData, sizeof(readData));
    if (std::memcmp(wave, readData, sizeof(wave))) {
        MessageBox(nullptr, TEXT("WaveFile: WAVE�`�����N�����݂��܂���ł����D"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // 4�o�C�g��ǂݍ���� fmt �`�����N���ǂ����𒲂ׂ�
    const char fmt[4] = {'f', 'm', 't', ' '};
    ifs.read(readData, sizeof(readData));
    if (std::memcmp(fmt, readData, sizeof(fmt))) {
        MessageBox(nullptr, TEXT("WaveFile: WAVE�`�����N�����݂��܂���ł����D"), TEXT("ERROR"), MB_OK);
        return false;
    } 

    // �t�H�[�}�b�g�T�C�Y�̓ǂݍ���
    std::uint32_t formatSize;
    ifs.read(reinterpret_cast<char *>(&formatSize), sizeof(formatSize));

    // �t�H�[�}�b�gID�̓ǂݍ���
    std::uint16_t id;
    ifs.read(reinterpret_cast<char *>(&id), sizeof(id));

    //  �t�H�[�}�b�gID����Ή����Ă���`�������ׂ�
    if (id == 1) {
        mFormat.wFormatTag = WAVE_FORMAT_PCM; // ���j�APCM
    } else if (id == 2) {
        mFormat.wFormatTag = WAVE_FORMAT_ADPCM; // MS ADPCM 
    } else {
        MessageBox(nullptr, TEXT("WaveFile: ���̃t�H�[�}�b�g�ɂ͑Ή����Ă��܂���D"), TEXT("ERROR"), MB_OK);
        return false;
    }

    // �`�����l�����̓ǂݍ���
    ifs.read(reinterpret_cast<char *>(&mFormat.nChannels), sizeof(mFormat.nChannels));

    // �T���v�����[�g�̓ǂݍ���
    ifs.read(reinterpret_cast<char *>(&mFormat.nSamplesPerSec), sizeof(mFormat.nSamplesPerSec));

    // �f�[�^���x (Byte/sec)�̓ǂݍ���
    ifs.read(reinterpret_cast<char *>(&mFormat.nAvgBytesPerSec), sizeof(mFormat.nAvgBytesPerSec));

    // �u���b�N�T�C�Y(Byte/sample�~�`�����l����)�̓ǂݍ���
    ifs.read(reinterpret_cast<char *>(&mFormat.nBlockAlign), sizeof(mFormat.nBlockAlign));

    // �T���v��������̃r�b�g���̓ǂݍ���
    ifs.read(reinterpret_cast<char *>(&mFormat.wBitsPerSample), sizeof(mFormat.wBitsPerSample));

    // �g���w�b�_����ǂݔ�΂�
    ifs.ignore(formatSize - 16);

    // 4�o�C�g��ǂݍ���� data �`�����N���ǂ����𒲂ׂ�
    const char data[4] = {'d', 'a', 't', 'a'};
    ifs.read(readData, sizeof(readData));
    if (std::memcmp(data, readData, sizeof(data))) {
        MessageBox(nullptr, TEXT("WaveFile: data�`�����N�����݂��܂���ł����D"), TEXT("ERROR"), MB_OK);
        return false;
    } 

    // �g�`�f�[�^�̃o�C�g���̓ǂݍ���
    std::uint32_t size;
    ifs.read(reinterpret_cast<char *>(&size), sizeof(size));


    // �g�`�f�[�^�̓ǂݍ���
    mBuffer.resize(size);
    ifs.read(reinterpret_cast<char *>(&mBuffer.front()), size);

    return true;
}