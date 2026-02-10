#include <iostream>
#include <stdlib.h>
#include <string>

namespace debug
{
    bool no_col = false;
    void no_color(bool b)
    {
        no_col = b;
    }
    
    void info(std::string msg)
    {
        if (no_col) std::cout << "[:)]" << msg << std::endl;
        else std::cout << "\e[0;30m[:)]" << msg << "\e[0m" << std::endl;
    }
    void warn(std::string msg)
    {
        if (no_col) std::cout << "[:|]" << msg << std::endl;
        else std::cout << "\e[0;33m[:|]" << msg << "\e[0m" << std::endl;
    }
    void error(std::string msg)
    {
        if (no_col) std::cout << "[:(]" << msg << std::endl;
        else std::cout << "\e[0;31m[:(]" << msg << "\e[0m" << std::endl;

        abort();
    }
}