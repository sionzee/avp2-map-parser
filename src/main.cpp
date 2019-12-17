
#include "./core/Processor.h"

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>


typedef std::vector<std::string> CommandLineStringArgs;

int main(int argc, char *argv[]) {
    std::string worldPath;
    int i;

    CommandLineStringArgs cmdlineStringArgs(&argv[0], &argv[0 + argc]);
    for (const auto &arg : cmdlineStringArgs) {
        if (arg.starts_with("--world=")) {
            worldPath = arg.substr(std::string("--world=").size());
        }
    }

    if (worldPath.empty()) {
        std::cout << "World path was not specified. Please add --world='absolute_path' option." << std::endl;
        return 1;
    }

    auto extension = std::filesystem::path(worldPath).extension().string();

    if (extension != ".dat") {
        std::cout << "Expected .dat extension, got " << extension << std::endl;
        return 1;
    }

    auto map = Processor::process(worldPath);


    std::cout << map << std::endl;
    delete map;

    return 0;

}