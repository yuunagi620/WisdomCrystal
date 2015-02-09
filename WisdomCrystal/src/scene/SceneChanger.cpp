// SceneChanger.cpp


// Includes
#include "SceneChanger.h"
#include "scene/Playing.h"


SceneChanger::SceneChanger() : mCurrentScene(new Playing()),
                               mGraphicsDevice(nullptr),
                               mSoundDevice(nullptr)
{
    // empty
}


SceneChanger::~SceneChanger() {
    // empty
}


bool SceneChanger::Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice) {
    mGraphicsDevice = graphicsDevice;
    mSoundDevice = soundDevice;

    return true;
}


void SceneChanger::UpdateScene(GameObjManager *gameObjManager) {

    // CurrentScene ‚Ì Update ‚ÌŒã, Ÿ‚Ìê–Ê‚ğ nextScene ‚É“ü‚ê‚Ä‚¨‚­
    Scene* nextScene = mCurrentScene->Update(gameObjManager);

    // next‚ÆCurrent‚ªˆá‚Á‚½ê‡‚Ì‚İ, Current‚ğnext‚É’u‚«Š·‚¦‚é
    if (nextScene != mCurrentScene.get()) {
        mCurrentScene.reset(nextScene);
    }
}
