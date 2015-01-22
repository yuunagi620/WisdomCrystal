// HighResolutionTimer.cpp

// Includes
#include "HighResolutionTimer.h"


HighResolutionTimer::HighResolutionTimer(double interval) : mFrep(),
                                                            mOldCount(),
                                                            mNowCount(),
                                                            mStepCount() {

    QueryPerformanceFrequency(&mFrep);
    mStepCount = static_cast<double>(mFrep.LowPart) * interval;
    QueryPerformanceCounter(&mOldCount);

}


bool HighResolutionTimer::Elapsed() {

    QueryPerformanceCounter(&mNowCount);

    if ((mNowCount.LowPart - mOldCount.LowPart) >= mStepCount) {
        mOldCount = mNowCount;
        return true;
    } else {
        return false;
    }

}
