#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <stdlib.h>

namespace debug
{
    bool no_col = false;
    void no_color(bool b)
    {
        no_col = b;
    }
    
    void info(const char* log, ...)
    {
        char msg[2048];
        va_list args;
        va_start(args, log);
        vsnprintf(msg, sizeof(msg), log, args);
        va_end(args);

        if (no_col)
            std::cout << "[:)] " << msg << std::endl;
        else
            std::cout << "\e[0;32m[:)] " << msg << "\e[0m" << std::endl;
    }
    void warn(const char* log, ...)
    {
        char msg[2048];
        va_list args;
        va_start(args, log);
        vsnprintf(msg, sizeof(msg), log, args);
        va_end(args);

        if (no_col)
            std::cout << "[:|] " << msg << std::endl;
        else
            std::cout << "\e[0;33m[:|] " << msg << "\e[0m" << std::endl;
    }
    void error(const char* log, ...)
    {
        char msg[2048];
        va_list args;
        va_start(args, log);
        vsnprintf(msg, sizeof(msg), log, args);
        va_end(args);

        if (no_col)
            std::cout << "[:(] " << msg << std::endl;
        else
            std::cout << "\e[0;31m[:(] " << msg << "\e[0m" << std::endl;

        abort();
    }
}