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

    double mDeltaFreq; // 1�b������N���b�N��
    LARGE_INTEGER mCounter;
    LONGLONG mOldLongCount;

    double getCurDefTime(); // �������Ԃ��v������֐�

};
