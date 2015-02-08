// Player.cpp

// Includes
#include <d2d1helper.h>

#include "Player.h"
#include "win/util/Input.h"


// Constants
const int   Player::PLAYER_IMAGE_WIDTH  = 32;
const int   Player::PLAYER_IMAGE_HEIGHT = 32;
const int   Player::PLAYER_IMAGE_ROW    = 10;
const int   Player::PLAYER_SPEED_X      = 3;
const float Player::PLAYER_SPEED_JUMP   = -10.0f;
const float Player::PLAYER_GRAVITY      = 0.5f;
const float Player::PLAYER_MAX_GRAVITY  = 4;

const int   Player::HIT_REGION_MEAGIN_WIDTH  = 0;
const int   Player::HIT_REGION_MEAGIN_HEIGHT = 0;
const int   Player::ROTATION_RATE = 10;


Player::Player() : mGraphicsDevice(nullptr),
                   mSoundDevice(nullptr),
                   mImage(nullptr),
                   mImageSrcRect(),
                   mGameOverSE(),
                   mD2DTextData(),
                   mX(100),
                   mY(400),
                   mIsAlive(false),
                   mIsLeft(false),
                   mIsGameOver(false),
                   mPlayerStatus(NORMAL)
{
    // empty
}


Player::~Player() {
    // empty
}


bool Player::Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) {
    mGraphicsDevice = graphicsDevice;
    mSoundDevice = soundDevice;

    // 以下、画像の読み込み
    mImage = mGraphicsDevice->CreateD2DBitmap(TEXT("resources/image/player.png"));
    if (mImage == nullptr) {
        MessageBox(nullptr, TEXT("Can not init player.png"), TEXT("ERROR"), MB_OK);
        return false;
    }

    mImageSrcRect = getRectF();

    // 以下、SEデータの作成
    if (mGameOverSE.Init(mSoundDevice, TEXT("resources/sound/SE/gameOverSE.wav")) == false) {
        MessageBox(nullptr, TEXT("Can not init gameOverSE.wav."), TEXT("ERROR"), MB_OK);
        return false;
    }

    // test
    if (mD2DTextData.Init(mGraphicsDevice) == false) {
        return false;
    }
    mD2DTextData.SetFontSize(50.0f);

    return true;
}


void Player::Update() {
    int dx = 0;
    int dy = 0;
    
    if (Input::IsKeyPressed(Input::LEFT)) {
        dx -= PLAYER_SPEED_X;
        mIsLeft = true;
    }

    if (Input::IsKeyPressed(Input::RIGHT)) {
        dx += PLAYER_SPEED_X;
        mIsLeft = false;
    }

    if (Input::IsKeyPressed(Input::DOWN)) {
        dy += 3;
    }

    if (Input::IsKeyPressed(Input::UP)) {
        dy -= 3;
    }

    if (Input::IsKeyPressed(Input::SPACE)) {
        soundSE(SE_GAMEOVER);
    }


    // 実際にPlayerの座標を移動
    mX += dx;
    mY += dy;

    changeImage(mPlayerStatus);
    draw();
}


void Player::draw() {

    // 左に向いていたら画像を反転
    if (mIsLeft) {
        mGraphicsDevice->FlipHorizontal(static_cast<float>(mX) + PLAYER_IMAGE_WIDTH  / 2,
                                        static_cast<float>(mY) + PLAYER_IMAGE_HEIGHT / 2);
    }

    if (mIsGameOver) {
        gameOverAnimetion();
    } 

    mGraphicsDevice->DrawBitmap(mImage, getRectF(), 1, mImageSrcRect);

    mGraphicsDevice->ResetTransform();
    
    mD2DTextData.DrawText(TEXT("test"), D2D1::RectF(250.f, 250.f, 400.f, 300.f));
}


void Player::gameOverAnimetion() {

    static int angle = 0;
    angle = (angle + ROTATION_RATE) % 360;
    
    mGraphicsDevice->RotateTransform(static_cast<float>(mX) + PLAYER_IMAGE_WIDTH  / 2,
                              static_cast<float>(mY) + PLAYER_IMAGE_HEIGHT / 2,
                              static_cast<float>(angle));
}


// indexを元に画像の領域を指定
void Player::changeImage(const int imageIndex) {
    mImageSrcRect = 
        D2D1::RectF(static_cast<float>((imageIndex % PLAYER_IMAGE_ROW)     * PLAYER_IMAGE_WIDTH),
                    static_cast<float>((imageIndex / PLAYER_IMAGE_ROW)     * PLAYER_IMAGE_HEIGHT),
                    static_cast<float>((imageIndex % PLAYER_IMAGE_ROW + 1) * PLAYER_IMAGE_WIDTH),
                    static_cast<float>((imageIndex / PLAYER_IMAGE_ROW + 1) * PLAYER_IMAGE_HEIGHT));
}



D2D1_RECT_F Player::getRectF() {
    return D2D1::RectF(static_cast<float>(mX),
                       static_cast<float>(mY),
                       static_cast<float>(mX) + PLAYER_IMAGE_WIDTH,
                       static_cast<float>(mY) + PLAYER_IMAGE_HEIGHT);
}


RECT Player::getHitRect(const int dx, const int dy) {
    RECT rect = {
        mX + dx + HIT_REGION_MEAGIN_WIDTH,
        mY + dy + HIT_REGION_MEAGIN_HEIGHT,
        mX + dx - HIT_REGION_MEAGIN_WIDTH  + PLAYER_IMAGE_WIDTH,
        mY + dy - HIT_REGION_MEAGIN_HEIGHT + PLAYER_IMAGE_HEIGHT
    };

    return rect;
}


void Player::soundSE(PlayerSE playerSE) {
    switch (playerSE) {
        case SE_GAMEOVER: mGameOverSE.StartSE(); break;
    }
}
