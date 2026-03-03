#include <string>
#include <vector>
#include <cstdint>

namespace string
{
    std::string cut_left(std::string str, char stop_point)
    {
        std::string result;
        int i = 0;
        for (; str[i] != stop_point; i++)
        {
            result.push_back(str[i]);
        }
        return result;
    }
    std::string cut_right(std::string str, char stop_point)
    {
        std::string result = str;
        int i = str.size();
        for (; str[i] != stop_point; i--)
        {
            result.pop_back();
        }
        return result;
    }
}