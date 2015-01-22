// SceneManager.cpp

// Includes
#include "SceneManager.h"
#include "scene/Title.h"


// Static member variables
SceneManager SceneManager::mSceneManager;


SceneManager::SceneManager() : mCurrentScene(new Title) {
    // empty
}


SceneManager::~SceneManager() {
    mCurrentScene.reset();
}


SceneManager *SceneManager::GetInstance() {
    return &mSceneManager;
}


void SceneManager::UpdateScene() {

    // CurrentSceneのUpdateの後,次の場面を nextScene に入れておく
    Scene* nextScene(mCurrentScene->Update());

    // nextとCurrentが違った場合のみ,Currentをnextに置き換える
    if (nextScene != mCurrentScene.get()) {
        mCurrentScene.reset(nextScene);
    }
}