#ifndef AVP2MAPREADER_DATASTREAMREADER_H
#define AVP2MAPREADER_DATASTREAMREADER_H


#include <string>
#include <cstdint>
#include "../types/Vector.h"

class BinaryStream {
private:
    char* m_pBuffer;
    uint m_position;
    size_t m_pBufferSize;
public:
    explicit BinaryStream(size_t& bufferSize, char *pBuffer);

    std::string readString(uint &length);
    void writeString(std::string& value);

    Vector3 readVector();
    void writeVector(Vector3& vector);

    void readDummy(uint &length);

    int getIndex();
    char* getBuffer();

    template <typename T>
    bool canWrite(T) {
        auto size = sizeof(T);
        if((this->m_pBufferSize - this->m_position) >= size) return true;
        try {
            // realloc
            char* buffer = new char[this->m_pBufferSize + 100];
            std::copy(m_pBuffer, m_pBuffer + m_pBufferSize, buffer);
            delete [] m_pBuffer;
            m_pBuffer = buffer;
            m_pBufferSize += 100;
            return true;
        } catch(std::bad_alloc&) {
            return false;
        }
    }

    template <typename T>
    void write(T& value) {
        if(!canWrite(value)) return;
        std::copy(&value, &value + sizeof(T), this->m_pBuffer[this->m_position]);
        this->m_position += sizeof(T);
    }

    template<typename T>
    T read() {
        const auto val = *reinterpret_cast<const T*>(&this->m_pBuffer[this->m_position]);
        this->m_position += sizeof(T);
        return val;
    }
};


#endif //AVP2MAPREADER_DATASTREAMREADER_H
