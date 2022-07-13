#ifndef FRUIT_H
#define FRUIT_H
#include <QString>
#include <QVector>
#include <QPoint>

class Fruit
{
public:
    Fruit();
    void place(int x, int y);
    QPoint position() const;
private:

    int m_x;
    int m_y;
};

#endif // FRUIT_H
