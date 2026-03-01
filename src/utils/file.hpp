#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include "utils/debug.hpp"

namespace file
{
    std::string read(std::string name);
    std::vector<char> read_bin(std::string name);
}