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


bool GameObjManager::Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) {
    mGameObjectMap.insert(std::make_pair(PLAYER, new Player()));
    mGameObjectMap.insert(std::make_pair(GHOST, new Ghost()));

    for (auto it = mGameObjectMap.begin(); it != mGameObjectMap.end(); ++it) {
        if (it->second != nullptr) {
            if (it->second->Init(graphicsDevice, soundDevice) == false) {
                return false;
            }
        }
    }
    mGameObjectMap.find(PLAYER)->second->Activate(100, 300);
    mGameObjectMap.find(GHOST)->second->Activate(700, 300);

    return true;
}


void GameObjManager::Activate(const int initX, const int initY) {
    // empty
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
