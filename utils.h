#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "privlevel.h"

namespace utilities {
    class Utils {
    public:
       static std::string toLowerCase(std::string);
       static std::string levelToString(privLevel);
       static bool contains(std::vector<std::string>, std::string);
   };
}
#endif