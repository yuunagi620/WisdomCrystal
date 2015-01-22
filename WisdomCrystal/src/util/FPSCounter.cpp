// FPSCounter.cpp

// Includes
#include "FPSCounter.h"


FPSCounter::FPSCounter() : mCurrentFPS(0.0),
                           mDeltaFreq(0.0),
                           mCounter(),
                           mOldLongCount(0) {

    QueryPerformanceCounter(&mCounter);
    mOldLongCount = mCounter.QuadPart; // 生成時の時刻（クロック数）を取得

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq); // 1秒当たりクロック数を取得
    mDeltaFreq = static_cast<double>(freq.QuadPart);

}


FPSCounter::~FPSCounter() {
    // empty
}


void FPSCounter::CountFPS() {

    double def = getCurDefTime();

    if (def == 0) {
        mCurrentFPS = 0;
        return;
    }

    mCurrentFPS = (1000.0 / def);
}


double FPSCounter::getCurDefTime() {

    double ret;

    // 現在の時刻を取得
    QueryPerformanceCounter(&mCounter);

    // 差分カウント数を算出する
    double def = static_cast<double>(mCounter.QuadPart - mOldLongCount);
    
    // 現在の時刻を保持
    mOldLongCount = mCounter.QuadPart;

    // 差分時間をミリ秒単位で返す
    ret = (def * 1000) / mDeltaFreq;

    return ret;
}
