#ifndef AVP2MAPREADER_FILEMARKER_H
#define AVP2MAPREADER_FILEMARKER_H

class BinaryStream;
class CFileMarker
{
public:
    explicit CFileMarker(BinaryStream *streamReader);

private:

    char	    *m_pBuffer;
    int		    m_MarkerPos;
};

#endif //AVP2MAPREADER_FILEMARKER_H
