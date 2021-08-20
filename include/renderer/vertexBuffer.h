#pragma once

#include <core.h>

namespace ZWET
{
    class VertexBuffer
    {
        public:
            VertexBuffer(size_t amount);
            VertexBuffer(size_t amount, std::vector<float>* positions);

            ~VertexBuffer();

            static unsigned int Create(size_t amount);
            static unsigned int Create(size_t amount, std::vector<float>* positions);

            static void bind(unsigned int buffer);
            void bind();

            static void unbind();

            static void setData(unsigned int buffer, std::vector<float>* positions);
            void setData(std::vector<float>* positions);

        private: 
            unsigned int buffer;
            int lol;
    };
}