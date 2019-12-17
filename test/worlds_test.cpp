#include "./lib/catch.hpp"
#include "../src/core/Processor.h"

TEST_CASE("SimpleWorld test", "[simple-world]") {
    const std::string simpleWorldPath = std::string(MAPS_PATH) + std::string("/Worlds/simple_world.dat");
    auto map = Processor::process(simpleWorldPath);

    REQUIRE(map->dataVersion == 70);
    REQUIRE(map->worldInfoString == "INFOSTRINGHERE");
    REQUIRE(map->name == "simple_world");
    REQUIRE(map->worldBorderMin == Vector3(-128, -128, -128));
    REQUIRE(map->worldBorderMax == Vector3(128, 128, 128));

    std::cout << map->toString() << std::endl;

    delete map;
}