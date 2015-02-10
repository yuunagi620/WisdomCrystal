// CSVUtilImpl.h

#pragma once

#include <memory>
#include <array>
#include <fstream>
#include <sstream>


namespace CSVUtil {

template<typename T>
bool ImportData(const std::string& filePath, T* data) {
    std::ifstream ifs(filePath);
    if (ifs.fail()) {
        return false; // �t�@�C���̓ǂݍ��݂Ɏ��s
    }

    int index = 0;
    std::string lineStr;

    try {

        // ��������s�P�ʂŒ��o
        while (getline(ifs, lineStr)) {
            std::string token;
            std::istringstream stream(lineStr);

            // ��������R���}�P�ʂŒ��o
            while (getline(stream, token, ',')) {
                data->at(index) = (std::atoi(token.c_str()));
                ++index;
            }
        }

    } catch (const std::out_of_range&) {
        return false; // �͈͊O�A�N�Z�X����
    }
    return true;
}


template<typename T>
bool ExportData(const std::string& fileName, T* data) {
    std::ofstream ofs(fileName);

    auto it = data->begin();
    while (it != (data->end() - 1)) {
        ofs << (*it) << ",";
        ++it;
    }
    ofs << (*it) << std::endl; // �Ō�̓R���}�����Ȃ��悤�ɂ���

    if (ofs.fail()) {
        return false;
    }

    return true;
}


} // namespace CSVUtil
