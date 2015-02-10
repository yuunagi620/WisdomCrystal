// GameObjManager.cpp

// Includes
#include "GameObjManager.h"
#include "Player.h"
#include "Ghost.h"


GameObjManager::GameObjManager() : mGameObjectMap() {
    // empty
}


GameObjManager::~GameObjManager() {
    // empty    
}


bool GameObjManager::Init(GraphicsDevice *graphicsDevice, SoundDevice *soundDevice) {
    mGameObjectMap.insert(std::make_pair(PLAYER, new Player()));
    for (int i = 0; i < 3; ++i) {
        mGameObjectMap.insert(std::make_pair(GHOST, new Ghost()));
    }

    for (auto it = mGameObjectMap.begin(); it != mGameObjectMap.end(); ++it) {
        if (it->second != nullptr) {
            if (it->second->Init(graphicsDevice, soundDevice) == false) {
                return false;
            }
        }
    }
    Activate(PLAYER, 100, 300);
    Activate(GHOST, 600, 300);
    Activate(GHOST, 700, 300);
    Activate(GHOST, 200, 300);

    return true;
}


bool GameObjManager::Activate(const GameObjectId initId, const int initX, const int initY) {
    auto range = mGameObjectMap.equal_range(initId);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second->Activate(initX, initY)) {
            return true;
        }
    }

    return false;
}


void GameObjManager::Update() {
    for (auto it = mGameObjectMap.begin(); it != mGameObjectMap.end(); ++it) {
        if (it->second != nullptr) {
            if (it->second->GetIsAlive()) { 
                it->second->Update();
            }
        }
    }
}
