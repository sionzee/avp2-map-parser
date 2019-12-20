//
// Created by sionzee on 19. 12. 2019. Dec.
//

#ifndef AVP2TOOLS_STRINGUTILS_H
#define AVP2TOOLS_STRINGUTILS_H

#include <string>
#include <vector>

struct StringUtils {
    static void SplitToVector(std::string& value, const std::basic_string<char>& delimeter, uint& count, std::vector<std::string>& vector) {
        int position = 0;
        int lastPosition = 0;
        for(int i = 0; i < count; i++) {
            position = value.find(delimeter);
            vector.push_back(value.substr(lastPosition, position));
            lastPosition = position;
        }
    }
};

#endif //AVP2TOOLS_STRINGUTILS_H
