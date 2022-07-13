#include <iostream>
#include <QApplication>
#include <game.h>
using namespace std;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Game game;
    game.setWindowTitle("Snake");
    game.show();
    game.start();

    return app.exec();
}
