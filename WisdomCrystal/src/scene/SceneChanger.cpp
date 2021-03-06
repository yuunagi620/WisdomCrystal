// SceneChanger.cpp

#include "SceneChanger.h"
#include "Title.h"
#include "Loading.h"
#include "Playing.h"


SceneChanger::SceneChanger() 
    : mCurrentScene(new Title())
    , mGraphicsDevice(nullptr)
    , mSoundDevice(nullptr)
    , mGameObjManager(nullptr) {
    // empty
}


SceneChanger::~SceneChanger() {
    // empty
}


bool SceneChanger::Init(GraphicsDevice *graphicsDevice,
                        SoundDevice *soundDevice,
                        GameObjManager *gameObjManager) {

    mGraphicsDevice = graphicsDevice;
    mSoundDevice    = soundDevice;
    mGameObjManager = gameObjManager;

    if (initNextScene() == false) {
        return false;
    }

    return true;
}


bool SceneChanger::UpdateScene() {

    // CurrentScene の Update の後, 次の場面を nextScene に入れておく
    Scene* nextScene = mCurrentScene->Update();

    // nextとCurrentが違った場合のみ, Currentをnextに置き換える
    if (nextScene != mCurrentScene.get()) {
        mCurrentScene.reset(nextScene);

        if (initNextScene() == false) {
            return false;
        }
    }

    return true;
}


bool SceneChanger::initNextScene() {
    return mCurrentScene->Init(mGraphicsDevice, mSoundDevice, mGameObjManager);
}