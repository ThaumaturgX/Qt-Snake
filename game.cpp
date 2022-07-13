#include "game.h"
#include <QPainter>
#include "snake.h"
#include <QDebug>
#include <QRandomGenerator>

Game::Game()
{
    this->setFixedSize(CELL_WIDTH * (GRID_WIDTH), CELL_HEIGHT * (GRID_HEIGHT));
    this->setStyleSheet("QWidget {background-image: url(C:/CG/backgroundtest.png) }");
}

void Game::start()
{
    gameOver = 0;
    keyPressed = 0;
    m_snake.m_dirX = 1;
    m_snake.m_dirY = 0;
    m_snake.coords.clear();
    m_snake.coords.push_back({X_ZERO+1,Y_ZERO+1});
    QRandomGenerator *gen = QRandomGenerator::global();
    int x = gen->bounded(1,GRID_WIDTH-1);
    int y = gen->bounded(1,GRID_HEIGHT-1);
    m_fruit.place(x,y);

    tick = TICK_START;
    timer = startTimer(tick);
}

void Game::end()
{
    gameOver = 1;
    killTimer(timer);
}

void Game::displaySnake(Snake snake)
{
    QPainter qp(this);
    qp.setBrush(Qt::darkGreen);
    auto &a = snake.coords;

    qp.drawEllipse(CELL_WIDTH * a[0].rx(),CELL_HEIGHT * a[0].ry(),CELL_WIDTH*1.1,CELL_HEIGHT*1.1);

    for(int i = 1; i < a.size(); i++)
    {
        qp.setBrush(QColor(0, 185 + (i*10)%70, 0));
        qp.drawEllipse(CELL_WIDTH * a[i].rx(),CELL_HEIGHT * a[i].ry(),CELL_WIDTH,CELL_HEIGHT);
    }
}

void Game::displayFruit(Fruit fruit)
{
    QPainter qp(this);
    qp.setBrush(Qt::red);
    qp.drawEllipse(
    CELL_WIDTH * fruit.position().rx(),
    CELL_HEIGHT * fruit.position().ry(),
                CELL_WIDTH,CELL_HEIGHT);
}

void Game::displayField()
{
    QPainter qp(this);
    QBrush qb;
    qb.setColor(Qt::black);
    qb.setStyle(Qt::BDiagPattern);
    qp.setBrush(qb);
    qp.drawRect(X_ZERO,Y_ZERO,CELL_WIDTH*GRID_WIDTH, CELL_HEIGHT); // top
    qp.drawRect(X_ZERO,Y_ZERO,CELL_WIDTH, GRID_HEIGHT*CELL_HEIGHT); // left
    qp.drawRect(X_ZERO,CELL_HEIGHT*(GRID_HEIGHT-1),CELL_WIDTH*GRID_WIDTH, CELL_HEIGHT); // bottom
    qp.drawRect((GRID_WIDTH-1)*CELL_WIDTH,Y_ZERO,CELL_WIDTH, CELL_HEIGHT*GRID_HEIGHT); // right
}

void Game::setTick(int x)
{
     tick = x;
     killTimer(timer);
     timer = startTimer(tick);

}

void Game::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    displaySnake(m_snake);
    displayFruit(m_fruit);
    //displayField();
}

void Game::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);

//    QLabel *label = new QLabel;
//    label->setText("Score: " + QString::number(m_snake.size()-1));
//    label->setAutoFillBackground(false);
//    label->setGeometry(0, 0,CELL_WIDTH * (GRID_WIDTH), CELL_HEIGHT * (GRID_HEIGHT) );
//    label->show();

    if(m_snake.head()==m_fruit.position())
    {
        m_snake.eat();
        QRandomGenerator *gen = QRandomGenerator::global();
        int x = gen->bounded(1,GRID_WIDTH-1);
        int y = gen->bounded(1,GRID_HEIGHT-1);
        m_fruit.place(x,y);
        if((m_snake.size()-1)%5==0)
        {
            int temp = TICK_MIN;
            this->setTick(std::max(tick-10, temp));
        }

    }

    QPoint last = m_snake.coords.back();
    m_snake.move();
    keyPressed=0;

    // If collided, move back and end the game

    if(m_snake.checkCollision()
    || m_snake.head().rx()<0
    || m_snake.head().rx()>=GRID_WIDTH
    || m_snake.head().ry()<0
    || m_snake.head().ry()>=GRID_HEIGHT)
    {
        auto &a = m_snake.coords;

        for(int i = 0; i < a.size()-1; i++)
        {
            a[i]=a[i+1];
        }
        a.back() = last;

        this->end();
    }

    this->repaint();
}

void Game::keyPressEvent(QKeyEvent *e)
{
    if(keyPressed && !gameOver)
        return;

    int key = e->key();
    switch(key)
    {
        case Qt::Key_Left:
            if(m_snake.m_dirX!=1)
            {
                m_snake.m_dirX = -1;
                m_snake.m_dirY = 0;
            }
            break;

        case Qt::Key_Right:
            if(m_snake.m_dirX!=-1)
            {
                m_snake.m_dirX = 1;
                m_snake.m_dirY = 0;
            }
            break;

        case Qt::Key_Down:
            if(m_snake.m_dirY!=-1)
            {
                m_snake.m_dirX = 0;
                m_snake.m_dirY = 1;
            }
            break;

        case Qt::Key_Up:
            if(m_snake.m_dirY!=1)
            {
                m_snake.m_dirX = 0;
                m_snake.m_dirY = -1;
            }
            break;

        case Qt::Key_R:
            if(!gameOver)
                killTimer(timer);
            this->start();
            break;
    }

    keyPressed=1;
}
