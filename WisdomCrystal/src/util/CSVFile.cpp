// CSVFile.cpp

#include <sstream>

#include "CSVFile.h"


namespace Util {

CSVFile::CSVFile() : mIfstream()
{
    // empty
}


CSVFile::~CSVFile() {
    // empty
}


bool CSVFile::Open(const std::string& filePath) {
    mIfstream.open(filePath);
    if (mIfstream.fail()) {
        return false;
    }

    reserveFields();

    std::string field;
    while (mIfstream.good()) {
         getline(mIfstream, field, ',');
         mFields.push_back(std::string(field, 0, field.length()));
    }
    return true;
}


void CSVFile::reserveFields() {
    int fieldNum = 1;
    const char comma = {','};
    char readData;
    while (mIfstream.read(&readData, sizeof(readData))) {
        if (std::memcmp(&comma, &readData, sizeof(comma)) == false) {
            ++fieldNum;
        }
    }

    // ファイルポインタを先頭へ移動
    mIfstream.clear();
    mIfstream.seekg(0, std::ios_base::beg);

    mFields.reserve(fieldNum);
}

} // namespace Util