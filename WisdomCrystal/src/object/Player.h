// Player.h

#pragma once

#include "GameObject.h"
#include "Canvas.h"
#include "win/D2D/D2DImage.h"


class Player : public GameObject {

public:
    Player();
    virtual ~Player();

    bool Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) override;
    bool Activate(const int initX, const int initY) override;
    void Update() override;

private:
    void draw();
    void gameOverAnimetion();

private:
    static const int PLAYER_IMAGE_WIDTH;
    static const int PLAYER_IMAGE_HEIGHT;
    static const int PLAYER_SPEED;
    static const int ROTATION_RATE;

    Canvas mCanvas;
    SoundDevice* mSoundDevice;

    D2DImage mImage;
    SEData mGameOverSE;

    int mX, mY;
    bool mIsAlive;
    bool mIsLeft;
    bool mIsGameOver;
};
