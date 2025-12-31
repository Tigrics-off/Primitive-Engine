#include <iostream>
#include <string>

bool nocolor = false;

namespace debug
{
    void no_color(bool color) {nocolor = color;}

    void info(std::string msg)
    {
        if (nocolor) std::cout << "[:)]" << msg << std::endl;
        else std::cout << "\e[0;32m[:)]" << msg << "\e[0;37m" << std::endl;
    }
    void warn(std::string msg)
    {
        if (nocolor) std::cout << "[:|]" << msg << std::endl;
        else std::cout << "\e[0;33m[:)]" << msg << "\e[0;37m" << std::endl;
    }
    void error(std::string msg)
    {
        if (nocolor) std::cout << "[:(]" << msg << std::endl;
        else std::cout << "\e[0;31m[:(]" << msg << "\e[0;37m" << std::endl;
    }
}