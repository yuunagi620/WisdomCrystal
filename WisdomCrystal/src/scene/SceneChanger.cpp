// SceneChanger.cpp


// Includes
#include "SceneChanger.h"

#include "Title.h"
#include "Loading.h"
#include "Playing.h"


SceneChanger::SceneChanger() : mCurrentScene(new Loading()),
                               mGraphicsDevice(nullptr),
                               mSoundDevice(nullptr),
                               mGameObjManager(nullptr)
{
    // empty
}


SceneChanger::~SceneChanger() {
    // empty
}


bool SceneChanger::Init(GraphicsDevice *graphicsDevice,
                        SoundDevice *soundDevice,
                        GameObjManager *gameObjManager) {
    mGraphicsDevice = graphicsDevice;
    mSoundDevice = soundDevice;
    mGameObjManager = gameObjManager;

    if (initNextScene() == false) {
        return false;
    }
    return true;
}


bool SceneChanger::UpdateScene() {

    // CurrentScene �� Update �̌�, ���̏�ʂ� nextScene �ɓ���Ă���
    Scene* nextScene = mCurrentScene->Update();

    // next��Current��������ꍇ�̂�, Current��next�ɒu��������
    if (nextScene != mCurrentScene.get()) {
        mCurrentScene.reset(nextScene);

        if (initNextScene() == false) {
            return false;
        }
    }

    return true;
}


bool SceneChanger::initNextScene() {
    return mCurrentScene->Init(mGraphicsDevice, mSoundDevice, mGameObjManager);
}