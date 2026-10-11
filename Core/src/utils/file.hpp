#pragma once
#include "utils/debug.hpp"
#include <fstream>
#include <ios>
#include <iosfwd>
#include <sstream>
#include <string>
#include <vector>

namespace files
{
    inline std::string get_text(std::string path)
    {
        std::ifstream file(path);
        
        if (!file.is_open())
            debug::error("Failed open text file \"{}\"", path);
        
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
    inline std::vector<unsigned char> get_byte(std::string path)
    {
        std::ifstream file(path);

        if (!file.is_open())
            debug::error("Failed open bin file \"{}\"", path);

        file.seekg(0, std::ios::end);
        std::streampos file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<unsigned char> file_data(file_size);
        file.read((char*)&file_data[0], file_size);
        return file_data;
    }
}