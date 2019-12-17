#ifndef AVP2MAPREADER_WORLDTREE_H
#define AVP2MAPREADER_WORLDTREE_H
#define MAX_WTNODE_CHILDREN		4

#include "utils/BinaryStream.h"

class WorldTree {
public:
    void LoadLayout(BinaryStream* stream) {
        const auto boxMin = stream->readVector();
        const auto boxMax = stream->readVector();

        /** WorldTree nodes */
        const auto nTotalNodes = stream->read<uint32_t>();

        auto idk = stream->read<uint32_t>(); // 0
        auto idk2 = stream->read<uint8_t>(); // 67
        auto idk3 = stream->read<uint8_t>(); // 8
        auto idk4 = stream->read<uint8_t>(); // 1

        /** WorldTree depth */
        const auto terrainDepth = stream->read<uint8_t>();

        uint8_t curByte = 0;
        uint8_t curBit = 8;
        // Save a bit for each node telling if it's subdivided.
        WorldTree::LoadLayout(stream, curByte, curBit);

    }

    bool LoadLayout(BinaryStream* stream, uint8_t &curByte, uint8_t &curBit) {
        bool bSubdivide;
        uint32_t i;

        // Read the next bit.
        if(curBit == 8) {
            curByte = stream->read<uint8_t>();
            curBit = 0;
        }

        bSubdivide = !!(curByte & (1<<curBit));
        curBit++;

        if(bSubdivide) {
            if(!WorldTree::Subdivide()) return false;

            for(i = 0; i < MAX_WTNODE_CHILDREN; i++) {
                if(!m_ChildrenA[i]->LoadLayout(stream, curByte, curBit))
                {
                    return false;
                }
            }
        }

        return true;
    }

private:

    WorldTree	*m_ChildrenA[MAX_WTNODE_CHILDREN];

    bool Subdivide() {
        uint32_t i;

        // Allocate..
        for(i=0; i < MAX_WTNODE_CHILDREN; i++)
        {
            m_ChildrenA[i] = new WorldTree;
        }

        return true;
    }
};

#endif //AVP2MAPREADER_WORLDTREE_H
