//
// Created by sionzee on 11. 12. 2019. Dec.
//

#ifndef AVP2MAPREADER_VECTOR_H
#define AVP2MAPREADER_VECTOR_H
#include <sstream>

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    friend std::ostream& operator<<(std::ostream& cout, const Vector3& vec) {
        std::ostringstream ss;
        ss << "X: " << vec.x << ", Y: " << vec.y << ", Z: " << vec.z;
        return cout << ss.str();
    }

    bool operator==(const Vector3 &rhs) const {
        return x == rhs.x &&
               y == rhs.y &&
               z == rhs.z;
    }

    bool operator!=(const Vector3 &rhs) const {
        return !(rhs == *this);
    }
};

#endif //AVP2MAPREADER_VECTOR_H
