// Title.cpp

// Includes
#include "Title.h"
#include "win/util/Input.h"


Title::Title() : mId(0),
                 mKeyWait(0),
                 mPlay(),
                 mSetting(),
                 mText(),
                 mGraphicsDevice(nullptr),
                 mSoundDevice(nullptr),
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
    mGraphicsDevice = graphicsDevice;
    mSoundDevice = soundDevice;

    if (mPlay.Init(graphicsDevice, soundDevice, 0, 40, 60, TEXT("")) == false) {
        return false;
    }

    if (mSetting.Init(graphicsDevice, soundDevice, 1, 40, 90, TEXT("")) == false) {
        return false;
    }

    if (mEnd.Init(graphicsDevice, soundDevice, 2, 40, 120, TEXT("")) == false) {
        return false;
    }

    if (mText.Init(mGraphicsDevice) == false) {
        return false;
    }
    mText.SetFontSize(50.0f);

    mNextScene = this;

    return true;
}


Scene* Title::Update() {

    // 描画
    mText.DrawText(TEXT("タイトル"), D2D1::RectF(0.f, 0.f, 300.f, 40.f));
    
    keyDownEvent();

    // 項目の描画メソッドをまとめて呼ぶ
    mPlay.Draw(mId);
    mSetting.Draw(mId);
    mEnd.Draw(mId);

    return mNextScene;
}


void Title::keyDownEvent() {

    if (++mKeyWait < 5) {
        return;
    }

    if (IsKeyPressed(Input::DOWN)) {
        mId = ++mId > 2 ? 0 : mId;
    } else if (IsKeyPressed(Input::UP)) {
        mId = --mId < 0 ? 2 : mId;
    } else if (IsKeyPressed(Input::SPACE)) {
        // empty
    }

    mKeyWait = 0;
}


