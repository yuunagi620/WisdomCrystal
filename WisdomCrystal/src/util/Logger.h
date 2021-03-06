// Logger.h

#pragma once

#include <fstream>
#include <sstream>


class Logger {

public:
    Logger(const std::string& fileName);
    virtual ~Logger();

    bool Write(const std::string& msg);

private:
    void writeTimeLog();

private:
    std::ofstream mOfstream;
};
