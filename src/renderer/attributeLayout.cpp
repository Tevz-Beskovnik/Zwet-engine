#include <attributeLayout.h>

namespace ZWET
{
    AttributeLayout::AttributeLayout(unsigned int& program, unsigned int& buffer)
        :program(program), buffer(buffer)
    {
    }

    void AttributeLayout::setLayout(Layout attributeLayout)
    {
        glBindBuffer(GL_ARRAY_BUFFER, attributeLayout.buffer);

        unsigned int attribute = glGetAttribLocation(attributeLayout.program, attributeLayout.nameOfAttribute.c_str());

        glEnableVertexAttribArray(attribute);

        glVertexAttribPointer(
            attribute,
            attributeLayout.size,
            attributeLayout.type,
            attributeLayout.normalise,
            attributeLayout.totalSizeInBytes,
            (void*)attributeLayout.offset
        );
    }
}