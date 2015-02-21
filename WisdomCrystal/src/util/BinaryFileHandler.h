// BinaryFileHandler.h

#pragma once

#include <iostream>
#include <memory>
#include <array>
#include <fstream>
#include <sstream>

namespace Util {
namespace BinaryFileHandler {

// CSV �t�@�C����ǂݍ���
template<typename T>
bool ImportData(const std::string& filePath, T *container);

// CSV �t�@�C���֏�������
template<typename T>
bool ExportData(const std::string& filePath, T *container);

} // namespace BinaryFileHandler
} // namespace Util


namespace Util {

template<typename T>
bool BinaryFileHandler::ImportData(const std::string& filePath, T* container) {
    std::ifstream ifs(filePath, std::ios::in | std::ios::binary);
    if (ifs.fail()) {
        return false; // �t�@�C���̓ǂݍ��݂Ɏ��s
    }
    int index = 0;
    int readData = 0;

    try {
        while(ifs.eof() == false){  //�t�@�C���̍Ō�܂ő�����
            ifs.read( ( char * ) &readData, sizeof( int ) );
              //������ł͂Ȃ��f�[�^��ǂ݂���
           container->at(index) = readData;
           ++index;
        }

    } catch (const std::out_of_range&) {
        return false; // �͈͊O�A�N�Z�X����
    }
    return true;
}



template<typename T>
bool BinaryFileHandler::ExportData(const std::string& fileName, T* container) {
    std::ofstream ofs(fileName, std::ios::out | std::ios::binary | std::ios::trunc);
    if (ofs == false) {
        return false;
    }

    auto it = container->begin();
    while (it != (container->end())) {
        ofs.write(reinterpret_cast<char *>(&(*it)), sizeof(*it));
        ++it;
    }

    if (ofs.fail()) {
        return false;
    }

    return true;
}

} // namespace Util