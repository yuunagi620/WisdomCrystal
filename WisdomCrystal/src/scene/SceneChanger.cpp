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

    // CurrentScene �� Update �̌�, ���̏�ʂ� nextScene �ɓ���Ă���
    Scene* nextScene = mCurrentScene->Update(gameObjManager);

    // next��Current��������ꍇ�̂�, Current��next�ɒu��������
    if (nextScene != mCurrentScene.get()) {
        mCurrentScene.reset(nextScene);
    }
}
