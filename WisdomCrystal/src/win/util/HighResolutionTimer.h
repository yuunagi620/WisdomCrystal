// HighResolutionTimer.h

#pragma once

#include <Windows.h>


class HighResolutionTimer {

public:
    explicit HighResolutionTimer(double interval);
    virtual ~HighResolutionTimer();

    // �^�C�}���o�߂��������ׂ�
    bool Elapsed();

private:
    LARGE_INTEGER mOldCount;
    LARGE_INTEGER mNowCount;
    double mStepCount; 
};
