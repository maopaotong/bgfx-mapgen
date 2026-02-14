#pragma once
#include <iostream>
namespace mg
{
    struct LogUtil
    {

        static void log(std::string msg)
        {
            std::cout << msg << std::endl;
        }
    };
};