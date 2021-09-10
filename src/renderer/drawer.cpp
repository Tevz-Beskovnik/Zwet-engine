#include <drawer.h>

namespace ZWET
{
    Drawer::Drawer(unsigned int type, int first, size_t amount)
        :type(type), first(first), amount(amount)
    {
        ;
    }

    void Drawer::draw(unsigned int type, int first, size_t amount)
    {
        glDrawArrays(type, first, amount);
    }

    void Drawer::draw()
    {
        glDrawArrays(type, first, amount);
    }
}