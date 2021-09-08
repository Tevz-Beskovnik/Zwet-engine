#include <drawer.h>

namespace ZWET
{
    void Drawer::draw(unsigned int type, int first, size_t amount)
    {
        glDrawArrays(type, first, amount);
    }
}