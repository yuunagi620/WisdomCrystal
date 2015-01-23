// GameObjManager.cpp

// Includes
#include "GameObjManager.h"
#include "WisdomCrystal.h"

#include "Player.h"
#include "SolidBlock.h"


// Static member variables
GameObjManager           GameObjManager::mGameObjManager;
std::vector<GameObject*> GameObjManager::mActiveGameObjects; // アクティブ化したゲームオブジェクト


GameObjManager::GameObjManager() {
    // empty    
}


GameObjManager::~GameObjManager() {
    // empty    
}


bool GameObjManager::Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) {
    mActiveGameObjects.reserve(1000);

    activateForInitAndCleanup();

    for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it) {
        if ((*it)->Init(graphicsDevice, soundDevice) == false) {
            return false; // GamaObject の初期化に失敗
        }
    }

    Deactivate();
    return true;
}


void GameObjManager::Cleanup() {

    activateForInitAndCleanup();

    for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it) {
        (*it)->Cleanup();
    }
}


void GameObjManager::Update() {
    for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it) {
        if (*it != nullptr) {
            (*it)->Update();
        }
    }
}


void GameObjManager::Deactivate() {
    for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it) {
        if (*it != nullptr) {
            (*it)->Deactivate();
        }
    }

    mActiveGameObjects.clear();
}


bool GameObjManager::Activate(int initX, int initY, int objID) {

    GameObject* obj;

    switch (objID) {
        case 0:  obj = nullptr;                                   break;
        case 1:  obj = Player::Activate(initX, initY);            break;
        case 2:  obj = SolidBlock::Activate(initX, initY, objID); break;

        default: obj = nullptr;
    }

    if (obj != nullptr) {
        mActiveGameObjects.push_back(obj);
    }

    return true;
}


void GameObjManager::activateForInitAndCleanup() {
    Deactivate();
    for (int i = 0; i <= GAME_OBJECT_NUM; ++i) {
        Activate(0, 0, i);
    }
}
