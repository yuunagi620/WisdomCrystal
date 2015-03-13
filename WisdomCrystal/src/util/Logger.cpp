// Logger.cpp

#include <iomanip>
#include <array>

#include "Logger.h"
#include "Month.h"


namespace Util {

Logger::Logger(const std::string& fileName) : mOfstream(fileName, std::ios::app) {
    // empty
}


Logger::~Logger() {
    // empty
}


bool Logger::Write(const std::string& msg) {
    SYSTEMTIME st;
    GetLocalTime(&st);


    mOfstream << "[";
    mOfstream << std::setfill('0') << std::setw(2) << std::to_string(st.wDay)    << "/";
    mOfstream << Month::ToEnglishMonthName(st.wMonth)                            << "/";
    mOfstream << std::setfill('0') << std::setw(4) << std::to_string(st.wYear)   << ":";
    mOfstream << std::setfill('0') << std::setw(2) << std::to_string(st.wHour)   << ":";
    mOfstream << std::setfill('0') << std::setw(2) << std::to_string(st.wMinute) << ":";
    mOfstream << std::setfill('0') << std::setw(2) << std::to_string(st.wSecond) << " ";
    mOfstream << "+0900";
    mOfstream << "]";

    mOfstream << msg << std::endl;

    if (mOfstream.fail()) {
        return false;
    }

    return true;
}

} // namespace Util
