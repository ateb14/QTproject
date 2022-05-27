#include "game.h"
#include <QApplication>
#include <QSplashScreen>
#include <QGraphicsView>

const int PATHLEN = 150;
const char startPNG[PATHLEN] = ":/art/start.png";
const char welcomePNG[PATHLEN] = ":/art/welcome.jpg";
const char backgroundPNG[PATHLEN] = ":/art/soccerField.png";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* Start */
    QPixmap start(startPNG);
    QSplashScreen splash(start);
    splash.resize(start.size());
    splash.show();
    Sleep(1000);

    /* Welcome */
    game * gameWindow = new game;

    QGraphicsView *view = new QGraphicsView;
    view->resize(1290,810);
    view->setScene(gameWindow);
    view->setWindowTitle("Game");
    view->setBackgroundBrush(QBrush(QPixmap(backgroundPNG)));
    splash.finish(view);
    view->show();
    return a.exec();
}
