//
// Created by sionzee on 11. 12. 2019. Dec.
//

#include "./BinaryStream.h"

BinaryStream::BinaryStream(size_t &bufferSize, char *pBuffer) {
    this->m_pBuffer = pBuffer;
    this->m_pBufferSize = bufferSize;
    this->m_position = 0u;
}

std::string BinaryStream::readString(int length) {
    if(length == 0) return std::string();
    const auto val = std::string(&this->m_pBuffer[this->m_position], &this->m_pBuffer[this->m_position + length]);
    this->m_position += length * 2;
    return val;
}

Vector3 BinaryStream::readVector() {
    return Vector3(read<float>(), read<float>(), read<float>());
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
