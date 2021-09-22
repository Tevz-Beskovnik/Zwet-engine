#pragma once

#include <core.h>
#include <utils.h>

namespace ZWET
{
    class Drawer
    {
        public:
            Drawer(unsigned int type, int first, size_t amount);

            ~Drawer();

            void setPolyCount(size_t newAmount) { amount = newAmount; };

            void setDrawType(unsigned int newType);

            void setFirst(int newFirst);

            static void draw(unsigned int type, int first, size_t amount);
            void draw();

            static SharedPtr<Drawer> create(unsigned int type, int first, size_t amount);

        private:
            unsigned int type;
            int first;
            size_t amount;
    };
}