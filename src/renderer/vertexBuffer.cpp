#include <vertexBuffer.h>

namespace ZWET
{
    VertexBuffer::VertexBuffer(size_t amount, std::vector<float>* positions)
        :polyCount(positions->size() / 11)
    {
        float* positionsPointer = positions->data();
        int sizeOfVector = positions->size();

        glGenBuffers(amount, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeOfVector * sizeof(float), positionsPointer, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &buffer);
    }

    void VertexBuffer::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
    }

    void VertexBuffer::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::setData(std::vector<float>* positions)
    {
        float* positionsPointer = positions->data();
        int sizeOfVector = positions->size();

        polyCount = positions->size() / 6;

        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeOfVector, (void*)positionsPointer);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    SharedPtr<VertexBuffer> VertexBuffer::create(size_t amount, std::vector<float>* positions)
    {
        return CreateShared<VertexBuffer>(amount, positions);
    }

    size_t& VertexBuffer::getPolyCount()
    {
        return polyCount;
    }
}