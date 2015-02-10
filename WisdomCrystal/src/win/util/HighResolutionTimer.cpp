// HighResolutionTimer.cpp

#include "HighResolutionTimer.h"


HighResolutionTimer::HighResolutionTimer(const double interval) : mOldCount(),
                                                                  mNowCount(),
                                                                  mStepCount()
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    mStepCount = (static_cast<double>(freq.LowPart) * interval);
    QueryPerformanceCounter(&mOldCount);
}


HighResolutionTimer::~HighResolutionTimer() {
    // empty
}


bool HighResolutionTimer::Elapsed() {
    QueryPerformanceCounter(&mNowCount);

    if ((mNowCount.LowPart - mOldCount.LowPart) >= mStepCount) {
        mOldCount = mNowCount;
        return true;
    } 

    return false;
}
