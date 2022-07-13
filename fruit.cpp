#include "fruit.h"
#include <QRandomGenerator>

Fruit::Fruit()
{
    m_x = 0;
    m_y = 0;
}

void Fruit::place(int x, int y)
{   
    m_x = x;
    m_y = y;
}

QPoint Fruit::position() const
{
    return {m_x, m_y};
}
