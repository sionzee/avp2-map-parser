#ifndef AVP2MAPREADER_MAP_H
#define AVP2MAPREADER_MAP_H

#include "../types/Vector.h"
#include "./WorldFlags.h"

#include <string>
#include <vector>


/** Information from BSP */
struct World {
    /** World Flags */
    WorldFlags flags;

    /** Name of the world */
    std::string worldName;
};

struct Map {
public:

    /** Version of DAT file */
    const uint dataVersion;

    /** This is Filename and the filename is used as MapName in game */
    const std::string name;

    /** Size of DAT file */
    const uint fileSize;

    /** World info (MasterPalette, WorldName, etc...) */
    std::string worldInfoString;

    /** Min position box of Main World */
    Vector3 worldBorderMin;

    /** Max position box of Main World */
    Vector3 worldBorderMax;

    /** Sub worlds (BSPs) */
    std::vector<World> subWorlds;

    std::string toString() {
        auto map = this;
        std::ostringstream ss;
        ss << ".DAT version: " << map->dataVersion << std::endl;
        ss << "Map name: " << map->name << std::endl;
        ss << "Map fileSize: " << map->fileSize << " Bytes" << std::endl;
        ss << "World Border from " << map->worldBorderMin << " to " << map->worldBorderMax << std::endl;
        return ss.str();
    }
};


#endif //AVP2MAPREADER_MAP_H
