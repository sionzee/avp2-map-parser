#ifndef AVP2TOOLS_PROCESSOR_H
#define AVP2TOOLS_PROCESSOR_H

#include "../api/Map.h"

#include <iostream>
#include <fstream>
#include <cstring>

class Processor {
public:
    [[nodiscard]] static Map* process(const std::string& path);
    static void save(const Map& map, const std::string& path);
};


#endif //AVP2TOOLS_PROCESSOR_H
