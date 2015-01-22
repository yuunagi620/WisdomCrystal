// FPSCounter.cpp

// Includes
#include "FPSCounter.h"


FPSCounter::FPSCounter() : mCurrentFPS(0.0),
                           mDeltaFreq(0.0),
                           mPerformanceCount(),
                           mLongCount(0) {

    // �������̃J�E���g����ێ�
    QueryPerformanceCounter(&mPerformanceCount);
    mLongCount = mPerformanceCount.QuadPart;

    // 1�b��������g�����擾
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

    // ���݂̎������擾
    QueryPerformanceCounter(&mPerformanceCount);

    // �����J�E���g�����Z�o����
    double def = static_cast<double>(mPerformanceCount.QuadPart - mLongCount);
    
    // ���݂̎�����ێ�
    mLongCount = mPerformanceCount.QuadPart;

    // �������Ԃ��~���b�P�ʂŕԂ�
    return ((def * 1000) / mDeltaFreq);
}
