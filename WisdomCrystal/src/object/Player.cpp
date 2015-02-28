// Player.cpp

#include <d2d1helper.h>

#include "Player.h"
#include "win/util/Input.h"

const int   Player::PLAYER_IMAGE_WIDTH  = 32;
const int   Player::PLAYER_IMAGE_HEIGHT = 32;
const int   Player::PLAYER_SPEED        = 3;
const int   Player::ROTATION_RATE       = 10;


Player::Player() : mCanvas(),
                   mSoundDevice(nullptr),
                   mImage(),
                   mGameOverSE(),
                   mX(100),
                   mY(400),
                   mIsAlive(false),
                   mIsLeft(false),
                   mIsGameOver(false)
{
    // empty
}


Player::~Player() {
    // empty
}


bool Player::Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) {
    mCanvas.Init(graphicsDevice);

    mSoundDevice = soundDevice;

    if (mImage.Init(graphicsDevice, TEXT("IMAGE_1"), TEXT("PNG")) == false) {
        return false;
    }

    RECT imageSrcRect = {0, 0, PLAYER_IMAGE_WIDTH, PLAYER_IMAGE_HEIGHT};
    mImage.SetImageSrcRect(imageSrcRect);

    if (mGameOverSE.Init(mSoundDevice, "resources/sound/SE/gameOverSE.ogg") == false) {
        return false;
    }

    return true;
}


bool Player::Activate(const int initX, const int initY) {
    if (GetIsAlive()) {
        return false;
    }
    mX = initX;
    mY = initY;
    SetIsAlive(true);

    return true;
}


void Player::Update() {
    int dx = 0;
    int dy = 0;
    
    if (Input::IsKeyPressed(Input::LEFT)) {
        dx -= PLAYER_SPEED;
        mIsLeft = true;
    }

    if (Input::IsKeyPressed(Input::RIGHT)) {
        dx += PLAYER_SPEED;
        mIsLeft = false;
    }

    if (Input::IsKeyPressed(Input::DOWN)) {
        dy += PLAYER_SPEED;
    }

    if (Input::IsKeyPressed(Input::UP)) {
        dy -= PLAYER_SPEED;
    }

    if (Input::IsKeyPressed(Input::SPACE)) {
        mGameOverSE.Start();
    }

    if (Input::IsKeyPressed(Input::C)) {
        mIsGameOver = true;
    }

    // é¿ç€Ç…PlayerÇÃç¿ïWÇà⁄ìÆ
    mX += dx;
    mY += dy;

    draw();
}


void Player::draw() {

    // ç∂Ç…å¸Ç¢ÇƒÇ¢ÇΩÇÁâÊëúÇîΩì]
    if (mIsLeft) {
        mCanvas.FlipHorizontal(static_cast<float>(mX) + PLAYER_IMAGE_WIDTH  / 2,
                                        static_cast<float>(mY) + PLAYER_IMAGE_HEIGHT / 2);
    }

    if (mIsGameOver) {
        gameOverAnimetion();
    } 

    mImage.Draw(mX, mY);
    mCanvas.ResetTransform();
}


void Player::gameOverAnimetion() {

    static int angle = 0;
    angle = (angle + ROTATION_RATE) % 360;
    
    mCanvas.RotateTransform(static_cast<float>(mX) + PLAYER_IMAGE_WIDTH  / 2,
                            static_cast<float>(mY) + PLAYER_IMAGE_HEIGHT / 2,
                            static_cast<float>(angle));
}

