// BackGround.cpp

#include "BackGround.h"

#pragma warning (disable: 4005) // C4005 �x������
#include <boost/lexical_cast.hpp>
#pragma warning (default: 4005) // C4005 �x������


BackGround::BackGround() : mGraphicsDevice(nullptr),
                           mImageID(0),
                           mImagePath(),
                           mImage()
{
    mImagePath.clear();
}


BackGround::~BackGround() {
    // empty
}


bool BackGround::Init(GraphicsDevice *graphicsDevice, const int backGroundIndex) {
    mGraphicsDevice = graphicsDevice;
    mImageID = backGroundIndex;

    changeImagePath();
    if (setBackGroundImage() == false) {
        return false;
    }

    return true;
}


void BackGround::Draw() {
    D2D1_COLOR_F fillColor = D2D1::ColorF(0x000000); // black
    mGraphicsDevice->ClearScreen(fillColor);
    mImage.Draw(0, 0);
}


// �w�i�摜�̕ύX
bool BackGround::ChangeBackGroundImage(const int index) {
    mImageID = index;

    changeImagePath();

    if (setBackGroundImage() == false) {
        return false;
    }

    return true;
}


//  �摜�̃p�X�̕ύX
void BackGround::changeImagePath() {
    mImagePath.clear();
    mImagePath += TEXT("resources/image/backGround_");
    mImagePath += boost::lexical_cast<TCHAR>(mImageID);
    mImagePath += TEXT(".jpg");
}


// �w�i�摜�̐ݒ�
bool BackGround::setBackGroundImage() {
    if (mImagePath.empty()) {
        return false;
    }

    if (mImage.Init(mGraphicsDevice, &mImagePath.front()) == false) {
        return false;
    }

    return true;
}
