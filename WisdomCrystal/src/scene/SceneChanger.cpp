// SceneChanger.cpp


// Includes
#include "SceneChanger.h"

#include "Title.h"
#include "Loading.h"
#include "Playing.h"


SceneChanger::SceneChanger() : mCurrentScene(new Loading()),
                               mGraphicsDevice(nullptr),
                               mSoundDevice(nullptr),
                               mGameObjManager(nullptr)
{
    // empty
}


SceneChanger::~SceneChanger() {
    // empty
}


bool SceneChanger::Init(GraphicsDevice *graphicsDevice,
                        SoundDevice *soundDevice,
                        GameObjManager *gameObjManager) {
    mGraphicsDevice = graphicsDevice;
    mSoundDevice = soundDevice;
    mGameObjManager = gameObjManager;

    if (initNextScene() == false) {
        return false;
    }
    return true;
}


bool SceneChanger::UpdateScene() {

    // CurrentScene ‚Ì Update ‚ÌŒã, ŽŸ‚Ìê–Ê‚ð nextScene ‚É“ü‚ê‚Ä‚¨‚­
    Scene* nextScene = mCurrentScene->Update();

    // next‚ÆCurrent‚ªˆá‚Á‚½ê‡‚Ì‚Ý, Current‚ðnext‚É’u‚«Š·‚¦‚é
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