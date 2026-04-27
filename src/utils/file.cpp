#include <fstream>
#include <sstream>
#include <vector>

#include "utils/debug.hpp"

namespace file
{
    std::string read(std::string name)
    {
        std::ifstream file(name);
        
        std::stringstream buf;
        buf << file.rdbuf();

        return buf.str();
    }
    std::vector<char> read_bin(std::string name)
    {
        if (name.empty())
        {
            debug::warn("read_bin called with empty name");
            return {};
        }
        
        std::ifstream file(name, std::ios::binary);
        if (!file.is_open())
        {
            debug::warn("Failed open file %s", name.c_str());
            return {};
        }
        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        std::vector<char> buffer(size);
        if (!file.read(buffer.data(), size))
            debug::error("Failed read file %s", name.c_str());
        
        return buffer;
    }
}