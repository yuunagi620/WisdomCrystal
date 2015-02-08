// BackGround.cpp

// Includes
#include "BackGround.h"

#pragma warning (disable: 4005) // C4005 �x������
#include <boost/lexical_cast.hpp>
#pragma warning (default: 4005) // C4005 �x������


BackGround::BackGround() : mGraphicsDevice(nullptr),
                           mImageID(0),
                           mImagePath(),
                           mImageSize(), 
                           mImageSrcRect(),
                           mImage(nullptr) {

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
    mGraphicsDevice->DrawBitmap(mImage, getRectF(), 1, mImageSrcRect);
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

    mImage = mGraphicsDevice->CreateD2DBitmap(&mImagePath.front());
    if (mImage == nullptr) {
        return false;
    }

    mImageSize = mImage->GetPixelSize();
    mImageSrcRect = getRectF();

    return true;
}


D2D1_RECT_F BackGround::getRectF() {
    return D2D1::RectF(0,
                       0,
                       static_cast<float>(mImageSize.width), 
                       static_cast<float>(mImageSize.height));
}
