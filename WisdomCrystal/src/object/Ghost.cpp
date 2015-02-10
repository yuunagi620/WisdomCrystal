// Ghost.cpp

#include "Ghost.h"
#include "win/util/Input.h"


Ghost::Ghost() : mGraphicsDevice(nullptr),
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
    mGraphicsDevice = graphicsDevice;
    mSoundDevice = soundDevice;

    if (mImage.Init(mGraphicsDevice, TEXT("resources/image/ghost.png")) == false) {
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
