// MapManager.h

#pragma once

#include <boost/noncopyable.hpp>

class MapManager : private boost::noncopyable {

public:
    static MapManager *GetInstance();

    bool LoadMapDataFile(int mapID);
    bool ActivateGameObj();

private:
    static const std::string PATH;
    static const std::string FILENAME;
    static const std::string FILENAME_EXTENSION;

    static MapManager mMapManager;
    static std::vector<int> mMapData;

    MapManager(); // インスタンス生成不可

};
