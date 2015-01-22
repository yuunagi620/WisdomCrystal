// HighResolutionTimer.h

#pragma once

#include <Windows.h>


class HighResolutionTimer {

public:
    explicit HighResolutionTimer(const double interval);
    virtual ~HighResolutionTimer();

    // タイマが経過したか調べる
    bool Elapsed();

private:
    LARGE_INTEGER mOldCount;
    LARGE_INTEGER mNowCount;

    double mStepCount; 
};
