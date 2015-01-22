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
        return new Error; // �}�b�v�f�[�^�̓ǂݍ��݂Ɏ��s
    }

    if (MapManager::GetInstance()->ActivateGameObj() == false) {
        return new Error; // �I�u�W�F�N�g�̃A�N�e�B�u���Ɏ��s
    }

    return new Playing();
}