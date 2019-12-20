//
// Created by sionzee on 20. 12. 2019. Dec.
//

#ifndef AVP2TOOLS_MESH_H
#define AVP2TOOLS_MESH_H

#include <array>
#include "../types/Vector.h"

struct Mesh {
    size_t nVertices;
    Vector3* vertices;

    size_t nNormals;
    Vector3* normals;
};

#endif //AVP2TOOLS_MESH_H
