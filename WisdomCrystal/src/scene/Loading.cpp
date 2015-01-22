// Loading.cpp

// Includes
#include "Loading.h"
#include "Playing.h"
#include "Error.h"
#include "../WisdomCrystal.h"
#include "../object/GameObjManager.h"
#include "../MapManager.h"


Scene *Loading::Update() {

    if (MapManager::GetInstance()->LoadMapDataFile(1) == false) {
        return new Error; // マップデータの読み込みに失敗
    }

    if (MapManager::GetInstance()->ActivateGameObj() == false) {
        return new Error; // オブジェクトのアクティブ化に失敗
    }

    return new Playing();
}