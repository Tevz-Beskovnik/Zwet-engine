#include <drawer.h>

namespace ZWET
{
    Drawer::Drawer(unsigned int type, int first, size_t amount)
        :type(type), first(first), amount(amount)
    {
        ;
    }

    Drawer::~Drawer()
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

    void Drawer::setDrawType(unsigned int newType)
    {
        type = newType;
    }

    void Drawer::setFirst(int newFirst)
    {
        first = newFirst;
    }

    SharedPtr<Drawer> Drawer::create(unsigned int type, int first, size_t amount)
    {
        return CreateShared<Drawer>(type, first, amount);
    }
}