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

    // CurrentScene �� Update �̌�, ���̏�ʂ� nextScene �ɓ���Ă���
    Scene* nextScene = mCurrentScene->Update(gameObjManager);

    // next��Current��������ꍇ�̂�, Current��next�ɒu��������
    if (nextScene != mCurrentScene.get()) {
        mCurrentScene.reset(nextScene);
    }
}
