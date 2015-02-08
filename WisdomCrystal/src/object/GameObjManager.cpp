// GameObjManager.cpp

// Includes
#include "GameObjManager.h"
#include "WisdomCrystal.h"

#include "Player.h"


GameObjManager::GameObjManager() : mActiveGameObjects() {
    std::fill(std::begin(mActiveGameObjects), std::end(mActiveGameObjects), nullptr);
}


GameObjManager::~GameObjManager() {
    // empty    
}


bool GameObjManager::Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) {
    mActiveGameObjects.at(0).reset(new Player());

    for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it) {
        if (*it != nullptr) {
            if ((*it)->Init(graphicsDevice, soundDevice) == false) {
                return false; // GamaObject ‚Ì‰Šú‰»‚ÉŽ¸”s
            }
        }
    }

    return true;
}


void GameObjManager::Cleanup() {
    for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it) {
        if (*it != nullptr) {
            (*it)->Cleanup();
        }
    }
}


void GameObjManager::Update() {
    for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it) {
        if (*it != nullptr) {
            (*it)->Update();
        }
    }
}


bool GameObjManager::Activate(int initX, int initY, int objID) {

    return true;
}

