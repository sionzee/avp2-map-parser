#include "Map.h"

uint Map::getDATVersion() const {
    return m_dataVersion;
}

std::string Map::getMapName() const {
    return m_mapName;
}

uint Map::getMapFileSize() const {
    return m_mapFileSize;
}

std::string Map::getWorldInfo() const {
    return m_worldInfo;
}

Map::Map(uint mDataVersion, const std::string &mMapName, uint mMapFileSize, const std::string &mWorldInfo,
         const Vector3 &mPositionBoxMin, const Vector3 &mPositionBoxMax, const Vector3 &mWorldOffset,
         const std::vector<World> &mSubWorlds) : m_dataVersion(mDataVersion), m_mapName(mMapName),
                                                 m_mapFileSize(mMapFileSize), m_worldInfo(mWorldInfo),
                                                 m_positionBoxMin(mPositionBoxMin), m_positionBoxMax(mPositionBoxMax),
                                                 m_worldOffset(mWorldOffset), m_subWorlds(mSubWorlds) {}
