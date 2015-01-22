// BackGround.cpp

// Includes
#include "BackGround.h"

#pragma warning (disable: 4005) // C4005 Œx–³‹
#include <boost/lexical_cast.hpp>
#pragma warning (default: 4005) // C4005 Œx‰ğœ

// Constants
const std::basic_string<TCHAR> BackGround::IMAGE_PATH         = TEXT("resources/image/");
const std::basic_string<TCHAR> BackGround::FILENAME           = TEXT("backGround_");
const std::basic_string<TCHAR> BackGround::FILENAME_EXTENSION = TEXT(".jpg");


BackGround::BackGround() : mImageID(0),
                           mImageSize(), 
                           mImageSrcRect(),
                           mImage(nullptr) {

    mImagePath.clear();
}


BackGround::~BackGround() {
    // empty
}


bool BackGround::Init(GraphicsDevice* graphicsDevice, const int backGroundIndex) {
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


// ”wŒi‰æ‘œ‚Ì•ÏX
bool BackGround::ChangeBackGroundImage(const int index) {
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
    mImagePath += IMAGE_PATH;
    mImagePath += FILENAME;
    mImagePath += boost::lexical_cast<TCHAR>(mImageID);
    mImagePath += FILENAME_EXTENSION;
}


// ”wŒi‰æ‘œ‚Ìİ’è
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
