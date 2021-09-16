#pragma once

#include <core.h>
#include <utils.h>

namespace ZWET
{
    struct Layout
    {
        unsigned int& program;
        unsigned int& buffer;
        std::string nameOfAttribute; 
        int size; 
        unsigned int type; 
        unsigned int normalise;
        int totalSizeInBytes; 
        ptrdiff_t offset;
    };

    class AttributeLayout
    {
        public:
            AttributeLayout(unsigned int& program, unsigned int& buffer);

            ~AttributeLayout();

            static void setLayout(Layout attribLayout);

        private:
            unsigned int& program;
            unsigned int& buffer;
    };
}