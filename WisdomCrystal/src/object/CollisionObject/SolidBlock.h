// SolidBlock.h

#pragma once

#include "CollisionObject.h"


class SolidBlock : public CollisionObject {

public:
    SolidBlock();

    static SolidBlock *Activate(int initX, int initY, int objID);

    bool Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) override;
    void Cleanup() override;
    void Update() override;
    void Deactivate() override {};

    CollisionData CollisionDetection(const CollisionRectData& rectData);

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
