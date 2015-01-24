// SceneChanger.cpp


// Includes
#include "SceneChanger.h"
#include "scene/Title.h"


SceneChanger::SceneChanger() : mCurrentScene(new Title) {
    // empty
}


SceneChanger::~SceneChanger() {
    // empty
}


void SceneChanger::UpdateScene(GameObjManager *gameObjManager) {

    // CurrentScene ‚Ì Update ‚ÌŒã, Ÿ‚Ìê–Ê‚ğ nextScene ‚É“ü‚ê‚Ä‚¨‚­
    Scene* nextScene = mCurrentScene->Update(gameObjManager);

    // next‚ÆCurrent‚ªˆá‚Á‚½ê‡‚Ì‚İ, Current‚ğnext‚É’u‚«Š·‚¦‚é
    if (nextScene != mCurrentScene.get()) {
        mCurrentScene.reset(nextScene);
    }
}
