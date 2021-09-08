#pragma once

#include <core.h>

namespace ZWET
{
    class Drawer
    {
        Drawer();

        ~Drawer();

        static void draw(unsigned int type, int first, size_t amount);
    };
}