#include <attributeLayout.h>

namespace ZWET
{
    void AttributeLayout::setLayout(layout attributeLayout)
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