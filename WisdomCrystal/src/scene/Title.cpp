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
                 mBackGround(),
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

    if (mPlay.Init(mGraphicsDevice, mSoundDevice, 0, 600, 460, TEXT("���X�g1")) == false) {
        return false;
    }
    if (mSetting.Init(mGraphicsDevice, mSoundDevice, 1, 600, 490, TEXT("���X�g2")) == false) {
        return false;
    }
    if (mEnd.Init(mGraphicsDevice, mSoundDevice, 2, 600, 520, TEXT("�I��")) == false) {
        return false;
    }
    if (mText.Init(mGraphicsDevice) == false) {
        return false;
    }
    if (mBackGround.Init(mGraphicsDevice, 0) == false) {
        return false;
    }

    mText.SetFontSize(50.0f);

    mNextScene = this;

    return true;
}


Scene* Title::Update() {

    mText.Draw(TEXT("�^�C�g��"), D2D1::RectF(550.f, 300.f, 800.f, 400.f));
    
    onKeyDown();

    mBackGround.Draw();
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


