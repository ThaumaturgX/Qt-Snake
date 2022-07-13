#ifndef SNAKE_H
#define SNAKE_H
#include <QVector>
#include <QPoint>


class Snake
{
    friend class Game;

public:

    Snake();
    void move();
    void eat();
    bool checkCollision() const;
    inline size_t size() const {return coords.size();}

private:

    QVector<QPoint> coords;
    int m_dirX;
    int m_dirY;
    bool ateFruit = 0;
    QPoint head() const;
};

#endif // SNAKE_H
