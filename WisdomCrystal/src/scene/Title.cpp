// Title.cpp

#include "Title.h"
#include "Loading.h"
#include "win/util/Input.h"
#include "util/Point.h"


Title::Title() : mId(0),
                 mKeyWait(0),
                 mPlay(),
                 mSetting(),
                 mEnd(),
                 mCanvas(),
                 mBrush(),
                 mText(),
                 mBackGround(),
                 mNextScene(nullptr)
{
    // empty
}


Title::~Title() {
    // empty
}


bool Title::Init(GraphicsDevice* graphicsDevice,
                 SoundDevice*    soundDevice,
                 GameObjManager *gameObjManager) {

    if (mPlay.Init(graphicsDevice, soundDevice, 0, 600, 460, TEXT("リスト1")) == false) {
        return false;
    }
    if (mSetting.Init(graphicsDevice, soundDevice, 1, 600, 490, TEXT("リスト2")) == false) {
        return false;
    }
    if (mEnd.Init(graphicsDevice, soundDevice, 2, 600, 520, TEXT("終了")) == false) {
        return false;
    }

    mCanvas.Init(graphicsDevice);

    if (mText.Init(graphicsDevice) == false) {
        return false;
    }
    if (mBackGround.Init(graphicsDevice, 0) == false) {
        return false;
    }

    mBrush.Init(graphicsDevice);
    mBrush.CreateLinearGradientBrush();

    mText.SetFontSize(50.0f);

    mNextScene = this;

    return true;
}


Scene* Title::Update() {
    onKeyDown();

    mBackGround.Draw();
    mBrush.Update();
    mCanvas.FillRectangle(0, 0, 150, 150, mBrush);
    mText.Draw(TEXT("タイトル"), 300, 600, 400, 800);
    mPlay.Draw(mId);
    mSetting.Draw(mId);
    mEnd.Draw(mId);

    Point p1(1,1);
    Point p2(2,2);
    Point p3(3,3);
    Point p4(4,4);

    Point p5(5,5);
    p5 = p1 + p2;
    Point p6(5,5);
    p6 = p1 - p2;
    Point p7(5,5);
    p7 = p1 * p2;
    Point p8(5,5);
    p8 = p1 * 2;
    Point p9(5,5);
    p9 = p1 / p2;
    Point p10(5,5);
    p10 = p4 / 2;

    return mNextScene;
}


void Title::onKeyDown() {

    if (++mKeyWait < 5) {
        return;
    }

    if (IsKeyPressed(Input::DOWN)) {
        mId = ++mId > 2 ? 0 : mId;
    } else if (IsKeyPressed(Input::UP)) {
        mId = --mId < 0 ? 2 : mId;
    } else if (IsKeyPressed(Input::SPACE)) {

        switch (mId) {
            case 0: { mNextScene = new Loading(); break; }
            case 1: { mNextScene = new Loading(); break; }
            case 2: { PostQuitMessage(0); }
            default:{ mNextScene = this; }
        }
    }

    mKeyWait = 0;
}


