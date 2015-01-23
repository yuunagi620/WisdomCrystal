// MapManager.h

#pragma once

#include <boost/noncopyable.hpp>

#include "object/GameObjManager.h"


class MapManager : private boost::noncopyable {

public:
    MapManager();

    bool LoadMapDataFile(int mapID);
    bool ActivateGameObj(GameObjManager* gameObjManager);

private:
    static const std::string PATH;
    static const std::string FILENAME;
    static const std::string FILENAME_EXTENSION;

    static std::vector<int> mMapData;
};
