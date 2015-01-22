// Playing.cpp

// Includes
#include "Playing.h"

#include "../object/GameObjManager.h"
#include "../BackGround.h"


Scene *Playing::Update() {
    GameObjManager::GetInstance()->Update();
    return this;
}