// FPSCounter.cpp

// Includes
#include "FPSCounter.h"


FPSCounter::FPSCounter() : mCurrentFPS(0.0),
                           mDeltaFreq(0.0),
                           mPerformanceCount(),
                           mLongCount(0) {

    // 生成時のカウント数を保持
    QueryPerformanceCounter(&mPerformanceCount);
    mLongCount = mPerformanceCount.QuadPart;

    // 1秒当たり周波数を取得
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    mDeltaFreq = static_cast<double>(freq.QuadPart); 
}


FPSCounter::~FPSCounter() {
    // empty
}


void FPSCounter::CountFPS() {
    double def = getCurDefTime();

    if (def <= 0) {
        mCurrentFPS = 0;
        return;
    }

    mCurrentFPS = (1000.0 / def);
}


double FPSCounter::getCurDefTime() {

    // 現在の時刻を取得
    QueryPerformanceCounter(&mPerformanceCount);

    // 差分カウント数を算出する
    double def = static_cast<double>(mPerformanceCount.QuadPart - mLongCount);
    
    // 現在の時刻を保持
    mLongCount = mPerformanceCount.QuadPart;

    // 差分時間をミリ秒単位で返す
    return ((def * 1000) / mDeltaFreq);
}
