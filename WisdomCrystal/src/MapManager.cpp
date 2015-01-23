// MapManager.cpp

// Includes
#include "MapManager.h"
#include "object/GameObjManager.h"
#include "util/CSVUtil.h"
#include "WisdomCrystal.h"

#pragma warning (disable: 4005) // C4005 警告無視
#include <boost/lexical_cast.hpp>
#pragma warning (default: 4005) // C4005 警告解除


// Constants
const std::string MapManager::PATH               = "resources/map/";
const std::string MapManager::FILENAME           = "map_";
const std::string MapManager::FILENAME_EXTENSION = ".csv";


MapManager::MapManager() : mMapData() {
    // empty
}


MapManager::~MapManager() {
    // empty
}


bool MapManager::LoadMapDataFile(const int mapID) {

    std::string filePath;

    filePath = filePath.erase();
    filePath += PATH;
    filePath += FILENAME;
    filePath += boost::lexical_cast<std::string>(mapID);
    filePath += FILENAME_EXTENSION;


    if (CSVUtil::ImportCSVData(filePath, &mMapData) == false) {
        return false; // CSV データの読み込みに失敗
    }

    if (mMapData.size() != MAX_MAP_CHIP) {
        return false; // 規定のマップデータの大きさと違う
    }

    return true;
}


bool MapManager::ActivateGameObj(GameObjManager* gameObjManager) {
    for (int j = 0; j < MAP_ROW; ++j) {
        for (int i = 0; i < MAP_COL; ++i) {

            if (gameObjManager->Activate(i * MAP_CHIP_WIDTH,
                                         j * MAP_CHIP_HEIGHT,
                                         mMapData.at(i + j * MAP_COL)) == false) {

                return false;
            }

        }
    }

    return true;
}
