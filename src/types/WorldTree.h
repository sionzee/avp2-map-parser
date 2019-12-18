#ifndef AVP2MAPREADER_WORLDTREE_H
#define AVP2MAPREADER_WORLDTREE_H
#define MAX_WTNODE_CHILDREN		4

#include <optional>
#include "../utils/BinaryStream.h"

struct WorldTreeNode {
public:
    Vector3 borderBoxMin;
    Vector3 borderBoxMax;

    WorldTreeNode *m_Children[2][2];
    WorldTreeNode *m_ChildrenA[MAX_WTNODE_CHILDREN];
    WorldTreeNode *m_pParent;

    void setBorderBox(Vector3 &min, Vector3 &max) {
        borderBoxMin = min;
        borderBoxMax = max;
    }

    bool Subdivide() {
        uint32_t i;

        // Allocate..
        for(i=0; i < MAX_WTNODE_CHILDREN; i++)
        {
            m_ChildrenA[i] = new WorldTreeNode;
            if(!m_ChildrenA[i])
            {
                return false;
            }

            m_ChildrenA[i]->m_pParent = this;
        }

        return true;
    }

    bool loadLayout(BinaryStream* stream, uint8_t &curByte, uint8_t &curBit) {
        bool bSubdivide;
        uint32_t i;

        /** Read the next bit */
        if(curBit == 8) {
            curByte = stream->read<uint8_t>();
            curBit = 0;
        }

        bSubdivide = (curByte & (1u << curBit)) != 0;
        curBit++;

        if(bSubdivide) {
            if(!Subdivide()) return false;

            for(i=0; i < MAX_WTNODE_CHILDREN; i++)
            {
                if(!m_ChildrenA[i]->loadLayout(stream, curByte, curBit))
                {
                    return false;
                }
            }
        }

        return true;
    }
};

struct WorldTree {
public:
    std::optional<WorldTreeNode> rootNode;

    void loadLayout(BinaryStream* stream) {
        rootNode = WorldTreeNode();

        auto borderBoxMin = stream->readVector();
        auto borderBoxMax = stream->readVector();
        rootNode->setBorderBox(borderBoxMin, borderBoxMax);

        /** WorldTree nodes */
        const auto nTotalNodes = stream->read<uint32_t>();

        /** On all tested maps it is 0 0 0 0 */
        const auto idk = stream->read<uint32_t>();

        /** Right now comes in bites shifting */
        uint8_t curByte = 0;
        uint8_t curBit = 8;
        rootNode.value().loadLayout(stream, curByte, curBit);
    }

    WorldTree() = default;
};

#endif //AVP2MAPREADER_WORLDTREE_H
