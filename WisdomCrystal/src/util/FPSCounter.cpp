// FPSCounter.cpp

// Includes
#include "FPSCounter.h"


FPSCounter::FPSCounter() : mCurrentFPS(0.0),
                           mDeltaFreq(0.0),
                           mCounter(),
                           mOldLongCount(0) {

    QueryPerformanceCounter(&mCounter);
    mOldLongCount = mCounter.QuadPart; // �������̎����i�N���b�N���j���擾

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq); // 1�b������N���b�N�����擾
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

    // ���݂̎������擾
    QueryPerformanceCounter(&mCounter);

    // �����J�E���g�����Z�o����
    double def = static_cast<double>(mCounter.QuadPart - mOldLongCount);
    
    // ���݂̎�����ێ�
    mOldLongCount = mCounter.QuadPart;

    // �������Ԃ��~���b�P�ʂŕԂ�
    ret = (def * 1000) / mDeltaFreq;

    return ret;
}
