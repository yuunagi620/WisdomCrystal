// FPSCounter.h

#pragma once

#include <windows.h>
#include <mmsystem.h>


class FPSCounter {

public:
    FPSCounter();
    virtual ~FPSCounter();

    void CountFPS();

    inline double GetFPS() const {
        return mCurrentFPS;
    };

private:
    // �������Ԃ��v������
    double getCurDefTime();

    double mCurrentFPS; 
    double mDeltaFreq; // 1�b������N���b�N��
    LARGE_INTEGER mPerformanceCount;
    LONGLONG mLongCount;
};
