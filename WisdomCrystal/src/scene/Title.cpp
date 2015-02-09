// Title.cpp

// Includes
#include "Title.h"
#include "Loading.h"
#include "win/util/Input.h"


Title::Title() : mId(0),
                 mPlay(),
                 mSetting(),
                 mText(),
                 mGraphicsDevice(nullptr),
                 mSoundDevice(nullptr),
                 mDrawSignal(),
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

    if (mPlay.Init(graphicsDevice, soundDevice, 0, 0, 0, TEXT("")) == false) {
        return false;
    }

    if (mSetting.Init(graphicsDevice, soundDevice, 1, 0, 80, TEXT("")) == false) {
        return false;
    }

    // text
    if (mText.Init(mGraphicsDevice) == false) {
        return false;
    }
    mText.SetFontSize(35.0f);

    // 描画シグナルにタイトル項目の描画メソッドをセット
    mDrawSignal.connect([this](int id) {mPlay.Draw(id);});
    mDrawSignal.connect([this](int id) {mSetting.Draw(id);});

    // 次のシーンをthisにする。
    mNextScene = this;
}


Scene* Title::Update() {

    // 描画
    mText.DrawText(TEXT("タイトル"), D2D1::RectF(250.f, 250.f, 400.f, 300.f));
    
    KeyDownEvent();

    // 項目の描画メソッドをまとめて呼ぶ
    mDrawSignal(mId);
    return mNextScene;
}


void Title::KeyDownEvent() {
    if (IsKeyPressed(Input::DOWN)) {
        mId = ++mId > 1 ? 0 : mId;
    } else if (IsKeyPressed(Input::UP)) {
        mId = --mId < 0 ? 1 : mId;
    } else if (IsKeyPressed(Input::SPACE)) {

        // 次のシーンを調べる。
        //const Scene *next(mNextSignal(mId));
        //mNextScene = next ? next : this;
    }
}


