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
    double mCurrentFPS; 

    double mDeltaFreq; // 1秒当たりクロック数
    LARGE_INTEGER mCounter;
    LONGLONG mOldLongCount;

    double getCurDefTime(); // 差分時間を計測する関数

};
