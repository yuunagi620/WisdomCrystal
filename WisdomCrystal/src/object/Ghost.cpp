// Ghost.cpp

#include "Ghost.h"
#include "win/util/Input.h"


Ghost::Ghost() : mCanvas(),
                 mSoundDevice(nullptr),
                 mImage(),
                 mX(600),
                 mY(400),
                 mIsAlive(false)
{
    // empty
}


Ghost::~Ghost() {
    // empty
}


bool Ghost::Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) {
    mCanvas.Init(graphicsDevice);
    mSoundDevice = soundDevice;

    if (mImage.Init(graphicsDevice, TEXT("resources/image/ghost.png")) == false) {
        return false;
    }

    return true;
}


bool Ghost::Activate(const int initX, const int initY) {
    if (GetIsAlive()) {
        return false;
    }
    mX = initX;
    mY = initY;

    SetIsAlive(true);
    return true;
}


void Ghost::Update() {
    mImage.Draw(mX, mY);
}
