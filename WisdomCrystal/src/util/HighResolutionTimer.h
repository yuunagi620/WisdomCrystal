// HighResolutionTimer.h

#pragma once

#include <Windows.h>

class HighResolutionTimer {

public:
    HighResolutionTimer(double interval);
    virtual ~HighResolutionTimer() {}

    bool Elapsed();

private:
    LARGE_INTEGER mFrep;
    LARGE_INTEGER mOldCount;
    LARGE_INTEGER mNowCount;

    double mStepCount; 

};
