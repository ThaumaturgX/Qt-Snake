#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include "snake.h"
#include "fruit.h"
#include <QKeyEvent>
#include <QLabel>


class Game : public QWidget
{
public:
    Game();
    void start();
    void end();
    void displaySnake(Snake);
    void displayFruit(Fruit);
    void displayField();

    void setTick(int x);

protected:
    void paintEvent(QPaintEvent*) override;
    void timerEvent(QTimerEvent*) override;
    void keyPressEvent(QKeyEvent*) override;

private:
    static const int CELL_WIDTH = 30;
    static const int CELL_HEIGHT = 30;
    static const int GRID_WIDTH = 30;
    static const int GRID_HEIGHT = 20;
    static const int TICK_MIN = 80;
    static const int TICK_START = 150;
    static const int X_ZERO = 0;
    static const int Y_ZERO = 0;

    bool gameOver;
    bool keyPressed;

    int timer;

    Snake m_snake;
    Fruit m_fruit;

    int tick = TICK_START;

};

#endif // GAME_H
