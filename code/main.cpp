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

    /* Welcome */
    Game * gameWindow = new Game;

    QGraphicsView *view = new QGraphicsView;
    view->resize(1290,810);
    view->setScene(gameWindow);
    view->setWindowTitle("Game");
    view->setBackgroundBrush(QBrush(QPixmap(backgroundPNG)));
    splash.finish(view);

    //quit button
    QPushButton *quitBtn = new QPushButton("Quit");
    quitBtn->setFixedSize(100,50);
    quitBtn->move((gameWindow->width()-100)/2,400);
    QObject::connect(quitBtn, &QPushButton::clicked, [=](){
        gameWindow->quit();
    });
    quitBtn->setParent(view);
    //start button
    QPushButton *startBtn = new QPushButton("Start");
    startBtn->setFixedSize(100,50);
    startBtn->move((gameWindow->width()-100)/2,300);
    QObject::connect(startBtn, &QPushButton::clicked, [=](){
        startBtn->hide();
        quitBtn->hide();
        gameWindow->start();
    });
    startBtn->setParent(view);



    view->show();
    return a.exec();
}
