// CSVFile.h

#pragma once

#include <fstream>
#include <vector>
#include <string>


class CSVFile {

public:
    CSVFile();
    virtual ~CSVFile();

    bool Open(const std::string& filePath);

private:
    void reserveFields();

private:
    std::ifstream mIfstream;
    std::vector<std::string> mFields; // �X�̃f�[�^
};