//
// Created by sionzee on 19. 12. 2019. Dec.
//

#ifndef AVP2TOOLS_WORLDBSP_H
#define AVP2TOOLS_WORLDBSP_H

#include <assert.h>
#include "../utils/BinaryStream.h"

struct WorldBsp {

    std::string worldName;

    void Load(BinaryStream* stream) {
        // seems to be object identification, for physics it is 2, for translucent 20
        auto objectType = stream->read<uint32_t>();

        // most probably worlds flags
        auto worldFlags = stream->read<uint32_t>();
        assert((worldFlags & 0xFFFF0000) == 0);

        uint worldNameLength = stream->read<uint16_t>();
        worldName = stream->readString(worldNameLength);

        auto pointsCount = stream->read<uint32_t>();
        auto planesCount = stream->read<uint32_t>();
        auto surfacesCount = stream->read<uint32_t>();

        auto portalsCount = stream->read<uint32_t>(); // 0 NOT_SUPPORTED_BY_ENGINE
        auto poliesCount = stream->read<uint32_t>();
        auto leafsCount = stream->read<uint32_t>(); // 0 NOT_SUPPORTED_BY_ENGINE
        auto vertsCount = stream->read<uint32_t>();
        auto totalVisListSize = stream->read<uint32_t>(); // 0 NOT_SUPPORTED
        auto leafListsCount = stream->read<uint32_t>(); // 0 NOT_SUPPORTED
        auto nodesCount = stream->read<uint32_t>();

        auto idkNumber2 = stream->read<uint32_t>(); // 0
        auto idkNumber3 = stream->read<uint32_t>(); // 6

        auto minBox = stream->readVector();
        auto maxBox = stream->readVector();

    }
};

#endif //AVP2TOOLS_WORLDBSP_H
