#include "./lib/catch.hpp"
#include "../src/core/Processor.h"

TEST_CASE("SimpleWorld test", "[simple-world]") {
    const std::string simpleWorldPath = std::string(MAPS_PATH) + std::string("/simpleworld.dat");
    auto map = Processor::process(simpleWorldPath);

    REQUIRE(map->getDATVersion() == 70);
    REQUIRE(map->getWorldInfo() == "INFOSTRINGHERE");
    REQUIRE(map->getMapName() == "simpleworld");
    delete map;
}