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
        throw std::runtime_error("�t�@�C�����J���̂Ɏ��s");
    }
    const char riff[4] = {'R', 'I', 'F', 'F'};
    char read_data[4];
    // �w�b�_�̓�����4�o�C�g��ǂݍ����"RIFE"���ǂ����𒲂ׂ�
    fin.read(read_data, sizeof(read_data));
    if (std::memcmp(riff, read_data, sizeof(riff))) {
        throw std::runtime_error("RIFE�`�����N�����݂��Ȃ�");
    } 
    // 4�o�C�g�ǂݔ�΂�
    fin.ignore(4);
    const char wave[4] = {'W', 'A', 'V', 'E'};
    // �����Ă�4�o�C�g��ǂݍ����"WAVE"���ǂ����𒲂ׂ�
    fin.read(read_data, sizeof(read_data));
    if (std::memcmp(wave, read_data, sizeof(wave))) {
	throw std::runtime_error("WAVE�`�����N�����݂��Ȃ�");
    } 
    // �����Ă�4�o�C�g��ǂݍ����"fmt "���ǂ����𒲂ׂ�
    const char fmt[4] = {'f', 'm', 't', ' '};
    fin.read(read_data, sizeof(read_data));
    if (std::memcmp(fmt, read_data, sizeof(fmt))) {
	throw std::runtime_error("fmt �`�����N�����݂��Ȃ�");
    } 
    std::uint32_t format_size;
    // �t�H�[�}�b�g�T�C�Y�ǂݍ���
    fin.read(reinterpret_cast<char *>(&format_size), sizeof(format_size));
    std::uint16_t id;
    // �t�H�[�}�b�g�^�OID�̓ǂݍ���
    fin.read(reinterpret_cast<char *>(&id), sizeof(id));
    // ID�ɑΉ�����t�H�[�}�b�g�ɂ���
    switch (id) {
    case 1:
	mFormat.wFormatTag = WAVE_FORMAT_PCM;
	break;
    case 2:
	mFormat.wFormatTag = WAVE_FORMAT_ADPCM;
	break;
    default:
	throw std::runtime_error("�Ή����Ă��Ȃ��t�H�[�}�b�g");
    }
    // �`�����l������ǂݍ���
    fin.read(reinterpret_cast<char *>(&mFormat.nChannels), sizeof(mFormat.nChannels));
    // �T���v�����[�g��ǂݍ���
    fin.read(reinterpret_cast<char *>(&mFormat.nSamplesPerSec), sizeof(mFormat.nSamplesPerSec));
    // �f�[�^���x��ǂݍ���
    fin.read(reinterpret_cast<char *>(&mFormat.nAvgBytesPerSec), sizeof(mFormat.nAvgBytesPerSec));
    // �u���b�N�T�C�Y��ǂݍ���
    fin.read(reinterpret_cast<char *>(&mFormat.nBlockAlign), sizeof(mFormat.nBlockAlign));
    // �T���v��������̃r�b�g����ǂݍ���
    fin.read(reinterpret_cast<char *>(&mFormat.wBitsPerSample), sizeof(mFormat.wBitsPerSample));
    // �g���w�b�_����ǂݔ�΂�
    fin.ignore(format_size - 16);

    const char data[4] = {'d', 'a', 't', 'a'};
    // �����Ă�4�o�C�g��ǂݍ����"data"���ǂ����𒲂ׂ�
    fin.read(read_data, sizeof(read_data));
    if (std::memcmp(data, read_data, sizeof(data))) {
	    throw std::runtime_error("data�`�����N�����݂��Ȃ�");
    } 
    std::uint32_t size;
    // �g�`�f�[�^�̃T�C�Y��ǂݍ���
    fin.read(reinterpret_cast<char *>(&size), sizeof(size));
    mBuffer.resize(size);
    // �g�`�f�[�^�ǂݍ���
    fin.read(reinterpret_cast<char *>(&mBuffer.front()), size);

    return true;
}