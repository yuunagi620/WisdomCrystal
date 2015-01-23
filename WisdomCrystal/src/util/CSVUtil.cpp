// CSVUtil.cpp

// Includes
#include "CSVUtil.h"

#include<fstream>
#include<sstream>



// Using namespace
using namespace std;


bool CSVUtil::ImportCSVData(string filePath, array<int, 880>* a) {

    ifstream ifs(filePath);
    if (ifs.fail()) {
        return false; // ƒtƒ@ƒCƒ‹‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s
    }

    int index = 0;
    string lineStr;
    while (getline(ifs, lineStr)) {
        string token;
        istringstream stream(lineStr);

        while (getline(stream, token, ',')) {
            a->at(index) = (atoi(token.c_str()));
            ++index;
        }
    }

    return true;
} 

