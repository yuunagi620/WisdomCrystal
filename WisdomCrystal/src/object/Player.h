// Player.h

#pragma once

#include "GameObject.h"
#include "win/D2D/D2DImage.h"
#include "win/D2D/D2DText.h"


class Player : public GameObject {

public:
    Player();
    virtual ~Player();

    bool Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) override;
    void Update() override;

private:
    void draw();
    void gameOverAnimetion();
    //void changeImage(const int index);
    //D2D1_RECT_F getRectF();

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

    D2DImage mImage;
    SEData mGameOverSE;

    int mX, mY;

    bool mIsAlive;
    bool mIsLeft;
    bool mIsGameOver;
};
