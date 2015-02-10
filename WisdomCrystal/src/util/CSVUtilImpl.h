// CSVUtilImpl.h

#pragma once

#include <memory>
#include <array>
#include <fstream>
#include <sstream>


namespace CSVUtil {

template<typename T>
bool ImportCSVData(const std::string& filePath, T* arr) {

    auto deleter = [](std::ifstream *ifs){
        ifs->close();
    };

    std::ifstream ifs(filePath);
    std::unique_ptr<std::ifstream, decltype(deleter)> ptr(&ifs, deleter);
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
                arr->at(index) = (std::atoi(token.c_str()));
                ++index;
            }
        }

    } catch (const std::out_of_range&) {
        return false; // �͈͊O�A�N�Z�X����
    }
    return true;
} 

} // namespace CSVUtil
