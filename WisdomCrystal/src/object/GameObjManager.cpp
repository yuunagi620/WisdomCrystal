// GameObjManager.cpp

// Includes
#include "GameObjManager.h"
#include "Player.h"
#include "Ghost.h"


GameObjManager::GameObjManager() : mGameObjectArray() {
    std::fill(std::begin(mGameObjectArray), std::end(mGameObjectArray), nullptr);
}


GameObjManager::~GameObjManager() {
    // empty    
}


bool GameObjManager::Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) {
    mGameObjectArray.at(0).reset(new Player());
    mGameObjectArray.at(1).reset(new Ghost());

    for (auto it = mGameObjectArray.begin(); it != mGameObjectArray.end(); ++it) {
        if (*it != nullptr) {
            if ((*it)->Init(graphicsDevice, soundDevice) == false) {
                return false;
            }
        }
    }

    mGameObjectArray.at(0)->Activate(100, 300);
    mGameObjectArray.at(1)->Activate(700, 300);

    return true;
}


void GameObjManager::Activate(const int initX, const int initY) {
    for (auto it = mGameObjectArray.begin(); it != mGameObjectArray.end(); ++it) {
        if (*it != nullptr) {
            (*it)->Activate(initX, initY);
        }
    }
}


void GameObjManager::Update() {
    for (auto it = mGameObjectArray.begin(); it != mGameObjectArray.end(); ++it) {
        if (*it != nullptr) {
            if ((*it)->GetIsAlive()) { 
                (*it)->Update();
            }
        }
    }
}
