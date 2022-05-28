#include "mywindow.h"
#include "game.h"
#include <QSplashScreen>
#include <QGraphicsView>
#include "mybtn.h"
#include <QTimer>

const int PATHLEN = 150;
const char startPNG[PATHLEN] = ":/art/start.png";
const char welcomePNG[PATHLEN] = ":/art/welcome.jpg";
const char backgroundPNG[PATHLEN] = ":/art/soccerField.png";

myWindow::myWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Game");

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
    //view->setWindowTitle("Game");
    view->setBackgroundBrush(QBrush(QPixmap(backgroundPNG)));
    splash.finish(view);

    //quit button

    myBtn *quitBtn = new myBtn(":/art/quitgame.png",this);
    quitBtn->move((gameWindow->width()-100)/2,400);
    QObject::connect(quitBtn, &QPushButton::clicked, [=](){
        gameWindow->quit();
    });
    quitBtn->setParent(view);

    //start button
    myBtn *startBtn=new myBtn("://art/startgame.png",this);
    startBtn->move((gameWindow->width()-100)/2,300);
    QObject::connect(startBtn, &myBtn::clicked, [=](){
        startBtn->move((gameWindow->width()-100)/2,300);
        QTimer::singleShot(100,this,[=](){
            startBtn->hide();
            quitBtn->hide();
            gameWindow->start();
        });
    });
    startBtn->setParent(view);


    view->move(-11,-45);
    view->setParent(this);
//    view->show();

    //第二个view
    QGraphicsView *view2 = new QGraphicsView;
    view2->resize(1290,190);
    view2->setScene(gameWindow->getBoard());
    view2->move(0,810);
    view2->setParent(this);


    setFixedSize(1290,1000);
}
