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
        return false; // ファイルの読み込みに失敗
    }

    int index = 0;
    string lineStr;

    try {

        // 文字列を行単位で抽出
        while (getline(ifs, lineStr)) {
            string token;
            istringstream stream(lineStr);

            // 文字列をコンマ単位で抽出
            while (getline(stream, token, ',')) {
                arr->at(index) = (atoi(token.c_str()));
                ++index;
            }
        }

    } catch (const std::out_of_range&) {
        return false; // 範囲外アクセスした
    }

    return true;
} 

} // namespace CSVUtil
