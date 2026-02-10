#include <fstream>
#include <sstream>
#include "../debug/debug.hpp"

namespace file
{
    std::string read(std::string name)
    {
        std::ifstream file(name);

        if (!file.is_open()) debug::error("Failed open file: " + name);
        
        std::stringstream buf;
        buf << file.rdbuf();

        return buf.str();
    }
}