// SceneManager.cpp


// Includes
#include "SceneManager.h"
#include "scene/Title.h"


SceneManager::SceneManager() : mCurrentScene(new Title) {
    // empty
}


SceneManager::~SceneManager() {
    // empty
}


void SceneManager::UpdateScene(GameObjManager *gameObjManager) {

    // CurrentScene の Update の後, 次の場面を nextScene に入れておく
    Scene* nextScene = mCurrentScene->Update(gameObjManager);

    // nextとCurrentが違った場合のみ, Currentをnextに置き換える
    if (nextScene != mCurrentScene.get()) {
        mCurrentScene.reset(nextScene);
    }
}
