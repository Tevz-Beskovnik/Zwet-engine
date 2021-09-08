#pragma once

#include <core.h>
#include <utils.h>

namespace ZWET
{
    struct layout
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
        AttributeLayout();

        ~AttributeLayout();

        static void setLayout(layout attribLayout);
    };
}