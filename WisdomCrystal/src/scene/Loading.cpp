// Loading.cpp

// Includes
#include "Loading.h"
#include "Playing.h"
#include "Error.h"
#include "object/GameObjManager.h"
#include "MapManager.h"


Loading::~Loading() {
    // empty
}


Scene *Loading::Update(GameObjManager *gameObjManager) {

    if (MapManager::GetInstance()->LoadMapDataFile(1) == false) {
        return new Error; // マップデータの読み込みに失敗
    }

    if (MapManager::GetInstance()->ActivateGameObj() == false) {
        return new Error; // オブジェクトのアクティブ化に失敗
    }

    return new Playing();
}