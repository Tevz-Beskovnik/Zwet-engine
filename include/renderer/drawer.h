#pragma once

#include <core.h>

namespace ZWET
{
    class Drawer
    {
        public:
            Drawer(unsigned int type, int first, size_t amount);

            ~Drawer();

            void setPolyCount(size_t newAmount) { amount = newAmount; };

            static void draw(unsigned int type, int first, size_t amount);
            void draw();

        private:
            unsigned int type;
            int first;
            size_t amount;
    };
}