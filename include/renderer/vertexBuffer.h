#pragma once

#include <core.h>
#include <utils.h>

namespace ZWET
{
    class VertexBuffer
    {
        public:
            VertexBuffer(size_t amount);
            VertexBuffer(size_t amount, std::vector<float>* positions);

            ~VertexBuffer();

            static SharedPtr<VertexBuffer> create(size_t amount, std::vector<float>* positions);

            void bind();

            static void unbind();

            void setData(std::vector<float>* positions);

            unsigned int getBuffer() { return buffer; };

        private: 
            unsigned int buffer;
    };
}