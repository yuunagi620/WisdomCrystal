// GameObjManager.cpp

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
    mGameObjectMap.insert(std::make_pair(PLAYER, std::make_shared<Player>()));
    for (int i = 0; i < 3; ++i) {
        mGameObjectMap.insert(std::make_pair(GHOST, std::make_shared<Ghost>()));
    }

    for (const auto& el : mGameObjectMap) {
        if (el.second != nullptr) {
            if (el.second->Init(graphicsDevice, soundDevice) == false) {
                return false;
            }
        }
    }

    Activate(PLAYER, 100, 100);
    Activate(GHOST,  500, 300);
    Activate(GHOST,  500, 500);

    return true;
}


bool GameObjManager::Activate(const GameObjectId initId, int initX, int initY) {
    auto range = mGameObjectMap.equal_range(initId);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second->Activate(initX, initY)) {
            return true;
        }
    }

    return false;
}


void GameObjManager::Update() {
    for (const auto& el : mGameObjectMap) {
        if (el.second != nullptr) {
            if (el.second->GetIsAlive()) { 
                el.second->Update();
            }
        }
    }
}
