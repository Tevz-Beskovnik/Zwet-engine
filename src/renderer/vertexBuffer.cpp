#include <vertexBuffer.h>

namespace ZWET
{
    VertexBuffer::VertexBuffer(size_t amount)
    {
        glGenBuffers(amount, &buffer);
    }

    VertexBuffer::VertexBuffer(size_t amount, std::vector<float>* positions)
    {
        float* positionsPointer = positions->data();
        int sizeOfVector = positions->size();

        glGenBuffers(amount, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(buffer, sizeOfVector * sizeof(float), (void*)positionsPointer, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VertexBuffer::~VertexBuffer()
    {

    }

    unsigned int VertexBuffer::Create(size_t amount)
    {
        unsigned int buffer;

        glGenBuffers(amount, &buffer);

        return buffer;
    }

    unsigned int VertexBuffer::Create(size_t amount, std::vector<float>* positions)
    {
        unsigned int buffer;
        float* positionsPointer = positions->data();
        int sizeOfVector = positions->size();

        glGenBuffers(amount, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeOfVector * sizeof(float), (void*)positionsPointer, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return buffer;
    }

    void VertexBuffer::bind(unsigned int buffer)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
    }

    void VertexBuffer::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
    }

    void VertexBuffer::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

     void VertexBuffer::setData(unsigned int buffer, std::vector<float>* positions)
    {
        float* positionsPointer = positions->data();
        int sizeOfVector = positions->size();

        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeOfVector, (void*)positionsPointer);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::setData(std::vector<float>* positions)
    {
        float* positionsPointer = positions->data();
        int sizeOfVector = positions->size();

        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeOfVector, (void*)positionsPointer);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}