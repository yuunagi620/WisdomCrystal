// BackGround.cpp

#include "BackGround.h"


BackGround::BackGround()
    : mGraphicsDevice(nullptr)
    , mImagePath()
    , mImageID(0)
    , mImage() {
    // empty
}


BackGround::~BackGround() {
    // empty
}


bool BackGround::Init(GraphicsDevice *graphicsDevice, int backGroundIndex) {
    mGraphicsDevice = graphicsDevice;

    if (ChangeBackGroundImage(backGroundIndex) == false) {
        return false;
    }

    return true;
}


void BackGround::Draw() {
    mImage.Draw(0, 0);
}


bool BackGround::ChangeBackGroundImage(int index) {
    mImageID = index;
    mImagePath = TEXT("resources/image/backGround_") + std::to_wstring(mImageID) + TEXT(".jpg");

    if (mImage.Init(mGraphicsDevice, &mImagePath.front()) == false) {
        return false;
    }

    return true;
}
