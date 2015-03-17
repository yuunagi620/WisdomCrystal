// BackGround.cpp

#include <string>

#include "BackGround.h"


BackGround::BackGround() : mGraphicsDevice(nullptr), mImageID(0), mImage() {
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


bool BackGround::ChangeBackGroundImage(int imageID) {
    mImageID = imageID;
    std::basic_string<TCHAR> imagePath = 
        TEXT("resources/image/backGround_") + std::to_wstring(mImageID) + TEXT(".jpg");

    if (mImage.Init(mGraphicsDevice, &imagePath.front()) == false) {
        return false;
    }

    return true;
}
