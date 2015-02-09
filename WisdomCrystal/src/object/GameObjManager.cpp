// GameObjManager.cpp

// Includes
#include "GameObjManager.h"
#include "Player.h"
#include "Ghost.h"


GameObjManager::GameObjManager() : mActiveGameObjects() {
    std::fill(std::begin(mActiveGameObjects), std::end(mActiveGameObjects), nullptr);
}


GameObjManager::~GameObjManager() {
    // empty    
}


bool GameObjManager::Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) {
    mActiveGameObjects.at(0).reset(new Player());
    mActiveGameObjects.at(1).reset(new Ghost());

    for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it) {
        if (*it != nullptr) {
            if ((*it)->Init(graphicsDevice, soundDevice) == false) {
                return false; // GamaObject ‚Ì‰Šú‰»‚ÉŽ¸”s
            }
        }
    }

    return true;
}


void GameObjManager::Update() {
    for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it) {
        if (*it != nullptr) {
            (*it)->Update();
        }
    }
}
