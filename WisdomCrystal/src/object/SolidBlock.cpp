// SolidBlock.cpp

// Includes
#include "SolidBlock.h"


// Constants
const int SolidBlock::MAX_SOLID_BLOCK = 880;
const int SolidBlock::MAP_CHIP_WIDTH  = 32;
const int SolidBlock::MAP_CHIP_HEIGHT = 32;
const int SolidBlock::MAP_CHIP_IMAGE_COL = 10;

// Static member variables
std::vector<SolidBlock> SolidBlock::mSolidBlock(MAX_SOLID_BLOCK);

ID2D1Bitmap             *SolidBlock::mImage = nullptr;

SolidBlock::SolidBlock() : mIsAlive(false),
                           mX(0),
                           mY(0),
                           mImageSrcRect()
{
    // empty
}


SolidBlock *SolidBlock::Activate(int initX, int initY, int objID) {

    for (auto it = mSolidBlock.begin(); it != mSolidBlock.end(); it++) {
        if (it->IsAlive() == false) {

            it->mX = initX;
            it->mY = initY;
            it->mIsAlive = true;

            it->changeImage(objID);
            return &(*it);
        }
    }

    return nullptr;
}


bool SolidBlock::Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) {
    mGraphicsDevice = graphicsDevice;
    mSoundDevice = soundDevice;

    // ˆÈ‰ºA‰æ‘œ‚Ì“Ç‚Ýž‚Ý
    mImage = mGraphicsDevice->CreateD2DBitmap(TEXT("resources/image/MapChip.png"));
    if (mImage == nullptr) {
        return false;
    }

    changeImage(0);

    return true;
}


void SolidBlock::Cleanup() {
    // empty
}


void SolidBlock::Update() {
    
    if (mIsAlive == false) {
        return;
    }

    mGraphicsDevice->DrawBitmap(mImage, getRectF(), 1, mImageSrcRect);
}


D2D1_RECT_F SolidBlock::getRectF() {
    return D2D1::RectF(static_cast<float>(mX),
                       static_cast<float>(mY),
                       static_cast<float>(mX) + MAP_CHIP_WIDTH,
                       static_cast<float>(mY) + MAP_CHIP_HEIGHT);
}


RECT SolidBlock::getHitRect() {
    RECT rect = {
        mX,
        mY,
        mX + MAP_CHIP_WIDTH,
        mY + MAP_CHIP_HEIGHT
    };

    return rect;
}


void SolidBlock::changeImage(int index) {
    mImageSrcRect =
        D2D1::RectF(static_cast<float>((index % MAP_CHIP_IMAGE_COL)     * MAP_CHIP_WIDTH),
                    static_cast<float>((index / MAP_CHIP_IMAGE_COL)     * MAP_CHIP_HEIGHT),
                    static_cast<float>((index % MAP_CHIP_IMAGE_COL + 1) * MAP_CHIP_WIDTH),
                    static_cast<float>((index / MAP_CHIP_IMAGE_COL + 1) * MAP_CHIP_HEIGHT));
}

