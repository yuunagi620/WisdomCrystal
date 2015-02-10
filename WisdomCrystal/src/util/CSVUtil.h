// CSVUtil.h

#pragma once

#include <array>
#include <fstream>
#include <sstream>


namespace CSVUtil {

template<typename T>
bool ImportCSVData(const std::string& filePath, T* arr) {

    using namespace std;

    ifstream ifs(filePath);
    if (ifs.fail()) {
        return false; // �t�@�C���̓ǂݍ��݂Ɏ��s
    }

    int index = 0;
    string lineStr;

    try {

        // ��������s�P�ʂŒ��o
        while (getline(ifs, lineStr)) {
            string token;
            istringstream stream(lineStr);

            // ��������R���}�P�ʂŒ��o
            while (getline(stream, token, ',')) {
                arr->at(index) = (atoi(token.c_str()));
                ++index;
            }
        }

    } catch (const std::out_of_range&) {
        return false; // �͈͊O�A�N�Z�X����
    }

    return true;
} 

} // namespace CSVUtil
