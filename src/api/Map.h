#ifndef AVP2MAPREADER_MAP_H
#define AVP2MAPREADER_MAP_H

#include "../types/Vector.h"
#include "./WorldFlags.h"

#include <string>
#include <vector>


/** Information from BSP */
struct World {
private:
    /** World Flags */
    WorldFlags m_flags;

    /** Name of the world */
    std::string m_worldName;
};

struct Map {
private:
    /** Version of DAT file */
    uint m_dataVersion;

    /** This is Filename and the filename is used as MapName in game */
    std::string m_mapName;

    /** Size of DAT file */
    uint m_mapFileSize;

    /** World info (MasterPalette, WorldName, etc...) */
    std::string m_worldInfo;

    /** Min position box of Main World */
    Vector3 m_worldBorderMin;

    /** Max position box of Main World */
    Vector3 m_worldBorderMax;

    /** Sub worlds (BSPs) */
    std::vector<World> m_subWorlds;


public:

    Map(uint mDataVersion, const std::string &mMapName, uint mMapFileSize, const std::string &mWorldInfo,
        const Vector3 &mPositionBoxMin, const Vector3 &mPositionBoxMax,
        const std::vector<World> &mSubWorlds);

    [[nodiscard]] uint getDATVersion() const;
    [[nodiscard]] std::string getMapName() const;
    [[nodiscard]] uint getMapFileSize() const;
    [[nodiscard]] std::string getWorldInfo() const;
    [[nodiscard]] Vector3 getWorldBorderMin() const;
    [[nodiscard]] Vector3 getWorldBorderMax() const;
    [[nodiscard]] Vector3 getWorldOffset() const;

    std::string toString() {
        auto map = this;
        std::ostringstream ss;
        ss << ".DAT version: " << map->m_dataVersion << std::endl;
        ss << "Map name: " << map->m_mapName << std::endl;
        ss << "Map size: " << map->m_mapFileSize << " Bytes" << std::endl;
        ss << "World Border from " << map->m_worldBorderMin << " to " << map->m_worldBorderMax << std::endl;
        return ss.str();
    }
};


#endif //AVP2MAPREADER_MAP_H
