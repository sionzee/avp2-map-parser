//
// Created by sionzee on 12. 12. 2019. Dec.
//

#ifndef AVP2MAPREADER_MAP_H
#define AVP2MAPREADER_MAP_H


#include <string>
#include <vector>
#include "../types/Vector.h"
#include "WorldFlags.h"


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
    Vector3 m_positionBoxMin;

    /** Max position box of Main World */
    Vector3 m_positionBoxMax;

    /** Offset from this world to the source world */
    Vector3 m_worldOffset;

    /** Sub worlds (BSPs) */
    std::vector<World> m_subWorlds;


public:

    Map(uint mDataVersion, const std::string &mMapName, uint mMapFileSize, const std::string &mWorldInfo,
        const Vector3 &mPositionBoxMin, const Vector3 &mPositionBoxMax, const Vector3 &mWorldOffset,
        const std::vector<World> &mSubWorlds);

    [[nodiscard]] uint getDATVersion() const;
    [[nodiscard]] std::string getMapName() const;
    [[nodiscard]] uint getMapFileSize() const;
    [[nodiscard]] std::string getWorldInfo() const;


    friend std::ostream& operator<<(std::ostream& cout, const Map& map) {
        std::ostringstream ss;
        ss << ".DAT version: " << map.m_dataVersion << std::endl;
        ss << "Map name: " << map.m_mapName << std::endl;
        ss << "Map size: " << map.m_mapFileSize << " Bytes" << std::endl;
        return cout << ss.str();
    }
};


#endif //AVP2MAPREADER_MAP_H
