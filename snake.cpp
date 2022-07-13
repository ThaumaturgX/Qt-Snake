#include "snake.h"

Snake::Snake()
{
    QPoint p(0,0);
    coords.push_back(p);
    ateFruit = 0;
    m_dirX = 1;
    m_dirY=0;
}

void Snake::move()
{
    QPoint p = coords.back();

    // Move tail

    for(int i = coords.size()-1; i > 0; i--)
    {
        coords[i] = coords[i-1];
    }

    // Move head

    coords[0].rx() += m_dirX;
    coords[0].ry() += m_dirY;

    // Increase size if necessary

    if(ateFruit)
    {
        ateFruit=0;
        coords.push_back(p);
    }
}

void Snake::eat()
{
    ateFruit=1;
}

bool Snake::checkCollision() const
{
    QPoint first = coords[0];
    for(int i = 1; i < coords.size(); i++)
    {
        if(coords[i]==first) return 1;
    }
    return 0;
}

QPoint Snake::head() const
{
    return coords[0];
}
