// SceneManager.cpp


// Includes
#include "SceneManager.h"
#include "scene/Title.h"


SceneManager::SceneManager() : mCurrentScene(new Title) {
    // empty
}


SceneManager::~SceneManager() {
    mCurrentScene.reset();
}


void SceneManager::UpdateScene() {

    // CurrentScene‚ÌUpdate‚ÌŒã,Ÿ‚Ìê–Ê‚ğ nextScene ‚É“ü‚ê‚Ä‚¨‚­
    Scene* nextScene = mCurrentScene->Update();

    // next‚ÆCurrent‚ªˆá‚Á‚½ê‡‚Ì‚İ, Current‚ğnext‚É’u‚«Š·‚¦‚é
    if (nextScene != mCurrentScene.get()) {
        mCurrentScene.reset(nextScene);
    }
}