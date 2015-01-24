// GameObjManager.cpp

// Includes
#include "GameObjManager.h"
#include "WisdomCrystal.h"

#include "Player.h"
#include "SolidBlock.h"


GameObjManager::GameObjManager() : mActiveGameObjects() {
    std::fill(std::begin(mActiveGameObjects), std::end(mActiveGameObjects), nullptr);
}


GameObjManager::~GameObjManager() {
    // empty    
}


bool GameObjManager::Init(GraphicsDevice* graphicsDevice, SoundDevice* soundDevice) {
    activateForInitAndCleanup();

    for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it) {
        if (*it != nullptr) {
            if ((*it)->Init(graphicsDevice, soundDevice) == false) {
                return false; // GamaObject ‚Ì‰Šú‰»‚ÉŽ¸”s
            }
        }
    }

    Deactivate();
    return true;
}


void GameObjManager::Cleanup() {

    activateForInitAndCleanup();

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


void GameObjManager::Deactivate() {
    for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it) {
        if (*it != nullptr) {
            (*it)->Deactivate();
        }
    }
    std::fill(std::begin(mActiveGameObjects), std::end(mActiveGameObjects), nullptr);
}


bool GameObjManager::Activate(int initX, int initY, int objID) {

    GameObject* obj;

    switch (objID) {
        case 0:  obj = nullptr;                                   break;
        case 1:  obj = Player::Activate(initX, initY);            break;
        case 2:  obj = SolidBlock::Activate(initX, initY, objID); break;

        default: obj = nullptr;
    }

    static int index = 0;
    
    try {
        mActiveGameObjects.at(index) = obj;
    } catch (const std::out_of_range&) {
        return false;
    }

    ++index;

    return true;
}


void GameObjManager::activateForInitAndCleanup() {
    Deactivate();
    for (int i = 0; i <= NUM_GAME_OBJECT; ++i) {
        Activate(0, 0, i);
    }
}
