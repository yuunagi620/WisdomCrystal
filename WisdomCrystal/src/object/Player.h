// Player.h

#pragma once

#include "GameObject.h"
#include "win/D2D/D2DTextData.h"

typedef enum PlayerStatusTag {
    NORMAL,
    WALK_1,
    WALK_2,
    JUMP,
    FALL,
    DEATH,
    PLAYER_STATUS_NUM
} PlayerStatus;


typedef enum PlayerSETag {
    SE_JUMP,
    SE_GAMEOVER,
    PLAYER_SE_NUM
} PlayerSE;


class Player : public GameObject {

public:
    Player();
    virtual ~Player();

    bool Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) override;
    void Update() override;

private:
    void draw();
    void gameOverAnimetion();
    void changeImage(const int index);
    D2D1_RECT_F getRectF();
    RECT getHitRect(const int dx, const int dy);

    void soundSE(PlayerSE playerSE);

private:
    static const int   PLAYER_IMAGE_WIDTH;
    static const int   PLAYER_IMAGE_HEIGHT;
    static const int   PLAYER_IMAGE_ROW;
    static const int   PLAYER_SPEED_X;
    static const float PLAYER_SPEED_JUMP;
    static const float PLAYER_GRAVITY;
    static const float PLAYER_MAX_GRAVITY;

    static const int   HIT_REGION_MEAGIN_WIDTH;
    static const int   HIT_REGION_MEAGIN_HEIGHT;
    static const int   ROTATION_RATE;

    GraphicsDevice* mGraphicsDevice;
    SoundDevice* mSoundDevice;

    ID2D1Bitmap* mImage;
    D2D1_RECT_F mImageSrcRect;

    SEData mGameOverSE;

    D2DTextData mD2DTextData;

    int mX, mY;

    bool mIsAlive;
    bool mIsLeft;
    bool mIsGameOver;

    PlayerStatus mPlayerStatus;
};
