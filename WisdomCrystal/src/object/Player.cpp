// Player.cpp

// Includes
#include <d2d1helper.h>

#include "Player.h"
#include "win/util/Input.h"


// Constants
const int   Player::PLAYER_IMAGE_WIDTH  = 32;
const int   Player::PLAYER_IMAGE_HEIGHT = 32;
const int   Player::PLAYER_SPEED        = 3;
const int   Player::ROTATION_RATE       = 10;


Player::Player() : mGraphicsDevice(nullptr),
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
    mGraphicsDevice = graphicsDevice;
    mSoundDevice = soundDevice;

    if (mImage.Init(mGraphicsDevice, TEXT("resources/image/player.png")) == false) {
        return false;
    }

    RECT imageSrcRect = {0, 0, PLAYER_IMAGE_WIDTH, PLAYER_IMAGE_HEIGHT};
    mImage.SetImageSrcRect(imageSrcRect);

    if (mGameOverSE.Init(mSoundDevice, TEXT("resources/sound/SE/gameOverSE.wav")) == false) {
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
        mGameOverSE.StartSE();
    }

    if (Input::IsKeyPressed(Input::C)) {
        mIsGameOver = true;
    }

    // ŽÀÛ‚ÉPlayer‚ÌÀ•W‚ðˆÚ“®
    mX += dx;
    mY += dy;

    draw();
}


void Player::draw() {

    // ¶‚ÉŒü‚¢‚Ä‚¢‚½‚ç‰æ‘œ‚ð”½“]
    if (mIsLeft) {
        mGraphicsDevice->FlipHorizontal(static_cast<float>(mX) + PLAYER_IMAGE_WIDTH  / 2,
                                        static_cast<float>(mY) + PLAYER_IMAGE_HEIGHT / 2);
    }

    if (mIsGameOver) {
        gameOverAnimetion();
    } 

    mImage.Draw(mX, mY);
    mGraphicsDevice->ResetTransform();
}


void Player::gameOverAnimetion() {

    static int angle = 0;
    angle = (angle + ROTATION_RATE) % 360;
    
    mGraphicsDevice->RotateTransform(static_cast<float>(mX) + PLAYER_IMAGE_WIDTH  / 2,
                                     static_cast<float>(mY) + PLAYER_IMAGE_HEIGHT / 2,
                                     static_cast<float>(angle));
}

