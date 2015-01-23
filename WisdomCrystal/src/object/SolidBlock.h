// SolidBlock.h

#pragma once

#include "object/GameObject.h"


class SolidBlock : public GameObject {

public:
    SolidBlock();

    static SolidBlock *Activate(int initX, int initY, int objID);

    bool Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) override;
    void Cleanup() override;
    void Update() override;
    void Deactivate() override {};

    inline bool IsAlive() const {
        return mIsAlive;
    }

private:
    static const int MAX_SOLID_BLOCK;
    static const int MAP_CHIP_WIDTH;
    static const int MAP_CHIP_HEIGHT;
    static const int MAP_CHIP_IMAGE_COL;

    D2D1_RECT_F getRectF();
    RECT getHitRect();
    void changeImage(int index);

    static std::vector<SolidBlock> mSolidBlock;

    static ID2D1Bitmap *mImage;
    D2D1_RECT_F mImageSrcRect;

    GraphicsDevice* mGraphicsDevice;
    SoundDevice* mSoundDevice;

    bool mIsAlive;
    int mX, mY;
};
