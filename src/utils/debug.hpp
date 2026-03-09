#pragma once
#include <stdlib.h>
#include <string>

namespace debug
{
    void no_color(bool b);
    
    void info(std::string msg);
    void warn(std::string msg);
    void error(std::string msg);
}