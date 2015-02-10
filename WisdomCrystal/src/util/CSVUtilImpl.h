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
                arr->at(index) = (std::atoi(token.c_str()));
                ++index;
            }
        }

    } catch (const std::out_of_range&) {
        return false; // 範囲外アクセスした
    }
    return true;
} 

} // namespace CSVUtil
