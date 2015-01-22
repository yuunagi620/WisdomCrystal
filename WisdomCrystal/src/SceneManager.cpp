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

    // CurrentScene��Update�̌�,���̏�ʂ� nextScene �ɓ���Ă���
    Scene* nextScene(mCurrentScene->Update());

    // next��Current��������ꍇ�̂�,Current��next�ɒu��������
    if (nextScene != mCurrentScene.get()) {
        mCurrentScene.reset(nextScene);
    }
}