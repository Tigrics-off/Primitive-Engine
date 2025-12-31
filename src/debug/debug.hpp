#include <string>

namespace debug
{
    void no_color(bool color);

    void info(std::string msg);
    void warn(std::string msg);
    void error(std::string msg);
}