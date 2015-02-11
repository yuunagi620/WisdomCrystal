// CSVHandler.h

#pragma once

#include <memory>
#include <array>
#include <fstream>
#include <sstream>


namespace CSVHandler {

// CSV ファイルを読み込み
template<typename T>
bool ImportData(const std::string& filePath, T *container);

// CSV ファイルへ書き込み
template<typename T>
bool ExportData(const std::string& filePath, T *container);

} // namespace CSVHandler


template<typename T>
bool CSVHandler::ImportData(const std::string& filePath, T* container) {
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
                container->at(index) = (std::atoi(token.c_str()));
                ++index;
            }
        }

    } catch (const std::out_of_range&) {
        return false; // 範囲外アクセスした
    }
    return true;
}


template<typename T>
bool CSVHandler::ExportData(const std::string& fileName, T* container) {
    std::ofstream ofs(fileName);

    auto it = container->begin();
    while (it != (container->end() - 1)) {
        ofs << (*it) << ",";
        ++it;
    }
    ofs << (*it) << std::endl; // 最後はコンマを入れないようにする

    if (ofs.fail()) {
        return false;
    }

    return true;
}

