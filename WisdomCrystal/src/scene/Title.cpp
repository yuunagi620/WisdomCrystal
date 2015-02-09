// Title.cpp

// Includes
#include "Title.h"
#include "Loading.h"
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

    if (mPlay.Init(graphicsDevice, soundDevice, 0, 600, 460, TEXT("リスト1")) == false) {
        return false;
    }

    if (mSetting.Init(graphicsDevice, soundDevice, 1, 600, 490, TEXT("リスト2")) == false) {
        return false;
    }

    if (mEnd.Init(graphicsDevice, soundDevice, 2, 600, 520, TEXT("終了")) == false) {
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

    mText.Draw(TEXT("タイトル"), D2D1::RectF(550.f, 300.f, 800.f, 400.f));
    
    onKeyDown();

    mPlay.Draw(mId);
    mSetting.Draw(mId);
    mEnd.Draw(mId);

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


