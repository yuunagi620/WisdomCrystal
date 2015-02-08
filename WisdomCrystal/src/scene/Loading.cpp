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
    MapManager mMapmanager;

    if (mMapmanager.LoadMapDataFile(1) == false) {
        return new Error; // �}�b�v�f�[�^�̓ǂݍ��݂Ɏ��s
    }

    if (mMapmanager.ActivateGameObj(gameObjManager) == false) {
        return new Error; // �I�u�W�F�N�g�̃A�N�e�B�u���Ɏ��s
    }

    return new Playing();
}