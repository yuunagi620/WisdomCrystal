// BackGround.cpp

#include "BackGround.h"

#pragma warning (disable: 4005) // C4005 Œx–³‹
#include <boost/lexical_cast.hpp>
#pragma warning (default: 4005) // C4005 Œx‰ğœ


BackGround::BackGround()
    : mGraphicsDevice(nullptr)
    , mImagePath()
    , mImageID(0)
    , mImage() {
    mImagePath.clear();
}


BackGround::~BackGround() {
    // empty
}


bool BackGround::Init(GraphicsDevice *graphicsDevice, int backGroundIndex) {
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


// ”wŒi‰æ‘œ‚Ì•ÏX
bool BackGround::ChangeBackGroundImage(int index) {
    mImageID = index;
    changeImagePath();

    if (setBackGroundImage() == false) {
        return false;
    }

    return true;
}


//  ‰æ‘œ‚ÌƒpƒX‚Ì•ÏX
void BackGround::changeImagePath() {
    mImagePath.clear();
    mImagePath += TEXT("resources/image/backGround_");
    mImagePath += boost::lexical_cast<TCHAR>(mImageID);
    mImagePath += TEXT(".jpg");
}


// ”wŒi‰æ‘œ‚Ìİ’è
bool BackGround::setBackGroundImage() {
    if (mImagePath.empty()) {
        return false;
    }

    if (mImage.Init(mGraphicsDevice, &mImagePath.front()) == false) {
        return false;
    }

    return true;
}
