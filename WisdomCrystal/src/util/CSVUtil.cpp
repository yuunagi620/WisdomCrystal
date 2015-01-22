// CSVUtil.cpp

// Includes
#include "CSVUtil.h"

#include<fstream>
#include<sstream>

// Using namespace
using namespace std;

bool CSVUtil::ImportCSVData(string filePath, vector<int> *vector) {

    ifstream ifs(filePath);
    if (ifs.fail()) {
        return false; // ƒtƒ@ƒCƒ‹‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s
    }

    string lineStr;
    while (getline(ifs, lineStr)) {
        string token;
        istringstream stream(lineStr);

        while (getline(stream, token, ',')) {
            vector->push_back(atoi(token.c_str()));
        }
    }

    return true;
} 

