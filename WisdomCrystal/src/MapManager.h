// MapManager.h

#pragma once

#include <array>
#include <boost/noncopyable.hpp>

#include "object/GameObjManager.h"


class MapManager : private boost::noncopyable {

public:
    MapManager();
    virtual ~MapManager();

    bool LoadMapDataFile(const int mapID);

    bool ActivateGameObj(GameObjManager* gameObjManager);

private:
    static const int MAX_MAP_DATA = 880;

    static const std::string PATH;
    static const std::string FILENAME;
    static const std::string FILENAME_EXTENSION;

    std::array<int, MAX_MAP_DATA> mMapData;
};
