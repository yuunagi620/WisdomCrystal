// Player.h

#pragma once

#include "CollisionObject.h"
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


class Player : public CollisionObject {

public:
    Player();

    static Player *Activate(int initX, int initY);

    bool Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) override;
    void Cleanup() override;
    void Update() override;
    void Deactivate() override;

    CollisionData CollisionDetection(const CollisionRectData& rectData);

    inline bool IsAlive() const {
        return mIsAlive;
    }

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

    void draw();
    void gameOverAnimetion();
    void changeImage(int index);
    D2D1_RECT_F getRectF();
    RECT getHitRect(int dx, int dy);

    void soundSE(PlayerSE playerSE);

    static Player mPlayer;
    
    static ID2D1Bitmap *mImage;
    static D2D1_RECT_F mImageSrcRect;

    static SEData mJumpSE;
    static SEData mGameOverSE;

    GraphicsDevice* mGraphicsDevice;
    SoundDevice* mSoundDevice;

    D2DTextData mD2DTextData;

    int mX, mY;
    float mVY;

    bool mIsAlive;
    bool mIsLeft;
    bool mIsJump;
    bool mIsGameOver;
    bool mIsGameClear;

    PlayerStatus mPlayerStatus;
};
