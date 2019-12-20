//
// Created by sionzee on 19. 12. 2019. Dec.
//

#ifndef AVP2TOOLS_WORLDBSP_H
#define AVP2TOOLS_WORLDBSP_H
#define MAX_WORLDPOLY_VERTS 40

#include <assert.h>
#include <array>
#include <iterator>
#include "../utils/BinaryStream.h"
#include "../utils/StringUtils.h"

// LTPlane
struct WorldPlane {
    int index;
    Vector3 normal;
    float distance;
};

//DiskSurface
struct WorldSurface {
    int index;
    uint32_t flags;
    uint16_t texture;
    uint16_t textureFlags;
};

struct WorldNode {
    int arrayIndex;
    uint32_t index;
    int sides[2];
};

struct WorldPoly {
    int index;
    uint32_t indexAndVertices;
    WorldSurface surface;
    WorldPlane plane;
    Vector3 vertices[MAX_WORLDPOLY_VERTS];

    Vector3* GetVertices() {
        return vertices;
    }

    Vector3& GetVertex(uint32_t& i) {
        return vertices[i];
    }

    uint32_t GetIndex() {
        return (indexAndVertices & 0xFFFFFF00) >> 8;
    }

    void SetIndex(uint32_t index) {
        indexAndVertices = (indexAndVertices & 0xFF) | (index << 8);
    }

    uint32_t GetNumVertices() {
        return (indexAndVertices & 0xFF);
    }

    void SetNumVertices(uint32_t nVertices)	{
        indexAndVertices = (indexAndVertices & 0xFFFFFF00) | (nVertices & 0xFF);
    }
};




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
        auto worldTranslation = stream->readVector();

        // sum of all names length of all textures in this bsp eg.: "test.dtx".length + "black.dtx".length
        auto namesLength = stream->read<uint32_t>();

        // size of used textures
        auto texturesCount = stream->read<uint32_t>();

        std::vector<std::string> textureList = stream->readStringArray(namesLength, texturesCount);

        int i, j;
        WorldPoly polies[poliesCount];
        WorldPlane planes[planesCount];
        WorldSurface surfaces[surfacesCount];
        WorldNode nodes[nodesCount];
        Vector3 points[pointsCount];

        for(i = 0; i < poliesCount; i++) {
            auto vertices = stream->read<uint16_t>();
            auto poly = WorldPoly {};
            poly.SetIndex(i);
            poly.SetNumVertices(vertices);
            polies[i] = poly;
        }

        for(i = 0; i < planesCount; i++) {
            auto normal = stream->readVector();
            auto distance = stream->read<float>();
            planes[i] = WorldPlane {i, normal, distance};
        }

        for(i = 0; i < surfacesCount; i++) {
            auto flags = stream->read<uint32_t>();
            auto textureIndex = stream->read<uint16_t>();
            auto textureFlags = stream->read<uint16_t>();
            surfaces[i] = WorldSurface {i, flags, textureIndex, textureFlags};
        }

        // ----- ABOVE VERIFIED -----

        for(i = 0; i < poliesCount; i++) {
            auto poly = polies[i];

            auto nSurfaceIndex = stream->read<uint32_t>();
            auto nPlaneIndex = stream->read<uint32_t>();

            poly.surface = surfaces[nSurfaceIndex];
            poly.plane = planes[nPlaneIndex];

            uint32_t size = sizeof(uint32_t) * (2 + poly.GetNumVertices());
            bool test = true;
//            stream->readVectorArray()
//
//
//            for(j = 0; j < poly.GetNumVertices(); j++) {
//                poly.GetVertices()[j] = &points[];
//            }
//
//            poly.GetVertices()
//           stream->readDummy(sizeof(uint32_t) * (2 + poly.nVertices));
        }

        for(i = 0; i < nodesCount; i++) {
            auto index = stream->read<uint32_t>();
            stream->readDummy(2); // 0 (WORD) - the leaves are no longer read in by the engine

            auto node = WorldNode {i, index};
            node.sides[0] = stream->read<uint32_t>();
            node.sides[1] = stream->read<uint32_t>();
            nodes[i] = node;
        }

        for(i = 0; i < pointsCount; i++) {
            points[i] = stream->readVector();
        }

        // Root poly index (index of pWorld->m_RootNode)
        auto rootPolyIndex = stream->read<uint32_t>();

        // Sections, of which have been removed, so always just write out 0. This should
        // be removed in the future
        stream->readDummy(4);


    }
};

#endif //AVP2TOOLS_WORLDBSP_H
