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

    // CurrentScene �� Update �̌�, ���̏�ʂ� nextScene �ɓ���Ă���
    Scene* nextScene = mCurrentScene->Update(gameObjManager);

    // next��Current��������ꍇ�̂�, Current��next�ɒu��������
    if (nextScene != mCurrentScene.get()) {
        mCurrentScene.reset(nextScene);
    }
}
