// CollisionObjManager.cpp

// Includes
#include "CollisionObjManager.h"

#include "Player.h"
#include "SolidBlock.h"


// Constants
const int CollisionObjManager::MAX_COLLISON_OBJECTS = 880; // CollisionObject �ő吔


// Static member variables
CollisionObjManager           CollisionObjManager::mCollisionObjManager;
std::vector<CollisionObject*> CollisionObjManager::mActiveCollisionObjects;


CollisionObjManager::CollisionObjManager() {
    mActiveCollisionObjects.reserve(MAX_COLLISON_OBJECTS);
}


CollisionObjManager *CollisionObjManager::GetInstance() {
    return &mCollisionObjManager;
}


std::vector<CollisionObject*> *CollisionObjManager::GetActiveCollisionObjects() {
    return &mActiveCollisionObjects;
}


GameObject *CollisionObjManager::Activate(int initX, int initY, int objID) {
    
    CollisionObject* obj;

    switch (objID) {
        case 1:  obj = Player::Activate(initX, initY);            break;
        case 2:  obj = SolidBlock::Activate(initX, initY, objID); break;

        default: obj = nullptr;
    }
    
    if (obj != nullptr) {
        mActiveCollisionObjects.push_back(obj);
    }

    return obj;
}
