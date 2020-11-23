#pragma once

#include "Graphics.h"

class Console
{
    public:
        void drawToConsole(Graphics Graphics);
    
    private:
        const std::string colors[9] = {
            "\e[0m", "\e[1;30m", "\e[1;31m",
            "\e[1;32m", "\e[1;33m", "\e[1;34m",
            "\e[1;35m", "\e[1;36m", "\e[1;37m"};

    private:
        int combineIntOR(int a, int b);
};