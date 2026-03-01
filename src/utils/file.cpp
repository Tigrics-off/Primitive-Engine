#include <fstream>
#include <sstream>
#include <vector>
#include "utils/debug.hpp"

namespace file
{
    std::string read(std::string name)
    {
        std::ifstream file(name);

        if (!file.is_open()) debug::error("Failed open file " + name);
        
        std::stringstream buf;
        buf << file.rdbuf();

        return buf.str();
    }
    std::vector<char> read_bin(std::string name)
    {
        std::ifstream file(name, std::ios::binary);
        if (!file.is_open()) debug::error("Failed open file " + name);

        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        if (size <= 0) debug::error("Empty or broke file " + name);

        std::vector<char> buffer(size);
        if (!file.read(buffer.data(), size))
        {
            debug::error("Failed read file " + name);
        }
        
        return buffer;
    }
}