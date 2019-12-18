#include "./Processor.h"
#include "../utils/BinaryStream.h"
#include "../utils/FileMarker.h"
#include "../api/Map.h"
#include "../types/WorldTree.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>
#include <vector>
#include <cstdint>

#define AVP2_DAT_VERSION 70

[[nodiscard]] Map* Processor::process(const std::string& path) {
    std::cout << "Opening file \"" << path << "\"" << std::endl;

    std::ifstream file(path, std::ifstream::binary);
    if (!file.is_open()) {
        std::cerr << "Cannot open the world file. [Error: " << strerror(errno) << "]" << std::endl;
        return nullptr;
    }

    file.seekg(0, std::ifstream::end);
    size_t length = file.tellg();
    file.seekg(0, std::ifstream::beg);

    char *buffer = new char[length];
    std::cout << "Reading " << length << " characters... ";
    file.read(buffer, length);

    if (file) std::cout << "all characters read successfully." << std::endl;
    else {
        std::cout << "error: only " << file.gcount() << " could be read" << std::endl;
        file.close();
        return nullptr;
    }

    file.close();

    auto stream = new BinaryStream(length, buffer);
    auto packerVersion = stream->read<uint32_t>();

    if (packerVersion != AVP2_DAT_VERSION) {
        std::cout << "This tool supports only version " << AVP2_DAT_VERSION << std::endl;
        return nullptr;
    }

    int i;

    // Markers
    CFileMarker objectListMarker(stream);
    CFileMarker blindDataMarker(stream);
    CFileMarker lightGridMarker(stream);
    CFileMarker physicsDataMarker(stream);
    CFileMarker particleDataMarker(stream);
    CFileMarker renderDataMarker(stream);

    // Dummy
    stream->read<uint32_t>();
    stream->read<uint32_t>();
    stream->read<uint32_t>();
    stream->read<uint32_t>();

    // World Info Length
    auto worldCustomInfoLength = stream->read<uint32_t>();

    // World custom info
    auto worldCustomInfo = stream->readString(worldCustomInfoLength);

    // Lightmap Grid Size
    auto lightGridSize = stream->read<float>();

    // World Borders
    auto worldBorderMin = stream->readVector();
    auto worldBorderMax = stream->readVector();

    // WorldTree layout;
    WorldTree worldTree;
    worldTree.loadLayout(stream);

    // Sub-Worlds
    auto totalSubWorlds = stream->read<uint8_t>();
//
//    for(i = 0; i < totalSubWorlds; i++) {
//        //dummy 4 bytes
//        stream->read<uint32_t>();
//
//    }

    delete stream;
    delete[] buffer;

    return new Map {
            .dataVersion = packerVersion,
            .name = std::filesystem::path(path).stem(),
            .fileSize = uint(length),
            .worldInfoString = worldCustomInfo,
            .worldBorderMin = worldBorderMin,
            .worldBorderMax = worldBorderMax,
            .subWorlds = std::vector<World>()
    };
}

void Processor::save(const Map &map, const std::string &path) {

}
