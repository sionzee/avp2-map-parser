#include "./lib/catch.hpp"
#include "../src/core/Processor.h"

TEST_CASE("SimpleWorld test", "[simple-world]") {
    const std::string simpleWorldPath = std::string(MAPS_PATH) + std::string("/Worlds/simple_world.dat");
    auto map = Processor::process(simpleWorldPath);

    REQUIRE(map->getDATVersion() == 70);
    REQUIRE(map->getWorldInfo() == "INFOSTRINGHERE");
    REQUIRE(map->getMapName() == "simple_world");
    REQUIRE(map->getWorldBorderMin() == Vector3(-128, -128, -128));
    REQUIRE(map->getWorldBorderMax() == Vector3(128, 128, 128));

    std::cout << map->toString() << std::endl;

    delete map;
}