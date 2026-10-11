#pragma once
#include <cstdlib>
#include <format>
#include <iostream>

namespace debug
{
    template <typename... Args>
    void info(std::format_string<Args...> fmt, Args&&... args)
    {
        std::cout 
            << "\x1b[32m[:)] "
            << std::vformat(fmt.get(), std::make_format_args(args...)) 
            << "\x1b[0m\n";
    }

    template <typename... Args>
    void warn(std::format_string<Args...> fmt, Args&&... args)
    {
        std::cout
            << "\x1b[33m[:|] "
            << std::vformat(fmt.get(), std::make_format_args(args...)) 
            << "\x1b[0m\n";
    }

    template <typename... Args>
    void error(std::format_string<Args...> fmt, Args&&... args)
    {
        std::cerr
            << "\x1b[31m[:(] "
            << std::vformat(fmt.get(), std::make_format_args(args...)) 
            << "\x1b[0m\n";
        std::exit(1);
    }
}