// SceneChanger.cpp


// Includes
#include "SceneChanger.h"
#include "scene/Playing.h"


SceneChanger::SceneChanger() : mCurrentScene(new Playing()) {
    // empty
}


SceneChanger::~SceneChanger() {
    // empty
}


void SceneChanger::UpdateScene(GameObjManager *gameObjManager) {

    // CurrentScene の Update の後, 次の場面を nextScene に入れておく
    Scene* nextScene = mCurrentScene->Update(gameObjManager);

    // nextとCurrentが違った場合のみ, Currentをnextに置き換える
    if (nextScene != mCurrentScene.get()) {
        mCurrentScene.reset(nextScene);
    }
}
