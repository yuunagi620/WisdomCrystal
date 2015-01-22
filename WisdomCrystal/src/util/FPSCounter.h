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
    // 差分時間を計測する
    double getCurDefTime();

    double mCurrentFPS; 
    double mDeltaFreq; // 1秒当たりクロック数
    LARGE_INTEGER mPerformanceCount;
    LONGLONG mLongCount;
};
