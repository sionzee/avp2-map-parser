#include "./BinaryStream.h"

BinaryStream::BinaryStream(size_t &bufferSize, char *pBuffer) {
    this->m_pBuffer = pBuffer;
    this->m_pBufferSize = bufferSize;
    this->m_position = 0u;
}

std::string BinaryStream::readString(uint &length) {
    if(length == 0) return std::string();
    const auto val = std::string(&this->m_pBuffer[this->m_position], &this->m_pBuffer[this->m_position + length]);
    this->m_position += length;
    return val;
}

Vector3 BinaryStream::readVector() {
    auto x = read<float>();
    auto y = read<float>();
    auto z = read<float>();
    return Vector3(x, y, z);
}

int BinaryStream::getIndex() {
    return this->m_position;
}

char *BinaryStream::getBuffer() {
    return this->m_pBuffer;
}

void BinaryStream::writeString(std::string &value) {

}

void BinaryStream::writeVector(Vector3 &vector) {

}

void BinaryStream::readDummy(uint &length) {
    this->m_position += length;
}
