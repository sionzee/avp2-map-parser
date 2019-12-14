//
// Created by sionzee on 14. 12. 2019. Dec.
//

#include "FileMarker.h"
#include "BinaryStream.h"

CFileMarker::CFileMarker(BinaryStream *streamReader) {
    m_MarkerPos = streamReader->getIndex();
    m_pBuffer = streamReader->getBuffer();
    streamReader->read<uint32_t>();
}
