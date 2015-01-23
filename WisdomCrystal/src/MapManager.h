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
    static const std::string PATH;
    static const std::string FILENAME;
    static const std::string FILENAME_EXTENSION;

    std::array<int, 880> mMapData;
};
