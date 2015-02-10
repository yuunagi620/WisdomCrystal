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
        return false; // ファイルの読み込みに失敗
    }

    int index = 0;
    std::string lineStr;

    try {

        // 文字列を行単位で抽出
        while (getline(ifs, lineStr)) {
            std::string token;
            std::istringstream stream(lineStr);

            // 文字列をコンマ単位で抽出
            while (getline(stream, token, ',')) {
                data->at(index) = (std::atoi(token.c_str()));
                ++index;
            }
        }

    } catch (const std::out_of_range&) {
        return false; // 範囲外アクセスした
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
    ofs << (*it) << std::endl; // 最後はコンマを入れないようにする

    if (ofs.fail()) {
        return false;
    }

    return true;
}


} // namespace CSVUtil
