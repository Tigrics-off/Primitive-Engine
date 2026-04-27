#pragma once
#include <stdlib.h>

namespace debug
{
    void no_color(bool b);
    
    void info(const char* log, ...);
    void warn(const char* log, ...);
    void error(const char* log, ...);
}